/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-27
 */

#ifndef IMAGEPROCESSING_VIDEO_LOADVIDEO_HPP
#define IMAGEPROCESSING_VIDEO_LOADVIDEO_HPP

#include <SFML/Graphics/Texture.hpp>

namespace Processing::Video
{

void
loadFromFile(const std::string& filename, bool is_open);

}

#endif  //IMAGEPROCESSING_VIDEO_LOADVIDEO_HPP
