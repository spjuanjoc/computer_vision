#include <fmt/core.h>

#include "Menu.h"

#include <string>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/highgui.hpp>

int
main()
{
  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

  std::string option;

  while (option != "-1")
  {
    fmt::println("Options:");
    option = showMenu(menu_main);
    parseOptionsMain(option);
    cv::waitKey(0);
    cv::destroyAllWindows();
  }

  return 0;
}
