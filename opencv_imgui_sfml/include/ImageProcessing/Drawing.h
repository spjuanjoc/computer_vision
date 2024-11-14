/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-15
 */

#ifndef INCLUDE_IMAGEPROCESSING_DRAWING_H
#define INCLUDE_IMAGEPROCESSING_DRAWING_H

#include "bindings/imgui-SFML.h"

namespace Processing
{

void
createCvMat(bool is_open);

void
drawSrcImage(const sf::Texture& texture_src, bool& is_open);

}  // namespace Processing

#endif  //INCLUDE_IMAGEPROCESSING_DRAWING_H
