#include "HelloOpenCv/ShowImage.h"
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/highgui.hpp>

int main()
{
  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

  showImage();

  int key = cv::waitKey(0);

  return 0;
}
