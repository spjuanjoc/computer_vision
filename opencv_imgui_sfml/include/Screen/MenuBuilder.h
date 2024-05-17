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

  void draw(std::string_view name);

  void drawSubmenu(std::string_view name);

  MenuBuilder& addPopupOption(const CallbackPair& option);

  MenuBuilder& addMenuOptions(const MenuBuilder::SubmenuPair& menu);

  void setButtonsSize(const ImVec2& size);

private:
  ImVec2 m_buttons_size{ 150, 25 };
  std::span<std::string_view> m_options;
  std::vector<CallbackPair> m_popup_options;
  std::unordered_map<std::string, std::span<std::string>>  m_submenus;
};
/*

static void
ShowExampleMenuFile()
{
  ImGui::MenuItem("App MenuBuilder", nullptr, false, false);
  if (ImGui::MenuItem("New")) {}
  if (ImGui::MenuItem("Open", "Ctrl+O")) {}
  if (ImGui::BeginMenu("Open Recent"))
  {
    ImGui::MenuItem("fish_hat.c");
    ImGui::MenuItem("fish_hat.inl");
    ImGui::MenuItem("fish_hat.h");
    if (ImGui::BeginMenu("More.."))
    {
      ImGui::MenuItem("Hello");
      ImGui::MenuItem("Sailor");
      if (ImGui::BeginMenu("Recurse.."))
      {
        ShowExampleMenuFile();
        ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenu();
  }
  if (ImGui::MenuItem("Save", "Ctrl+S")) {}
  if (ImGui::MenuItem("Save As..")) {}

  ImGui::Separator();
  if (ImGui::BeginMenu("Options"))
  {
    static bool enabled = true;
    ImGui::MenuItem("Enabled", "", &enabled);
    ImGui::BeginChild("child", ImVec2(0, 60), ImGuiChildFlags_Border);
    for (int i = 0; i < 10; i++)
      ImGui::Text("Scrolling Text %d", i);
    ImGui::EndChild();
    static float f = 0.5f;
    static int   n = 0;
    ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
    ImGui::InputFloat("Input", &f, 0.1f);
    ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Colors"))
  {
    float sz = ImGui::GetTextLineHeight();
    for (int i = 0; i < ImGuiCol_COUNT; i++)
    {
      const char* name = ImGui::GetStyleColorName((ImGuiCol) i);
      ImVec2      p    = ImGui::GetCursorScreenPos();
      ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol) i));
      ImGui::Dummy(ImVec2(sz, sz));
      ImGui::SameLine();
      ImGui::MenuItem(name);
    }
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Options"))  // <-- Append!
  {
    static bool b = true;
    ImGui::Checkbox("SomeOption", &b);
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Disabled", false))  // Disabled
  {
    IM_ASSERT(0);
  }
  if (ImGui::MenuItem("Checked", NULL, true)) {}
  ImGui::Separator();
  if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

static void
showAppMainMenuBar()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      ShowExampleMenuFile();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
      if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
      ImGui::Separator();
      if (ImGui::MenuItem("Cut", "CTRL+X")) {}
      if (ImGui::MenuItem("Copy", "CTRL+C")) {}
      if (ImGui::MenuItem("Paste", "CTRL+V")) {}
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
*/

}  // namespace Screen::MenuBuilder

#endif  //OPENCV_IMGUI_SFML_INCLUDE_SCREEN_MENU_H
