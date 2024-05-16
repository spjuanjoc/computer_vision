/**
* @brief Handles the multimedia events for the keyboard and mouse.
*
* @author  spjuanjoc
* @date    2021-11-26
*/

#include "Core/Events/EventsHandler.h"

#include "Core/Logging/Logger.h"

#include "bindings/imgui-SFML.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace Core
{

EventsHandler::EventsHandler(const std::shared_ptr<sf::RenderWindow>& window)
: m_window(window)
{
}

void
EventsHandler::poll()
{
  if (m_window)
    poll(*m_window);
}

void
EventsHandler::poll(sf::RenderWindow& window)
{
  sf::Event event {};

  while (window.pollEvent(event))
  {
    ImGui::SFML::ProcessEvent(window, event);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      m_is_clicked = true;
      onLeftClick();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
      m_is_clicked = true;
      onRightClick();
    }

    switch (event.type)
    {
      case sf::Event::KeyPressed:
      {
        m_key        = static_cast<KEY_NAMES>(event.key.code);
        m_is_alt     = event.key.alt;
        m_is_control = event.key.control;
        m_is_shift   = event.key.shift;
        m_is_system  = event.key.system;

        pauseResume();
        close(window);

        break;
      }
      case sf::Event::KeyReleased:
      {
        m_key = KEY_NAMES::UNKNOWN;
        break;
      }
      case sf::Event::MouseButtonPressed:
      {
        m_is_clicked = true;
        break;
      }
      case sf::Event::MouseButtonReleased:
      {
        m_is_clicked = false;
        onMouseReleased();
        break;
      }
      case sf::Event::Closed:
      {
        Logger::Info("Bye");
        window.close();
        break;
      }
      default:
        break;
    }
  }  // End of poll event
}

void
EventsHandler::pauseResume()
{
  if (KEY_NAMES::Enter == pressedKey())
  {
    if (m_is_running)
    {
      m_is_running = false;
      Logger::Info("Pause");
    }
    else
    {
      m_is_running = true;
      Logger::Info("Start");
    }
  }
}

void
EventsHandler::close()
{
  if (m_window)
    close(*m_window);
}

void
EventsHandler::close(sf::RenderWindow& window)
{
  if ((m_is_shift || m_is_control) && (m_key == KEY_NAMES::W || m_key == KEY_NAMES::Q))
  {
    Logger::Info("Close");
    window.close();
  }
}

bool
EventsHandler::isClickPressed() const
{
  return m_is_clicked;
}

EventsHandler::ClickSignal
EventsHandler::signalClicked() const
{
  return m_left_click_signal;
}

EventsHandler::ClickSignal
EventsHandler::signalRightClick() const
{
  return m_right_click_signal;
}

EventsHandler::ReleasedSignal
EventsHandler::signalMouseReleased() const
{
  return m_mouse_released_signal;
}

void
EventsHandler::onLeftClick() const
{
  const auto& click_x = sf::Mouse::getPosition(*m_window).x;
  const auto& click_y = sf::Mouse::getPosition(*m_window).y;

  m_left_click_signal.emit(click_x, click_y);
}

void
EventsHandler::onRightClick() const
{
  const auto& click_x = sf::Mouse::getPosition(*m_window).x;
  const auto& click_y = sf::Mouse::getPosition(*m_window).y;

  m_right_click_signal.emit(click_x, click_y);
}

void
EventsHandler::onMouseReleased() const
{
  m_mouse_released_signal.emit();
}

}  // namespace Core
