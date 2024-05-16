/**
 * @brief Declares the drawer for the application background.
 *
 * @author  spjuanjoc
 * @date    2021-10-12
 */

#ifndef SCREEN_COMPONENTS_BACKGROUND_H
#define SCREEN_COMPONENTS_BACKGROUND_H

#include "Constants.h"
#include "Screen/Components/IDrawable.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string_view>

namespace Screen::Components
{

class Background : virtual public IDrawable
{
public:
  Background();
  explicit Background(std::string_view texture_filename);

  void draw() override;

  void draw(sf::RenderWindow& window) override;

  void setWindow(std::shared_ptr<sf::RenderWindow> window) override;

protected:
  void loadTexturesFiles();

  void setTextures();

private:
  std::string_view m_file { BACKGROUND_FILENAME };
  sf::Texture      m_texture;
  sf::Sprite       m_sprite;
};

}  // namespace Screen::Components

#endif  //SCREEN_COMPONENTS_BACKGROUND_H
