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
#include "ImageProcessing/Preprocessing.hpp"
#include "ImageProcessing/Enhancements.hpp"
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
using namespace Processing::Preprocessing;
using namespace Processing::Enhancements;

void
runMainLoop(const std::shared_ptr<sf::RenderWindow>& main_window, [[maybe_unused]] const Core::Arguments& args)
{
  sf::Clock           delta_clock;
  Core::EventsHandler program { main_window };
  Background          background;
  StartWindow         start_window;
  sf::Texture         texture_src;
  sf::Texture         texture_dst;
  std::string         filename        = "share/images/lena.bmp";
  cv::Mat             mat_src         = cv::imread(filename, cv::IMREAD_UNCHANGED);
  sf::Image           image_src       = cvMat2sfImage(mat_src);
  bool                should_draw_src = true;
  int                 kernel_size     = 1;

  Screen::Menu::MenuBuilder  menu;
  std::array<std::string, 4> options_main       = { "Raw image", "Load image", "Video", "Preprocessing" };
  std::array<std::string, 3> options_preprocess = { "Grayworld", "Enhancements", "Color spaces" };
  std::array<std::string, 5> options_enhance    = { "Convolution", "Laplace filter", "Median blur", "Sobel filter", "Thresholding" };

  // Callbacks definition
  auto on_raw         = [&]() { createCvMat(true); };
  auto on_load        = [&]() { should_draw_src = true; };
  auto on_preprocess  = [&]() { menu.drawSubmenu("Preprocessing menu"); };
  auto on_grayworld   = [&]() { grayWorld(mat_src, true); };
  auto on_enhancement = [&]() { menu.drawSubmenu("Enhancements menu"); };

  auto on_convolution = [&]() { convolution(mat_src, true); };
  auto on_laplace     = [&]() { laplace(mat_src, true); };
  auto on_median      = [&]() { medianBlur(mat_src, kernel_size, true); };
  auto on_sobel      = [&]() { sobel(mat_src, true); };
  auto on_threshold      = [&]() { thresholding(mat_src, true); };

  auto do_nothing = [&]() { ImGui::Text("nothing"); };

  menu.addMenuOptions({ "Main menu", options_main })
    .addPopupOption({ "Raw image", on_raw })
    .addPopupOption({ "Load image", on_load })
    .addPopupOption({ "Video", do_nothing })
    .addPopupOption({ "Preprocessing", on_preprocess });

  menu.addMenuOptions({ "Preprocessing menu", options_preprocess })
    .addPopupOption({ "Grayworld", on_grayworld })
    .addPopupOption({ "Enhancements", on_enhancement })
    .addPopupOption({ "Color spaces", do_nothing });

  menu.addMenuOptions({ "Enhancements menu", options_enhance })
    .addPopupOption({ "Convolution", on_convolution })
    .addPopupOption({ "Laplace filter", on_laplace })
    .addPopupOption({ "Median blur", on_median })
    .addPopupOption({ "Sobel filter", on_sobel })
    .addPopupOption({ "Thresholding", on_threshold });


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

//    showAppMainMenuBar();
//    drawMainMenu();

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
