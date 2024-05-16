/**
 * @brief Defines the background class.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#include "Screen/Components/Background.h"

namespace Screen::Components
{

Background::Background()
: Background(BACKGROUND_FILENAME)
{
}

Background::Background(std::string_view texture_filename)
: m_file(texture_filename)
{
  loadTexturesFiles();
  setTextures();
}

void
Background::draw()
{
  if (m_window != nullptr)
  {
    draw(*m_window);
  }
}

void
Background::draw(sf::RenderWindow& window)
{
  window.draw(m_sprite);
}

void
Background::setWindow(std::shared_ptr<sf::RenderWindow> window)
{
  m_window = window;
}

void
Background::loadTexturesFiles()
{
  m_texture.loadFromFile(m_file.data());
}

void
Background::setTextures()
{
  m_sprite.setTexture(m_texture);
}

}  // namespace Screen::Components
