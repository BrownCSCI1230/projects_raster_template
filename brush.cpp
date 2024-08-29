#include "canvas2d.h"
#include "settings.h"

#include <iostream>

// Helper functions (can move to utils)

std::vector<int> indexToCoords(int index, int width) {
    return std::vector<int>{(int) (index / width), index % width};
}

float distanceFromCenter(int i) {
    std::vector<int> maskCoords = indexToCoords(i, settings.brushRadius * 2 + 1);
    return sqrt(pow(maskCoords[0] - settings.brushRadius, 2) + pow(maskCoords[1] - settings.brushRadius, 2));

}

// Opacity calculations

/**
 * @brief coordsToIndex
 * @param x col to convert
 * @param y row to convert
 * @param width number of columns in the 2D representation
 * @return index of the 1D vector corresponding to the coord (x, y)
 */
int coordsToIndex(int x, int y, int width) {
    return width * y + x;
}

/**
 * Initializes the mask with all 0 opacity.
 * @brief initializeMask
 */
void Canvas2D::initializeMask() {
    mask = std::vector<float>(pow(2 * settings.brushRadius + 1, 2));
    std::fill (mask.begin(), mask.end(), 0);
}

void Canvas2D::applyMask(int r, int c) {
    int length = 2 * settings.brushRadius + 1;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {

            int maskIndex = i * length + j;
            int currRow = r + i - settings.brushRadius;
            int currCol = c + j - settings.brushRadius;

            if (currCol >= 0 && currCol < m_width && currRow >= 0 && currRow < m_height) {
                int currIndex = coordsToIndex(currCol, currRow, m_width);

                RGBA color = settings.brushColor;

                m_data[currIndex].r= (1 - mask[maskIndex]) * m_data[currIndex].r + mask[maskIndex] * color.r;
                m_data[currIndex].g = (1 - mask[maskIndex]) * m_data[currIndex].g + mask[maskIndex] * color.g;
                m_data[currIndex].b = (1 - mask[maskIndex]) * m_data[currIndex].b + mask[maskIndex] * color.b;

//                m_data[currIndex].r = 0.f * mask[maskIndex];
//                m_data[currIndex].g = 0.f * mask[maskIndex];
//                m_data[currIndex].b = 255.f * mask[maskIndex];
            }
        }
    }
    displayImage();
}

/**
 * Updates the mask's opacity values. Invoked when the brush size or the brush type changes.
 * @brief Brush::updateMask
 */
void Canvas2D::updateMask() {
    for (int i = 0; i < mask.size(); ++i) {
        float dist = distanceFromCenter(i);
        std::cout<<dist<<std::endl;
        if (dist <= settings.brushRadius) {
            mask[i] = 1;
//            if (settings.brushType == BRUSH_CONSTANT) {
//                mask[i] = 1;
//                currBrushType = BRUSH_CONSTANT;
//            } else if (settings.brushType == BRUSH_LINEAR) {
//                mask[i] = calcLinearOpacity(dist);
//                currBrushType = BRUSH_LINEAR;
//            } else if (settings.brushType == BRUSH_QUADRATIC) {
//                mask[i] = calcQuadraticOpacity(dist);
//                currBrushType = BRUSH_QUADRATIC;
//            }
        }
    }
}

