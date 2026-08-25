/**
 * @file    Settings.h
 *
 * This file contains various settings and enumerations that you will need to
 * use in the various assignments. The settings are bound to the GUI via static
 * data bindings.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "rgba.h"

// Enumeration values for the Brush types from which the user can choose in the
// GUI.
enum BrushType {
    BRUSH_CONSTANT,
    BRUSH_LINEAR,
    BRUSH_QUADRATIC,
    BRUSH_SMUDGE,
    BRUSH_SPRAY,
    BRUSH_SPEED,
    BRUSH_FILL,
    BRUSH_CUSTOM,
    NUM_BRUSH_TYPES
};

/**
 * @struct Settings
 *
 * Stores application settings for the CS123 GUI.
 *
 * You can access all app settings through the "settings" global variable.
 * The settings will be automatically updated when things are changed in the
 * GUI (the reverse is not true however: changing the value of a setting does
 * not update the GUI).
 */
struct Settings {
    // Brush
    int brushType;    // The user's selected brush @see BrushType
    int brushRadius;  // The brush radius
    RGBA brushColor;
    int brushDensity;       // This is for spray brush (extra credit)
    bool fixAlphaBlending;  // Fix alpha blending (extra credit)

    QString imagePath;

    void loadSettingsOrDefaults();
    void saveSettings();
};

// The global Settings object, will be initialized by MainWindow
extern Settings settings;

#endif  // SETTINGS_H
