#include <fmt/core.h>

#include "ShowImage.h"

#include <opencv2/core.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

void
drawText(cv::Mat& image)
{
  constexpr auto text       = "Hello OpenCV";
  constexpr auto font_scale = 1;
  constexpr auto thickness  = 1;
  const auto     point      = cv::Point(20, 50);
  const auto     color      = cv::Scalar(255, 255, 255);

  putText(image, text, point, cv::FONT_HERSHEY_COMPLEX, font_scale, color, thickness, cv::LINE_AA);
}


int
main()
{
  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

  fmt::println("Built with OpenCV v:{}", CV_VERSION);

  cv::VideoCapture capture;
  cv::Mat          frame;

  showImage();
  cv::waitKey(0);

  capture.open(0);

  if (capture.isOpened())
  {
    fmt::println("Capture is open");

    for (;;)
    {
      capture.read(frame);

      if (frame.empty())
        break;

      drawText(frame);
      imshow("Hello OpenCV", frame);

      if (cv::waitKey(10) >= 0)
        break;
    }
  }
  else
  {
    fmt::println("No capture");
    frame = cv::Mat::zeros(480, 640, CV_8UC1);
    drawText(frame);
    imshow("Hello OpenCV", frame);
    cv::waitKey(0);
  }


  return 0;
}
