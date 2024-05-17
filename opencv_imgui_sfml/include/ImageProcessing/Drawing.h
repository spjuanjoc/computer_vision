/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-15
 */

#ifndef INCLUDE_IMAGEPROCESSING_DRAWING_H
#define INCLUDE_IMAGEPROCESSING_DRAWING_H

#include "Conversions.h"

#include <imgui.h>

#include "bindings/imgui-SFML.h"
#include <SFML/Graphics/Texture.hpp>
#include <opencv2/core/mat.hpp>

namespace Processing
{

void
createCvMat(bool is_open);

void
drawSrcImage(const sf::Texture& texture_src, bool& is_open);

}  // namespace Processing

#endif  //INCLUDE_IMAGEPROCESSING_DRAWING_H
