/*!

 Settings.h
 CS123 Support Code

 @author  Evan Wallace (edwallac)
 @date    9/1/2010

 This file contains various settings and enumerations that you will need to
 use in the various assignments. The settings are bound to the GUI via static
 data bindings.

**/

#include "settings.h"
#include <QSettings>

Settings settings;

/**
 * @brief Loads the application settings
 */
void Settings::loadSettingsOrDefaults() {
    // Load image settings
    QSettings s("CS123", "CS123");

    brushType = s.value("brushType", BRUSH_LINEAR).toInt();
    brushRadius = s.value("brushRadius", 10).toInt();
    brushColor.r = s.value("brushRed", 0).toInt();
    brushColor.g = s.value("brushGreen", 0).toInt();
    brushColor.b = s.value("brushBlue", 0).toInt();
    brushColor.a = s.value("brushAlpha", 255).toInt();
    brushDensity = s.value("brushDensity", 5).toInt();
    fixAlphaBlending = s.value("fixAlphaBlending", false).toBool();

    imagePath = s.value("imagePath", "").toString();
}

/**
 * @brief Saves settings from this session to be loaded
 * in for next session.
 */
void Settings::saveSettings() {
    QSettings s("CS123", "CS123");

    s.setValue("brushType", brushType);
    s.setValue("brushRadius", brushRadius);
    s.setValue("brushRed", brushColor.r);
    s.setValue("brushGreen", brushColor.g);
    s.setValue("brushBlue", brushColor.b);
    s.setValue("brushAlpha", brushColor.a);
    s.setValue("brushDensity", brushDensity);
    s.setValue("fixAlphaBlending", fixAlphaBlending);

    s.setValue("imagePath", imagePath);
}
