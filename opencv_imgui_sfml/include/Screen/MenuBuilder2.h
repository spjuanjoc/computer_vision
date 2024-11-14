/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-11-13
 */

#ifndef SCREEN_MENUBUILDER2_H
#define SCREEN_MENUBUILDER2_H

#include <Core/Logging/Logger.h>

#include <array>
#include <imgui.h>
#include <span>

namespace Screen::Menu
{

struct Option
{
  void select() const { ++is_selected; }

  std::string           name;
  std::function<void()> callback {};
  bool                  is_submenu { false };
  mutable std::uint32_t is_selected { 0 };
};

class MenuBuilder2
{
public:
  using OptionPair = std::pair<std::string, std::span<Option>>;
  using OptionsMap2 = std::unordered_map<std::string, std::span<Option>>;

  // using CallbackPair = std::pair<std::string_view, std::function<void()>>;
  // using OptionsMap   = std::unordered_map<std::string, std::span<std::string>>;
  // using ActionsMap   = std::unordered_map<std::string_view, std::function<void()>>;

  void draw(std::string_view name);

  void drawOptions(std::string_view name);

  void addCombobox(const MenuBuilder2::OptionPair& combo, size_t& option_index);

  void setButtonsSize(const ImVec2& size);

  MenuBuilder2& addOptions(const MenuBuilder2::OptionPair& menu);

  MenuBuilder2& addSubmenu(const MenuBuilder2::OptionPair& menu);

private:

  static void drawSubmenu(const Option& option);

  void runCallbacks(std::string_view name);

  void drawItem(const Option& option) const;

  void drawCombobox(std::string_view name, size_t& option_index);

  MenuBuilder2& addComboboxOptions(const MenuBuilder2::OptionPair& combo);

private:
  ImVec2                    m_buttons_size { 150, 25 };
  OptionsMap2                m_options;
  // std::vector<CallbackPair> m_popup_options;
  // ActionsMap                m_option_actions;
  // OptionsMap                m_submenus;
  OptionsMap2                m_combos;
};

}  // namespace Screen::MenuBuilder2

#endif  //SCREEN_MENUBUILDER2_H
