/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-15
 */

#ifndef OPENCV_IMGUI_SFML_INCLUDE_SCREEN_MENU_H
#define OPENCV_IMGUI_SFML_INCLUDE_SCREEN_MENU_H

#include <Core/Logging/Logger.h>

#include <array>
#include <imgui.h>
#include <span>

namespace Screen::Menu
{

class MenuBuilder
{
public:
  using CallbackPair = std::pair<std::string_view, std::function<void()>>;
  using SubmenuPair  = std::pair<std::string, std::span<std::string>>;
  using OptionsMap   = std::unordered_map<std::string, std::span<std::string>>;

  void draw(std::string_view name);

  void drawSubmenu(std::string_view name);

  void drawCombobox(std::string_view name, size_t& option_index);

  void setButtonsSize(const ImVec2& size);

  MenuBuilder& addMenuOptions(const MenuBuilder::SubmenuPair& menu);

  MenuBuilder& addPopupOption(const CallbackPair& option);

  MenuBuilder& addComboboxOptions(const MenuBuilder::SubmenuPair& combo);

private:
  ImVec2                      m_buttons_size { 150, 25 };
  std::span<std::string_view> m_options;
  std::vector<CallbackPair>   m_popup_options;
  OptionsMap                  m_submenus;
  OptionsMap                  m_combos;
};

}  // namespace Screen::MenuBuilder

#endif  //OPENCV_IMGUI_SFML_INCLUDE_SCREEN_MENU_H
