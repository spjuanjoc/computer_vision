/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-15
 */

#ifndef SCREEN_MENUBUILDER_H
#define SCREEN_MENUBUILDER_H

#include <Core/Logging/Logger.h>

#include <imgui.h>
#include <span>

namespace cv
{
class Mat;
}

namespace Screen::Menu
{

class MenuBuilder;

void
buildMenu(const cv::Mat& mat_src, MenuBuilder& menu, bool& should_draw_src);

/**
*
*/
struct Option
{
  void select() const { ++is_selected; }

  std::string           name;
  std::function<void()> callback {};
  bool                  is_submenu { false };
  mutable std::uint32_t is_selected { 0 };
};

/**
*
*/
class MenuBuilder
{
public:
  using OptionPair = std::pair<std::string, std::span<Option>>;
  using OptionsMap = std::unordered_map<std::string, std::span<Option>>;

  void draw(std::string_view name);

  void drawOptions(std::string_view name);

  void addCombobox(const MenuBuilder::OptionPair& combo, size_t& option_index);

  void setButtonsSize(const ImVec2& size);

  MenuBuilder& addOptions(const MenuBuilder::OptionPair& menu);

  MenuBuilder& addSubmenu(const MenuBuilder::OptionPair& menu);

private:

  static void drawSubmenu(const Option& option);

  void runCallbacks(std::string_view name);

  void drawItem(const Option& option) const;

  void drawCombobox(std::string_view name, size_t& option_index);

  MenuBuilder& addComboboxOptions(const MenuBuilder::OptionPair& combo);

private:
  ImVec2      m_buttons_size { 150, 25 };
  OptionsMap m_options;
  OptionsMap m_combos;
};

}  // namespace Screen::MenuBuilder

#endif  //SCREEN_MENUBUILDER_H
