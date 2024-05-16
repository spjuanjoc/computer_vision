/**
 * @brief Defines the constants for the screen components.
 *
 * @author  spjuanjoc
 * @date    2021-11-26
 */

#ifndef SCREEN_COMPONENTS_CONSTANTS_H
#define SCREEN_COMPONENTS_CONSTANTS_H

#include <cstdint>

namespace Screen::Components
{

constexpr std::uint32_t MAP_COLS { 70 };
constexpr std::uint32_t MAP_ROWS { 40 };

constexpr float TILE_SCALE      = 2.0F;
constexpr float HALF_DIVISOR    = 2.0F;
constexpr float QUARTER_DIVISOR = 4.0F;

constexpr auto BACKGROUND_FILENAME = "share/textures/background/gray.png";
constexpr auto START_FILENAME      = "share/textures/background/background_pastel.png";
constexpr auto START_TEXT          = "TO START PRESS ENTER";

}  // namespace Screen::Components

#endif  //SCREEN_COMPONENTS_CONSTANTS_H
