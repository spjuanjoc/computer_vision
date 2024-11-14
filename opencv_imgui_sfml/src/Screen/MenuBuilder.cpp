/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-16
 */

#include "Screen/MenuBuilder.h"

#include "Screen/Components/Constants.h"
namespace Screen::Menu
{

void
MenuBuilder::draw(const std::string_view name)
{
  ImGui::SetNextWindowSize(Components::MENU_WINDOW_SIZE);
  ImGui::SetNextWindowPos(Components::MENU_WINDOW_POS);

  ImGui::Begin("Menu");

  if (ImGui::TreeNodeEx(name.data(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    drawSubmenu(name);
    ImGui::TreePop();
  }

  ImGui::End();
}

void
MenuBuilder::drawSubmenu(const std::string_view name)
{
  const auto& options = m_submenus[name.data()];

  ImGui::BeginGroup();
  for (const auto& option : options)
  {
    if (ImGui::Button(option.data(), m_buttons_size))
    {
      ImGui::OpenPopup(option.data());
    }
  }
  ImGui::EndGroup();

  for (auto& [pop_name, callback] : m_popup_options)
  {
    if (ImGui::BeginPopup(pop_name.data()))
    {
      callback();
      ImGui::EndPopup();
    }
  }
}

void
MenuBuilder::drawCombobox(const std::string_view name, size_t& option_index)
{
  const auto& options             = m_combos[name.data()];
  const auto& combo_preview_value = options[option_index];

  if (ImGui::BeginCombo(name.data(), combo_preview_value.data(), ImGuiComboFlags_WidthFitPreview))
  {
    for (size_t n = 0; n < options.size(); ++n)
    {
      const bool is_selected = (option_index == n);

      if (ImGui::Selectable(options[n].data(), is_selected))
        option_index = n;

      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  }
}

void
MenuBuilder::setButtonsSize(const ImVec2& size)
{
  m_buttons_size = size;
}

MenuBuilder&
MenuBuilder::addMenuOptions(const MenuBuilder::SubmenuPair& menu)
{
  const auto& [name, options] = menu;
  m_submenus[name]            = options;

  return *this;
}

MenuBuilder&
MenuBuilder::addPopupOption(const CallbackPair& option)
{
  m_popup_options.push_back(option);

  return *this;
}

MenuBuilder&
MenuBuilder::addComboboxOptions(const MenuBuilder::SubmenuPair& combo)
{
  const auto& [name, options] = combo;
  m_combos[name]              = options;

  return *this;
}

}  // namespace Screen::Menu
