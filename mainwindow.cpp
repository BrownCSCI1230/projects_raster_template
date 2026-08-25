#include "mainwindow.h"
#include "settings.h"

#include <QCheckBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QTabWidget>
#include <QVBoxLayout>
#include <iostream>

MainWindow::MainWindow() {
    setWindowTitle("2D Projects: Brush");

    // loads in settings from last run or uses default values
    settings.loadSettingsOrDefaults();

    QHBoxLayout* hLayout =
        new QHBoxLayout();  // horizontal layout for canvas and controls panel

    // layout for all the controls
    QVBoxLayout* controlsLayout = new QVBoxLayout();
    controlsLayout->setAlignment(Qt::AlignTop);

    // make the controls panel scrollable
    QWidget* controlsWidget = new QWidget();
    controlsWidget->setLayout(controlsLayout);
    QScrollArea* controlsScroll = new QScrollArea();
    controlsScroll->setWidget(controlsWidget);
    controlsScroll->setWidgetResizable(true);

    // add the controls panel to the h layout
    hLayout->addWidget(controlsScroll);
    setLayout(hLayout);

    setupCanvas2D();
    resize(800, 600);

    // makes the canvas into a scroll area
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(m_canvas);
    scrollArea->setWidgetResizable(true);
    hLayout->addWidget(scrollArea, 1);

    // brush selection
    addHeading(controlsLayout, "Brush");
    addRadioButton(controlsLayout, "Constant",
                   settings.brushType == BRUSH_CONSTANT,
                   [this] { setBrushType(BRUSH_CONSTANT); });
    addRadioButton(controlsLayout, "Linear", settings.brushType == BRUSH_LINEAR,
                   [this] { setBrushType(BRUSH_LINEAR); });
    addRadioButton(controlsLayout, "Quadratic",
                   settings.brushType == BRUSH_QUADRATIC,
                   [this] { setBrushType(BRUSH_QUADRATIC); });
    addRadioButton(controlsLayout, "Smudge", settings.brushType == BRUSH_SMUDGE,
                   [this] { setBrushType(BRUSH_SMUDGE); });

    // brush parameters
    addSpinBox(controlsLayout, "red", 0, 255, 1, settings.brushColor.r,
               [this](int value) { setUIntVal(settings.brushColor.r, value); });
    addSpinBox(controlsLayout, "green", 0, 255, 1, settings.brushColor.g,
               [this](int value) { setUIntVal(settings.brushColor.g, value); });
    addSpinBox(controlsLayout, "blue", 0, 255, 1, settings.brushColor.b,
               [this](int value) { setUIntVal(settings.brushColor.b, value); });
    addSpinBox(controlsLayout, "alpha", 0, 255, 1, settings.brushColor.a,
               [this](int value) { setUIntVal(settings.brushColor.a, value); });
    addSpinBox(controlsLayout, "radius", 0, 100, 1, settings.brushRadius,
               [this](int value) { setIntVal(settings.brushRadius, value); });

    // extra credit brushes
    addHeading(controlsLayout, "Extra Credit Brushes");
    addRadioButton(controlsLayout, "Spray", settings.brushType == BRUSH_SPRAY,
                   [this] { setBrushType(BRUSH_SPRAY); });
    addSpinBox(controlsLayout, "density", 0, 100, 1, settings.brushDensity,
               [this](int value) { setIntVal(settings.brushDensity, value); });
    addRadioButton(controlsLayout, "Speed", settings.brushType == BRUSH_SPEED,
                   [this] { setBrushType(BRUSH_SPEED); });
    addRadioButton(controlsLayout, "Fill", settings.brushType == BRUSH_FILL,
                   [this] { setBrushType(BRUSH_FILL); });
    addRadioButton(controlsLayout, "Custom", settings.brushType == BRUSH_CUSTOM,
                   [this] { setBrushType(BRUSH_CUSTOM); });
    addCheckBox(
        controlsLayout, "Fix alpha blending", settings.fixAlphaBlending,
        [this](bool value) { setBoolVal(settings.fixAlphaBlending, value); });

    // clearing canvas
    addPushButton(controlsLayout, "Clear canvas",
                  &MainWindow::onClearButtonClick);

    // save canvas as image
    addPushButton(controlsLayout, "Save Image", &MainWindow::onSaveButtonClick);
}

/**
 * @brief Sets up Canvas2D
 */
void MainWindow::setupCanvas2D() {
    m_canvas = new Canvas2D();
    m_canvas->init();

    if (!settings.imagePath.isEmpty()) {
        m_canvas->loadImageFromFile(settings.imagePath);
    }
}

// ------ FUNCTIONS FOR ADDING UI COMPONENTS ------

void MainWindow::addHeading(QBoxLayout* layout, QString text) {
    QFont font;
    font.setPointSize(16);
    font.setBold(true);

    QLabel* label = new QLabel(text);
    label->setFont(font);
    layout->addWidget(label);
}

void MainWindow::addLabel(QBoxLayout* layout, QString text) {
    layout->addWidget(new QLabel(text));
}

void MainWindow::addRadioButton(QBoxLayout* layout,
                                QString text,
                                bool value,
                                auto function) {
    QRadioButton* button = new QRadioButton(text);
    button->setChecked(value);
    layout->addWidget(button);
    connect(button, &QRadioButton::clicked, this, function);
}

void MainWindow::addSpinBox(QBoxLayout* layout,
                            QString text,
                            int min,
                            int max,
                            int step,
                            int val,
                            auto function) {
    QSpinBox* box = new QSpinBox();
    box->setMinimum(min);
    box->setMaximum(max);
    box->setSingleStep(step);
    box->setValue(val);
    QHBoxLayout* subLayout = new QHBoxLayout();
    addLabel(subLayout, text);
    subLayout->addWidget(box);
    layout->addLayout(subLayout);
    connect(box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, function);
}

void MainWindow::addDoubleSpinBox(QBoxLayout* layout,
                                  QString text,
                                  double min,
                                  double max,
                                  double step,
                                  double val,
                                  int decimal,
                                  auto function) {
    QDoubleSpinBox* box = new QDoubleSpinBox();
    box->setMinimum(min);
    box->setMaximum(max);
    box->setSingleStep(step);
    box->setValue(val);
    box->setDecimals(decimal);
    QHBoxLayout* subLayout = new QHBoxLayout();
    addLabel(subLayout, text);
    subLayout->addWidget(box);
    layout->addLayout(subLayout);
    connect(box,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            this, function);
}

void MainWindow::addPushButton(QBoxLayout* layout,
                               QString text,
                               auto function) {
    QPushButton* button = new QPushButton(text);
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, function);
}

void MainWindow::addCheckBox(QBoxLayout* layout,
                             QString text,
                             bool val,
                             auto function) {
    QCheckBox* box = new QCheckBox(text);
    box->setChecked(val);
    layout->addWidget(box);
    connect(box, &QCheckBox::clicked, this, function);
}

// ------ FUNCTIONS FOR UPDATING SETTINGS ------

void MainWindow::setBrushType(int type) {
    settings.brushType = type;
    m_canvas->settingsChanged();
}

void MainWindow::setUIntVal(std::uint8_t& setValue, int newValue) {
    setValue = newValue;
    m_canvas->settingsChanged();
}

void MainWindow::setIntVal(int& setValue, int newValue) {
    setValue = newValue;
    m_canvas->settingsChanged();
}

void MainWindow::setFloatVal(float& setValue, float newValue) {
    setValue = newValue;
    m_canvas->settingsChanged();
}

void MainWindow::setBoolVal(bool& setValue, bool newValue) {
    setValue = newValue;
    m_canvas->settingsChanged();
}

// ------ PUSH BUTTON FUNCTIONS ------

void MainWindow::onClearButtonClick() {
    m_canvas->resize(m_canvas->parentWidget()->size().width(),
                     m_canvas->parentWidget()->size().height());
    m_canvas->clearCanvas();
}

void MainWindow::onRevertButtonClick() {
    m_canvas->loadImageFromFile(settings.imagePath);
}

void MainWindow::onUploadButtonClick() {
    // Get new image path selected by user
    QString file =
        QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath(),
                                     tr("Image Files (*.png *.jpg *.jpeg)"));
    if (file.isEmpty()) {
        return;
    }
    settings.imagePath = file;

    // Display new image
    m_canvas->loadImageFromFile(settings.imagePath);

    m_canvas->settingsChanged();
}

void MainWindow::onSaveButtonClick() {
    // Get new image path selected by user
    QString file = QFileDialog::getSaveFileName(
        this, tr("Save Image"), QDir::currentPath(),
        tr("Image Files (*.png *.jpg *.jpeg)"));
    if (file.isEmpty()) {
        return;
    }

    // Save image
    m_canvas->saveImageToFile(file);
}
