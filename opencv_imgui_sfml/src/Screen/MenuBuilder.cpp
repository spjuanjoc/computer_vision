/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-16
 */

#include "Screen/MenuBuilder.h"

#include <ImageProcessing/Drawing.h>

#include "Screen/Components/Constants.h"

#include <future>

#include <ImageProcessing/Histogram/Histogram.hpp>
#include <ImageProcessing/Morphology/MorphologicalOperations.hpp>
#include <ImageProcessing/Preprocessing/ColorSpaces.hpp>
#include <ImageProcessing/Preprocessing/Enhancements.hpp>
#include <ImageProcessing/Preprocessing/GrayWorld.hpp>
#include <ImageProcessing/Video/LoadVideo.hpp>

using namespace Screen;
using namespace Screen::Components;
using namespace Screen::Menu;
using namespace Processing;
using namespace Processing::Preprocessing;
using namespace Processing::Enhancements;
using namespace Processing::Spaces;
using namespace Processing::Video;
using namespace Processing::Morphology;

namespace Screen::Menu
{

void
buildMenu(const cv::Mat& mat_src, MenuBuilder& menu, bool& should_draw_src)
{
  const std::string filename   = "share/images/beach.png";
  const std::string video      = "share/videos/perfect-sp.avi";
  constexpr bool    is_submenu = true;

  static int         kernel_size               = 1;
  static std::size_t structuring_element_index = 0;
  static std::size_t image_type_index          = 0;

  [[maybe_unused]] auto do_nothing         = [&]() { ImGui::Text("nothing here, come back later"); };

  // Options declaration
  static std::vector<Option> options_video;
  static std::vector<Option> structuring_elements;
  static std::vector<Option> options_preprocess;
  static std::vector<Option> image_types;
  static std::vector<Option> options_morpho;
  static std::vector<Option> options_enhance;
  static std::vector<Option> options_spaces;
  static std::vector<Option> options_histogram;
  static std::vector<Option> options_main;

  // Callbacks definitions
  // Main
  auto on_raw        = [&]() { Processing::createCvMat(true); };
  auto on_load       = [&]() { should_draw_src = true; };
  auto on_video      = [&]() { menu.addSubmenu({ "Video menu", options_video }); };
  auto on_preprocess = [&]() { menu.addSubmenu({ "Preprocessing menu", options_preprocess }); };
  auto on_histogram  = [&]() { menu.addSubmenu({ "Histogram menu", options_histogram }); };
  auto on_morphology = [&]()
  {
    menu.addCombobox({ "Structuring Element", structuring_elements }, structuring_element_index);
    menu.addCombobox({ "Image type", image_types }, image_type_index);
    menu.addSubmenu({ "Morphology menu", options_morpho });
  };

  // Video
  auto on_load_video = [&]() { auto video_thread = std::async([&]() { loadFromFile(video, true); }); };

  // Preprocessing
  auto on_grayworld   = [&]() { grayWorld(mat_src, true); };
  auto on_enhancement = [&]() { menu.addSubmenu({ "Enhancements menu", options_enhance }); };
  auto on_spaces      = [&]() { menu.addSubmenu({ "Color spaces menu", options_spaces }); };

  // Enhancements
  auto on_convolution = [&]() { convolution(mat_src, true); };
  auto on_laplace     = [&]() { laplace(mat_src, true); };
  auto on_median      = [&]() { medianBlur(mat_src, kernel_size, true); };
  auto on_sobel       = [&]() { sobel(mat_src, true); };
  auto on_threshold   = [&]() { thresholding(mat_src, true); };

  // Color spaces
  auto on_gray   = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2GRAY); };
  auto on_hls    = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2HLS); };
  auto on_hsv    = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2HSV); };
  auto on_cielab = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2Lab); };
  //  auto on_cieluv    = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2Luv); };
  auto on_ycrcb = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2YCrCb); };

  // Morphology
  auto on_dilation = [&]() { dilation(mat_src, true, structuring_element_index, image_type_index); };
  auto on_erosion  = [&]() { erosion(mat_src, true, structuring_element_index, image_type_index); };
  auto on_open     = [&]() { morphology(mat_src, true, structuring_element_index, image_type_index, cv::MorphTypes::MORPH_OPEN); };
  auto on_close    = [&]() { morphology(mat_src, true, structuring_element_index, image_type_index, cv::MorphTypes::MORPH_CLOSE); };
  auto on_gradient = [&]() { morphology(mat_src, true, structuring_element_index, image_type_index, cv::MorphTypes::MORPH_GRADIENT); };

  // Histogram
  auto on_gray_histogram  = [&]() { grayHistogram(mat_src, true); };
  auto on_color_histogram = [&]() { colorHistogram(mat_src, true); };

  // Options definition
  structuring_elements = { { "Rectangular" }, { "Cross shaped" }, { "Elliptical" }, { "Custom" } };
  image_types          = { { "Grayscale" }, { "Binary" } };
  options_video        = { { "Load video", on_load_video } };
  options_morpho       = { { "Dilation", on_dilation },
                           { "Erosion", on_erosion },
                           { "Opening", on_open },
                           { "Closing", on_close },
                           { "Gradient", on_gradient } };
  options_enhance      = { { "Convolution", on_convolution },
                           { "Laplace filter", on_laplace },
                           { "Median blur", on_median },
                           { "Sobel filter", on_sobel },
                           { "Thresholding", on_threshold } };
  options_preprocess   = { { "Grayworld", on_grayworld },
                           { "Enhancements", on_enhancement, is_submenu },
                           { "Color spaces", on_spaces, is_submenu } };
  options_spaces       = { { "Gray space", on_gray },
                           { "HLS", on_hls },
                           { "HSV", on_hsv },
                           { "CIE lab", on_cielab },
                           { "YUV (YCrCb)", on_ycrcb } };
  options_histogram    = { { "Grayscale", on_gray_histogram }, { "Color", on_color_histogram } };

  options_main = { { "Raw image", on_raw },
                   { "Load image", on_load },
                   { "Video", on_video, is_submenu },
                   { "Preprocessing", on_preprocess, is_submenu },
                   { "Morphology", on_morphology, is_submenu },
                   { "Histogram", on_histogram, is_submenu } };

  menu.addOptions({ "Main menu", options_main });
}

void
MenuBuilder::draw(const std::string_view name)
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
MenuBuilder::drawOptions(const std::string_view name)
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
MenuBuilder::drawCombobox(const std::string_view name, size_t& option_index)
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
MenuBuilder::addCombobox(const MenuBuilder::OptionPair& combo, size_t& option_index)
{
  addComboboxOptions(combo);
  drawCombobox(combo.first, option_index);
}

void
MenuBuilder::setButtonsSize(const ImVec2& size)
{
  m_buttons_size = size;
}

MenuBuilder&
MenuBuilder::addOptions(const MenuBuilder::OptionPair& menu)
{
  const auto& [name, options] = menu;

  m_options[name] = options;

  return *this;
}

MenuBuilder&
MenuBuilder::addSubmenu(const MenuBuilder::OptionPair& menu)
{
  addOptions(menu);
  drawOptions(menu.first);

  return *this;
}

MenuBuilder&
MenuBuilder::addComboboxOptions(const MenuBuilder::OptionPair& combo)
{
  const auto& [name, options] = combo;
  m_combos[name]              = options;

  return *this;
}

void
MenuBuilder::runCallbacks(const std::string_view name)
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
MenuBuilder::drawSubmenu(const Option& option)
{
  if (ImGui::TreeNode(option.name.data()))
  {
    option.callback();
    ImGui::TreePop();
  }
}

void
MenuBuilder::drawItem(const Option& option) const
{
  if (ImGui::Button(option.name.data(), m_buttons_size))
  {
    option.select();
  }
}

}  // namespace Screen::Menu
