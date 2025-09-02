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

// Constant key expressions for querying QSettings
namespace QSettingsKeys {
    namespace Brush {
        constexpr QAnyStringView
            BRUSH_TYPE         = "brushType",
            BRUSH_RADIUS       = "brushRadius",
            BRUSH_RED          = "brushRed",
            BRUSH_GREEN        = "brushGreen",
            BRUSH_BLUE         = "brushBlue",
            BRUSH_ALPHA        = "brushAlpha",
            BRUSH_DENSITY      = "brushDensity",
            FIX_ALPHA_BLENDING = "fixAlphaBlending";
    }
    namespace Filter {
        constexpr QAnyStringView
            FILTER_TYPE             = "filterType",
            EDGE_DETECT_SENSITIVITY = "edgeDetectSensitivity",
            BLUR_RADIUS             = "blurRadius",
            SCALE_X                 = "scaleX",
            SCALE_Y                 = "scaleY",
            MEDIAN_RADIUS           = "medianRadius",
            ROTATION_ANGLE          = "rotationAngle",
            BILATERAL_RADIUS        = "bilateralRadius",
            R_SHIFT                 = "rShift",
            G_SHIFT                 = "gShift",
            B_SHIFT                 = "bShift",
            NON_LINEAR_MAP          = "nonLinearMap",
            GAMMA                   = "gamma",
            IMAGE_PATH              = "imagePath";
    }
}

/**
 * @brief Loads the application settings
 */
void Settings::loadSettingsOrDefaults() {
    using namespace QSettingsKeys;

    QSettings s("CS123", "CS123");

    // Load settings for Brush
    brushType             = s.value(Brush::BRUSH_TYPE, BRUSH_LINEAR).toInt();
    brushRadius           = s.value(Brush::BRUSH_RADIUS, 10).toInt();
    brushColor.r          = s.value(Brush::BRUSH_RED, 0).toInt();
    brushColor.g          = s.value(Brush::BRUSH_GREEN, 0).toInt();
    brushColor.b          = s.value(Brush::BRUSH_BLUE, 0).toInt();
    brushColor.a          = s.value(Brush::BRUSH_ALPHA, 255).toInt();
    brushDensity          = s.value(Brush::BRUSH_DENSITY, 5).toInt();
    fixAlphaBlending      = s.value(Brush::FIX_ALPHA_BLENDING, false).toBool();

    // Load settings for Filter
    filterType            = s.value(Filter::FILTER_TYPE, FILTER_EDGE_DETECT).toInt();
    edgeDetectSensitivity = s.value(Filter::EDGE_DETECT_SENSITIVITY, 0.5f).toDouble();
    blurRadius            = s.value(Filter::BLUR_RADIUS, 10).toInt();
    scaleX                = s.value(Filter::SCALE_X, 2).toDouble();
    scaleY                = s.value(Filter::SCALE_Y, 2).toDouble();
    medianRadius          = s.value(Filter::MEDIAN_RADIUS, 1).toInt();
    rotationAngle         = s.value(Filter::ROTATION_ANGLE, 90.0).toFloat();
    bilateralRadius       = s.value(Filter::BILATERAL_RADIUS, 1).toInt();
    rShift                = s.value(Filter::R_SHIFT, 1).toInt();
    gShift                = s.value(Filter::G_SHIFT, 1).toInt();
    bShift                = s.value(Filter::B_SHIFT, 1).toInt();
    nonLinearMap          = s.value(Filter::NON_LINEAR_MAP, false).toBool();
    gamma                 = s.value(Filter::GAMMA, 0.1).toFloat();
    imagePath             = s.value(Filter::IMAGE_PATH, "").toString();
}

/**
 * @brief Saves settings from this session to be loaded
 * in for next session.
 */
void Settings::saveSettings() {
    using namespace QSettingsKeys;

    QSettings s("CS123", "CS123");

    // Save settings for Brush
    s.setValue(Brush::BRUSH_TYPE, brushType);
    s.setValue(Brush::BRUSH_RADIUS, brushRadius);
    s.setValue(Brush::BRUSH_RED, brushColor.r);
    s.setValue(Brush::BRUSH_GREEN, brushColor.g);
    s.setValue(Brush::BRUSH_BLUE, brushColor.b);
    s.setValue(Brush::BRUSH_ALPHA, brushColor.a);
    s.setValue(Brush::BRUSH_DENSITY, brushDensity);
    s.setValue(Brush::FIX_ALPHA_BLENDING, fixAlphaBlending);

    // Save settings for Filter
    s.setValue(Filter::FILTER_TYPE, filterType);
    s.setValue(Filter::EDGE_DETECT_SENSITIVITY, edgeDetectSensitivity);
    s.setValue(Filter::BLUR_RADIUS, blurRadius);
    s.setValue(Filter::SCALE_X, scaleX);
    s.setValue(Filter::SCALE_Y, scaleY);
    s.setValue(Filter::MEDIAN_RADIUS, medianRadius);
    s.setValue(Filter::ROTATION_ANGLE, rotationAngle);
    s.setValue(Filter::BILATERAL_RADIUS, bilateralRadius);
    s.setValue(Filter::R_SHIFT, rShift);
    s.setValue(Filter::G_SHIFT, gShift);
    s.setValue(Filter::B_SHIFT, bShift);
    s.setValue(Filter::NON_LINEAR_MAP, nonLinearMap);
    s.setValue(Filter::GAMMA, gamma);
    s.setValue(Filter::IMAGE_PATH, imagePath);
}
