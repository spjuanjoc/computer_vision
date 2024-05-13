#include "0_CreateMat/CreateMatrix.h"
#include "1_Video/Load.h"
#include "1_Video/TrackBar.h"
#include "HelloOpenCv/ShowImage.h"
#include "HelloOpenCv/SobelFilter.h"

#include <string>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/highgui.hpp>

void
parseOptions(const std::string& option)
{
  int value = std::stoi(option);

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
    fmt::println("\t0. End");
    fmt::print("\nSelect an option: ");

    std::cin >> option;

    parseOptions(option);
    cv::waitKey(0);
    cv::destroyAllWindows();
  }

  return 0;
}
