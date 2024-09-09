#include "canvas2d.h"
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include "settings.h"
#include <algorithm>
#include <cmath>

/**
 * @brief Initializes new 500x500 canvas
 */
void Canvas2D::init() {
    setMouseTracking(true);
    m_width = 500;
    m_height = 500;
    clearCanvas();
}

/**
 * @brief Canvas2D::clearCanvas sets all canvas pixels to blank white
 */
void Canvas2D::clearCanvas() {
    m_data.assign(m_width * m_height, RGBA{255, 255, 255, 255});
    settings.imagePath = "";
    displayImage();
}

/**
 * @brief Stores the image specified from the input file in this class's
 * `std::vector<RGBA> m_image`.
 * Also saves the image width and height to canvas width and height respectively.
 * @param file: file path to an image
 * @return True if successfully loads image, False otherwise.
 */
bool Canvas2D::loadImageFromFile(const QString &file) {
    QImage myImage;
    if (!myImage.load(file)) {
        std::cout<<"Failed to load in image"<<std::endl;
        return false;
    }
    myImage = myImage.convertToFormat(QImage::Format_RGBX8888);
    m_width = myImage.width();
    m_height = myImage.height();
    QByteArray arr = QByteArray::fromRawData((const char*) myImage.bits(), myImage.sizeInBytes());

    m_data.clear();
    m_data.reserve(m_width * m_height);
    for (int i = 0; i < arr.size() / 4; i++){
        m_data.push_back(RGBA{(std::uint8_t) arr[4*i], (std::uint8_t) arr[4*i+1], (std::uint8_t) arr[4*i+2], (std::uint8_t) arr[4*i+3]});
    }
    displayImage();
    return true;
}

/**
 * @brief Saves the current canvas image to the specified file path.
 * @param file: file path to save image to
 * @return True if successfully saves image, False otherwise.
 */
bool Canvas2D::saveImageToFile(const QString &file) {
    QImage myImage = QImage(m_width, m_height, QImage::Format_RGBX8888);
    for (int i = 0; i < m_data.size(); i++){
        myImage.setPixelColor(i % m_width, i / m_width, QColor(m_data[i].r, m_data[i].g, m_data[i].b, m_data[i].a));
    }
    if (!myImage.save(file)) {
        std::cout<<"Failed to save image"<<std::endl;
        return false;
    }
    return true;
}


/**
 * @brief Get Canvas2D's image data and display this to the GUI
 */
void Canvas2D::displayImage() {
    QByteArray img(reinterpret_cast<const char *>(m_data.data()), 4 * m_data.size());
    QImage now = QImage((const uchar*)img.data(), m_width, m_height, QImage::Format_RGBX8888);
    setPixmap(QPixmap::fromImage(now));
    setFixedSize(m_width, m_height);
    update();
}

/**
 * @brief Canvas2D::resize resizes canvas to new width and height
 * @param w
 * @param h
 */
void Canvas2D::resize(int w, int h) {
    m_width = w;
    m_height = h;
    m_data.resize(w * h);
    displayImage();
}

/**
 * @brief Called when the filter button is pressed in the UI
 */
void Canvas2D::filterImage() {

    // EXAMPLE 1: per-pixel debugging
    for (int i = 0; i < m_data.size(); i++) {
//        if (i == 481*m_height + 257) {
            auto& pix = m_data[i];
//            pix.r *= 1.1;
//            pix.g *= 1.1;
//            pix.b *= 1.1;
            pix.r = std::min(255.0, pix.r*1.1);
            pix.g = std::min(255.0, pix.g*1.1);
            pix.b = std::min(255.0, pix.b*1.1);
//        }
    }




//    // EXAMPLE 2: Visualizing intermediates (e.g. 'visual printf')

//    int x_mid = m_width / 2;
//    int y_mid = m_height / 2;
//    float max_dist = std::max(m_width, m_height);
//    int stripe_width = 20;

//    for (int i = 0 ; i < m_data.size(); i++) {
//        int y = i / m_height;
//        int x = i % m_height;
//        auto dist = (int)(std::sqrt((x-x_mid)*(x-x_mid) + (y-y_mid)*(y-y_mid)));
////        auto dist = (x-x_mid) + (y-y_mid);
//        auto& pix = m_data[i];
////        pix.r = 255 * (dist / max_dist);
////        pix.g = 255 * (dist / max_dist);
////        pix.b = 255 * (dist / max_dist);
//        pix.r = ((dist / stripe_width) % 2) == 0 ? 255: 0;
//        pix.g = ((dist / stripe_width) % 2) == 0 ? 255: 0;
//        pix.b = ((dist / stripe_width) % 2) == 0 ? 255: 0;
//    }

    displayImage();
}

/**
 * @brief Called when any of the parameters in the UI are modified.
 */
void Canvas2D::settingsChanged() {
    // this saves your UI settings locally to load next time you run the program
    settings.saveSettings();

    // TODO: fill in what you need to do when brush or filter parameters change
}

/**
 * @brief These functions are called when the mouse is clicked and dragged on the canvas
 */
void Canvas2D::mouseDown(int x, int y) {
    // Brush TODO
}

void Canvas2D::mouseDragged(int x, int y) {
    // Brush TODO
}

void Canvas2D::mouseUp(int x, int y) {
    // Brush TODO
}
