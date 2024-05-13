#include "0_CreateMat/CreateMatrix.h"
#include "1_ShowImage/ShowImage.h"
#include "1_ShowImage/SobelFilter.h"
#include "2_Video/Load.h"
#include "2_Video/TrackBar.h"
#include "3_GrayWorld/Grayworld.h"

#include <string>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/highgui.hpp>

void
parseOptions(const std::string& option)
{
  std::int32_t value = 0;

  try
  {
    value = std::stoi(option);
  }catch (const std::exception& exception){
    fmt::println(stderr, "Unrecognized option '{}'", option, exception.what());
    value = 0;
  }

  switch (value)
  {
    case 0:
      fmt::println("End");
      break;
    case 1:
      showImage();
      break;
    case 2:
      showSobel();
      break;
    case 3:
      createMatrix();
      break;
    case 4:
      loadFromFile();
      break;
    case 5:
      showTrackbar();
      break;
    case 6:
      grayWorld();
      break;
    default:
      fmt::println("Invalid option");
      break;
  }
}

int
main()
{
  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

  std::string option;

  while (option != "0")
  {
    fmt::println("Options:");
    fmt::println("\t1. Show image");
    fmt::println("\t2. Show Sobel filter");
    fmt::println("\t3. Create a cv::Mat");
    fmt::println("\t4. Load a video");
    fmt::println("\t5. Add a trackbar to a video");
    fmt::println("\t6. Grayworld");
    fmt::println("\t0. End");
    fmt::print("\nSelect an option: ");

    std::cin >> option;

    parseOptions(option);
    cv::waitKey(0);
    cv::destroyAllWindows();
  }

  return 0;
}
