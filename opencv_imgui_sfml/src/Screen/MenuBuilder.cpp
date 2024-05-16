/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-16
 */

#include "Screen/MenuBuilder.h"


namespace Screen::Menu
{

void
MenuBuilder::draw(std::string_view name)
{
  if (ImGui::TreeNodeEx(name.data(), ImGuiTreeNodeFlags_DefaultOpen))
  {
    drawSubmenu(name);
    ImGui::TreePop();
  }
}

void
MenuBuilder::drawSubmenu(std::string_view name)
{
  const auto& options = m_submenus[name.data()];

  ImGui::BeginGroup();
  for (const auto& option: options)
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

MenuBuilder&
MenuBuilder::addPopupOption(const CallbackPair& option)
{
  m_popup_options.push_back(option);

  return *this;
}
void
MenuBuilder::addMenuOptions(const MenuBuilder::SubmenuPair& menu)
{
  auto& [name, options] = menu;
  m_submenus[name] = options;
}

void
MenuBuilder::setButtonsSize(const ImVec2& size)
{
  m_buttons_size = size;
}

}  // namespace Screen::MenuBuilder
