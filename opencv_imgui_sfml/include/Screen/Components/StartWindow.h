/**
 * @brief Declares the drawer for the start window class.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#ifndef SCREEN_COMPONENTS_STARTWINDOW_H
#define SCREEN_COMPONENTS_STARTWINDOW_H

#include "Constants.h"
#include "Screen/Components/IDrawable.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string_view>

#include <imgui.h>

namespace Screen::Components
{

class StartWindow : virtual public IDrawable
{
public:
  StartWindow();
  explicit StartWindow(std::string_view texture_filename);

  ~StartWindow() override                    = default;
  StartWindow(StartWindow&&)                 = default;
  StartWindow(const StartWindow&)            = default;
  StartWindow& operator=(StartWindow&&)      = default;
  StartWindow& operator=(const StartWindow&) = default;

  void draw() override;

  void draw(sf::RenderWindow& window) override;

  void setWindow(std::shared_ptr<sf::RenderWindow> window) override;

protected:
  void loadTexturesFiles();

  void setTextures();

  void setText(const ImVec2& position);

private:
  std::string_view m_text { START_TEXT };
  std::string_view m_file { START_FILENAME };
  sf::Texture      m_texture;
  sf::Sprite       m_sprite;
};

}  // namespace Screen::Components

#endif  //SCREEN_COMPONENTS_STARTWINDOW_H
