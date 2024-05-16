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
#include "Screen/Menu.h"

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
  ImGuiWindowFlags    window_flags = ImGuiWindowFlags_AlwaysAutoResize;

  background.setWindow(main_window);
  start_window.setWindow(main_window);

  std::string          filename  = "share/images/lena.bmp";
  cv::Mat              cv_image  = cv::imread(filename, cv::IMREAD_UNCHANGED);
  sf::Image            image_src = cvMat2sfImage(cv_image);
  sf::Texture          texture_src;
  sf::Texture          texture_dst;
  int                  kernel_size = 1;
  constexpr const auto step        = 2;

  cv::Mat   mat       = sfImage2cvMat(image_src);
  sf::Image image_dst = cvMat2sfImage(applyMedianFilter(mat, kernel_size));

  texture_src.loadFromImage(image_src);
  texture_dst.loadFromImage(image_dst);

  while (main_window->isOpen())
  {
    program.poll();
    ImGui::SFML::Update(*main_window, delta_clock.restart());

    main_window->clear();
    background.draw();

    showAppMainMenuBar();
    drawMainMenu(window_flags);

    drawSrcImage(window_flags, texture_src);

    if (draw_median)
      drawMedian(window_flags, texture_dst, kernel_size, step, mat, image_dst);

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
