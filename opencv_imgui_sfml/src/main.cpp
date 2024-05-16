/**
 * @brief Defines the entry point which starts rendering the window, and polling the
 *        multimedia events.
 *
 * @author  spjuanjoc
 * @date    2021-10-12
*/

#include "Core/Constants/Constants.h"
#include "Core/Events/EventsHandler.h"
#include "Core/Initialization/Arguments.h"
#include "Core/Initialization/Fonts.h"
#include "Core/Logging/Logger.h"
#include "ImageProcessing/Conversions.h"
#include "ImageProcessing/Drawing.h"
#include "Screen/Components/Background.h"
#include "Screen/Components/StartWindow.h"
#include "Screen/MenuBuilder.h"

#include "bindings/imgui-SFML.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace Screen;
using namespace Screen::Components;
using namespace Screen::Menu;
using namespace Processing;

void
runMainLoop(const std::shared_ptr<sf::RenderWindow>& main_window, [[maybe_unused]] const Core::Arguments& args)
{
  sf::Clock           delta_clock;
  Core::EventsHandler program { main_window };
  Background          background;
  StartWindow         start_window;
  sf::Texture         texture_src;
  sf::Texture         texture_dst;
  std::string         filename        = "share/images/spheres.bmp";
  cv::Mat             mat_src         = cv::imread(filename, cv::IMREAD_UNCHANGED);
  sf::Image           image_src       = cvMat2sfImage(mat_src);
  bool                should_draw_src = true;
  int                 kernel_size     = 1;
  Screen::Menu::MenuBuilder  menu;
  std::array<std::string, 4> options_main       = { "Raw images", "Load image", "Video", "Preprocessing" };
  std::array<std::string, 3> options_preprocess = { "Grayworld", "Enhancements", "Color space" };
  std::array<std::string, 5> options_enhance = { "Convolution", "Laplace filter", "Median blur", "Sobel filter", "Thresholding" };

  auto on_button1 = [&]() { menu.drawSubmenu("Preprocessing menu"); };
  auto on_button2 = [&]() { menu.drawSubmenu("Enhancements menu"); };
  auto hello_cb   = []() { ImGui::Text("hello"); };
  auto on_median  = [&]()
  {
    should_draw_median = true;
    if (should_draw_median)
      drawMedian(mat_src, kernel_size, texture_dst, should_draw_median);
  };

  menu.addMenuOptions({ "Main menu", options_main });
  menu.addMenuOptions({ "Preprocessing menu", options_preprocess });
  menu.addMenuOptions({ "Enhancements menu", options_enhance });

  menu.addPopupOption({ "Preprocessing", on_button1 })
    .addPopupOption({ "Show image", hello_cb })
    .addPopupOption({ "Grayworld", hello_cb })
    .addPopupOption({ "Enhancements", on_button2 })
    .addPopupOption({ "Median blur", on_median });

  //  cv::Mat   mat       = sfImage2cvMat(image_src);
//  sf::Image image_dst = cvMat2sfImage(applyMedianFilter(mat, kernel_size));

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

//    menu.showOptionPopup("Option Preprocessing", "", hello_cb);
//    showAppMainMenuBar();
//    drawMainMenu();
//
    if (should_draw_src)
      drawSrcImage(texture_src, should_draw_src);
//
//    if (should_draw_median)
//      drawMedian(mat_src, kernel_size, texture_dst, should_draw_median);

    ImGui::SFML::Render(*main_window);
    main_window->display();
  }
}

int
main(int argc, const char* argv[])
{
  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

  auto args = Core::parseArguments(argc, argv);
  //  Logger::SpdLogger::get().enableFileSink();
  Logger::SpdLogger::get().setLevel(args.level);
  Logger::Info(">>main");

  auto mode = args.is_fullscreen ? sf::VideoMode().getFullscreenModes().at(0) : sf::VideoMode(args.width, args.height);
  auto main_window = std::make_shared<sf::RenderWindow>(mode, WINDOW_TITLE);

  main_window->setFramerateLimit(args.frame_rate);
  [[maybe_unused]] bool const isInit = ImGui::SFML::Init(*main_window);
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  Core::Initialization::loadFonts();
  [[maybe_unused]] bool const isFont = ImGui::SFML::UpdateFontTexture();
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  ImGui::GetIO().FontGlobalScale = args.scale;

  runMainLoop(main_window, args);

  ImGui::SFML::Shutdown();
  Logger::Info("<<main");

  return 0;
}
