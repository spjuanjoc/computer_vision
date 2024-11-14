/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-11-13
 */

#include "Screen/MenuBuilder2.h"

#include "Screen/Components/Constants.h"

namespace Screen::Menu
{

void
MenuBuilder2::draw(const std::string_view name)
{
  ImGui::SetNextWindowSize(Components::MENU_WINDOW_SIZE);
  ImGui::SetNextWindowPos(Components::MENU_WINDOW_POS);

  ImGui::Begin("Menu window");
  if (ImGui::CollapsingHeader(name.data(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    drawOptions(name);
  }
  ImGui::End();
}

void
MenuBuilder2::drawOptions(const std::string_view name)
{
  const auto& options = m_options[name.data()];

  for (const auto& option : options)
  {
    if (option.is_submenu)
    {
      drawSubmenu(option);
    }
    else
    {
      drawItem(option);
    }
  }

  runCallbacks(name);
}

void
MenuBuilder2::drawCombobox(const std::string_view name, size_t& option_index)
{
  const auto& options             = m_combos[name.data()];
  const auto& combo_preview_value = options[option_index].name;

  if (ImGui::BeginCombo(name.data(), combo_preview_value.data(), ImGuiComboFlags_WidthFitPreview))
  {
    for (size_t n = 0; n < options.size(); ++n)
    {
      const bool is_selected = (option_index == n);

      if (ImGui::Selectable(options[n].name.data(), is_selected))
        option_index = n;

      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  }
}

void
MenuBuilder2::addCombobox(const MenuBuilder2::OptionPair& combo, size_t& option_index)
{
  addComboboxOptions(combo);
  drawCombobox(combo.first, option_index);
}

void
MenuBuilder2::setButtonsSize(const ImVec2& size)
{
  m_buttons_size = size;
}

MenuBuilder2&
MenuBuilder2::addOptions(const MenuBuilder2::OptionPair& menu)
{
  const auto& [name, options] = menu;

  m_options[name] = options;

  return *this;
}

MenuBuilder2&
MenuBuilder2::addSubmenu(const MenuBuilder2::OptionPair& menu)
{
  addOptions(menu);
  drawOptions(menu.first);

  return *this;
}

/*MenuBuilder2&
MenuBuilder2::addOptionAction(const CallbackPair& option)
{
  const auto& [name, callback] = option;
  m_option_actions[name] = callback;

  return *this;
}*/

MenuBuilder2&
MenuBuilder2::addComboboxOptions(const MenuBuilder2::OptionPair& combo)
{
  const auto& [name, options] = combo;
  m_combos[name]              = options;

  return *this;
}

void
MenuBuilder2::runCallbacks(const std::string_view name)
{
  const auto& options = m_options[name.data()];

  for (const auto& option : options)
  {
    if (option.is_selected & 1)
    {
      option.callback();
    }
  }
}

void
MenuBuilder2::drawSubmenu(const Option& option)
{
  if (ImGui::TreeNode(option.name.data()))
  {
    option.callback();
    ImGui::TreePop();
  }
}

void
MenuBuilder2::drawItem(const Option& option) const
{
  if (ImGui::Button(option.name.data(), m_buttons_size))
  {
    option.select();
  }
}

}  // namespace Screen::Menu
