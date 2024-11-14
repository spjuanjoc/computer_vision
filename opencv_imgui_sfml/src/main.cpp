/**
 * @brief Defines the entry point which starts rendering the window, and polling the
 *        multimedia events.
 *
 * @author  spjuanjoc
 * @date    2021-10-12
*/

#include <Screen/MenuBuilder2.h>

#include "Core/Constants/Constants.h"
#include "Core/Events/EventsHandler.h"
#include "Core/Initialization/Arguments.h"
#include "Core/Initialization/Fonts.h"
#include "Core/Logging/Logger.h"
#include "ImageProcessing/Conversions.h"
#include "ImageProcessing/Drawing.h"
#include "ImageProcessing/Morphology/MorphologicalOperations.hpp"
#include "ImageProcessing/Preprocessing/ColorSpaces.hpp"
#include "ImageProcessing/Preprocessing/Enhancements.hpp"
#include "ImageProcessing/Preprocessing/GrayWorld.hpp"
#include "ImageProcessing/Video/LoadVideo.hpp"
#include "Screen/Components/Background.h"
#include "Screen/Components/StartWindow.h"
#include "Screen/MenuBuilder.h"

#include <future>

#include "bindings/imgui-SFML.h"
#include <ImageProcessing/Histogram/Histogram.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace Screen;
using namespace Screen::Components;
using namespace Screen::Menu;
using namespace Processing;
using namespace Processing::Preprocessing;
using namespace Processing::Enhancements;
using namespace Processing::Spaces;
using namespace Processing::Video;
using namespace Processing::Morphology;

void
buildMenu2(const cv::Mat& mat_src, MenuBuilder2& menu, bool& should_draw_src)
{
  const std::string  filename                  = "share/images/beach.png";
  const std::string  video                     = "share/videos/perfect-sp.avi";
  constexpr bool     is_submenu                = true;

  int                kernel_size               = 1;
  static std::size_t structuring_element_index = 0;
  static std::size_t image_type_index          = 0;

  auto do_nothing         = [&]() { ImGui::Text("nothing here, come back later"); };

  static std::vector<Option> options_video { {"Load video", do_nothing} };
  static std::vector<Option> structuring_elements {
    {"Rectangular", do_nothing},
    {"Cross shaped", do_nothing},
    {"Elliptical", do_nothing},
    {"Custom", do_nothing}
  };
  static std::vector<Option> image_types { {"Grayscale", do_nothing}, {"Binary", do_nothing} };
  static std::vector<Option> options_morpho {
    {"Dilation", do_nothing},
    {"Erosion", do_nothing},
    {"Opening", do_nothing},
    {"Closing", do_nothing},
    {"Gradient", do_nothing}
  };

  // Callbacks definitions
  // Main
  auto on_raw        = [&]() { createCvMat(true); };
  auto on_load       = [&]() { should_draw_src = true; };
  auto on_video      = [&]() { menu.addSubmenu({"Video menu", options_video}); };
  auto on_preprocess = [&]() { menu.addSubmenu({"Preprocessing menu", options_video}); };
  auto on_morphology = [&]()
  {
    menu.addCombobox({ "Structuring Element", structuring_elements }, structuring_element_index);
    menu.addCombobox({"Image type", image_types}, image_type_index);
    menu.addSubmenu({"Morphology menu", options_morpho});
  };
  auto on_histogram = [&]() { menu.addSubmenu({"Histogram menu", options_video}); };

  static std::vector<Option> options_main
  { {"Raw image", on_raw},
    {"Load image", on_load},
    {"Video", on_video, is_submenu},
    {"Preprocessing", on_preprocess, is_submenu},
    {"Morphology", on_morphology, is_submenu},
    {"Histogram", on_histogram, is_submenu}
  };

  menu.addOptions({ "Main menu", options_main });

}

void
buildMenu(const cv::Mat& mat_src, MenuBuilder& menu, bool& should_draw_src)
{
  const std::string filename    = "share/images/beach.png";
  const std::string video       = "share/videos/perfect-sp.avi";
  int               kernel_size = 1;

  static std::array<std::string, 6> options_main              = { "Raw image", "Load image", "Video", "Preprocessing", "Morphology", "Histogram" };
  static std::array<std::string, 1> options_video             = { "Load video" };
  static std::array<std::string, 3> options_preprocess        = { "Grayworld", "Enhancements", "Color spaces" };
  static std::array<std::string, 5> options_enhance           = { "Convolution", "Laplace filter", "Median blur", "Sobel filter", "Thresholding" };
  static std::array<std::string, 5> options_spaces            = { "Gray space", "HLS", "HSV", "CIE lab", /*"CIE luv",*/ "YUV (YCrCb)" };
  static std::array<std::string, 5> options_morpho            = { "Dilation", "Erosion", "Opening", "Closing", "Gradient" };
  static std::array<std::string, 2> options_histogram         = { "Grayscale", "Color" };
  static std::array<std::string, 4> structuring_elements      = { "Rectangular", "Cross shaped", "Elliptical", "Custom" };
  static std::array<std::string, 2> image_types               = { "Grayscale", "Binary" };
  static std::size_t                structuring_element_index = 0;
  static std::size_t                image_type_index          = 0;

  // Callbacks definitions
  // Main
  auto on_raw        = [&]() { createCvMat(true); };
  auto on_load       = [&]() { should_draw_src = true; };
  auto on_video      = [&]() { menu.drawSubmenu("Video menu"); };
  auto on_preprocess = [&]() { menu.drawSubmenu("Preprocessing menu"); };
  auto on_morphology = [&]()
  {
    menu.drawCombobox("Structuring Element", structuring_element_index);
    menu.drawCombobox("Image type", image_type_index);
    menu.drawSubmenu("Morphology menu");
  };
  auto on_histogram = [&]() { menu.drawSubmenu("Histogram menu"); };

  // Video
  auto on_load_video = [&]() { auto video_thread = std::async([&]() { loadFromFile(video, true); }); };

  // Preprocessing
  auto on_grayworld   = [&]() { grayWorld(mat_src, true); };
  auto on_enhancement = [&]() { menu.drawSubmenu("Enhancements menu"); };

  // Enhancements
  auto on_convolution = [&]() { convolution(mat_src, true); };
  auto on_laplace     = [&]() { laplace(mat_src, true); };
  auto on_median      = [&]() { medianBlur(mat_src, kernel_size, true); };
  auto on_sobel       = [&]() { sobel(mat_src, true); };
  auto on_threshold   = [&]() { thresholding(mat_src, true); };

  // Color spaces
  auto on_spaces = [&]() { menu.drawSubmenu("Color spaces menu"); };
  auto on_gray   = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2GRAY); };
  auto on_hls    = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2HLS); };
  auto on_hsv    = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2HSV); };
  auto on_cielab = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2Lab); };
  //  auto on_cieluv    = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2Luv); };
  auto on_ycrcb = [&]() { toColorSpace(mat_src, true, cv::COLOR_RGB2YCrCb); };

  // Morphology
  auto on_dilation = [&]() { dilation(mat_src, true, structuring_element_index, image_type_index); };
  auto on_erosion  = [&]() { erosion(mat_src, true, structuring_element_index, image_type_index); };
  auto on_open
    = [&]() { morphology(mat_src, true, structuring_element_index, image_type_index, cv::MorphTypes::MORPH_OPEN); };
  auto on_close
    = [&]() { morphology(mat_src, true, structuring_element_index, image_type_index, cv::MorphTypes::MORPH_CLOSE); };
  auto on_gradient
    = [&]() { morphology(mat_src, true, structuring_element_index, image_type_index, cv::MorphTypes::MORPH_GRADIENT); };

  // Histogram
  auto on_gray_histogram  = [&]() { grayHistogram(mat_src, true); };
  auto on_color_histogram = [&]() { colorHistogram(mat_src, true); };
  auto do_nothing         = [&]() { ImGui::Text("nothing here, come back later"); };

  menu.addMenuOptions({ "Main menu", options_main })
    .addPopupOption({ "Raw image", on_raw })
    .addPopupOption({ "Load image", on_load })
    .addPopupOption({ "Video", on_video })
    .addPopupOption({ "Preprocessing", on_preprocess })
    .addPopupOption({ "Morphology", on_morphology })
    .addPopupOption({ "Histogram", on_histogram });

  menu.addMenuOptions({"Video menu", options_video})
    .addPopupOption({"Load video", on_load_video});

  menu.addMenuOptions({ "Preprocessing menu", options_preprocess })
    .addPopupOption({ "Grayworld", on_grayworld })
    .addPopupOption({ "Enhancements", on_enhancement })
    .addPopupOption({ "Color spaces", on_spaces });

  menu.addMenuOptions({ "Enhancements menu", options_enhance })
    .addPopupOption({ "Convolution", on_convolution })
    .addPopupOption({ "Laplace filter", on_laplace })
    .addPopupOption({ "Median blur", on_median })
    .addPopupOption({ "Sobel filter", on_sobel })
    .addPopupOption({ "Thresholding", on_threshold });

  menu.addMenuOptions({ "Color spaces menu", options_spaces })
    .addPopupOption({ "Gray space", on_gray })
    .addPopupOption({ "HLS", on_hls })
    .addPopupOption({ "HSV", on_hsv })
    .addPopupOption({ "CIE lab", on_cielab })
//    .addPopupOption({ "CIE lub", on_cieluv })
    .addPopupOption({ "YUV (YCrCb)", on_ycrcb });

  menu.addMenuOptions({ "Morphology menu", options_morpho })
    .addComboboxOptions({"Structuring Element", structuring_elements})
    .addComboboxOptions({"Image type", image_types })
    .addPopupOption({"Dilation", on_dilation})
    .addPopupOption({"Erosion", on_erosion})
    .addPopupOption({"Opening", on_open})
    .addPopupOption({"Closing", on_close})
    .addPopupOption({"Gradient", on_gradient});

  menu.addMenuOptions({ "Histogram menu", options_histogram })
    .addPopupOption({ "Grayscale", on_gray_histogram })
    .addPopupOption({ "Color", on_color_histogram });
}

void
runMainLoop(const std::shared_ptr<sf::RenderWindow>& main_window, [[maybe_unused]] const Core::Arguments& args)
{
  sf::Clock           delta_clock;
  Core::EventsHandler program { main_window };
  Background          background;
  StartWindow         start_window;
  sf::Texture         texture_src;
  sf::Texture         texture_dst;
  std::string         filename        = "share/images/beach.png";
  bool                should_draw_src = true;
  cv::Mat             mat_src         = cv::imread(filename, cv::IMREAD_UNCHANGED);
  sf::Image           image_src       = cvMat2sfImage(mat_src);

  MenuBuilder2 menu;
  buildMenu2(mat_src, menu, should_draw_src);

  texture_src.loadFromImage(image_src);
  texture_dst.loadFromImage(image_src);
  background.setWindow(main_window);
  start_window.setWindow(main_window);

  while (main_window->isOpen())
  {
    program.poll();
    ImGui::SFML::Update(*main_window, delta_clock.restart());

    main_window->clear();
    background.draw();

    menu.draw("Main menu");

    if (should_draw_src)
      drawSrcImage(texture_src, should_draw_src);

    ImGui::SFML::Render(*main_window);
    main_window->display();
  }
}

int
main(int argc, const char* argv[])
{
  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

  const auto args = Core::parseArguments(argc, argv);
  //  Logger::SpdLogger::get().enableFileSink();
  Logger::SpdLogger::get().setLevel(args.level);
  Logger::Info(">>main");

  auto mode = args.is_fullscreen ? sf::VideoMode().getFullscreenModes().at(0) : sf::VideoMode(args.width, args.height);
  const auto main_window = std::make_shared<sf::RenderWindow>(mode, WINDOW_TITLE);

  main_window->setFramerateLimit(args.frame_rate);
  [[maybe_unused]] bool const isInit = ImGui::SFML::Init(*main_window);
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  Core::Initialization::loadFonts();
  [[maybe_unused]] bool const isFont = ImGui::SFML::UpdateFontTexture();
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  ImGui::GetIO().FontGlobalScale = args.scale;
//  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  runMainLoop(main_window, args);

  ImGui::SFML::Shutdown();
  Logger::Info("<<main");

  return 0;
}
