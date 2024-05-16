/**
 * @brief Defines the transversal constants.
 *
 * @author  spjuanjoc
 * @date    2021-11-26
 */

#ifndef CORE_CONSTANTS_H
#define CORE_CONSTANTS_H

#include <cstdint>

namespace Core
{

constexpr std::uint32_t DEFAULT_LEVEL  = 4;
constexpr std::uint32_t MAX_FRAME_RATE = 30;
constexpr std::uint32_t WINDOW_HEIGHT  = 480;
constexpr std::uint32_t WINDOW_WIDTH   = 640;

constexpr float WINDOW_SCALE = 1.0F;

constexpr auto NAME    = "opencv_imgui_sfml";
constexpr auto VERSION = "1.0.0";

}  // namespace Core

constexpr float FONT_SIZE     = 22.0F;

constexpr auto  FONT_FILENAME = "share/fonts/roboto/Roboto-Regular.ttf";
constexpr auto  WINDOW_TITLE  = "Hello OpenCV";

#endif /* CORE_CONSTANTS_H */
