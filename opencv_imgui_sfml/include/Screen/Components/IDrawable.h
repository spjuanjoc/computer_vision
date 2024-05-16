/**
 * @brief Declares the interface for drawable objects.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#ifndef SCREEN_COMPONENTS_DRAWABLE_H
#define SCREEN_COMPONENTS_DRAWABLE_H

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

namespace Screen::Components
{

class IDrawable
{
public:
  IDrawable()                                = default;
  virtual ~IDrawable()                       = default;
  IDrawable(IDrawable&& rhs)                 = default;
  IDrawable(const IDrawable& rhs)            = default;
  IDrawable& operator=(IDrawable&& rhs)      = default;
  IDrawable& operator=(const IDrawable& rhs) = default;

  virtual void draw() = 0;

  virtual void draw(sf::RenderWindow& window) = 0;

  virtual void setWindow(std::shared_ptr<sf::RenderWindow> window) = 0;

protected:
  std::shared_ptr<sf::RenderWindow> m_window;
};

}  // namespace Screen::Components

#endif  //SCREEN_COMPONENTS_DRAWABLE_H
