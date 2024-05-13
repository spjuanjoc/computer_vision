/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-10
 */

#ifndef HELLO_OPENCV_INCLUDE_1_TRACKBAR_H
#define HELLO_OPENCV_INCLUDE_1_TRACKBAR_H

#include <fmt/core.h>

#include <opencv2/opencv.hpp>

void
showTrackbar()
{
  const int               slider_max = 100;
  static cv::VideoCapture capture("share/videos/perfect-sp.avi");
  static cv::Mat          frame;

  cv::namedWindow("Video track", cv::WINDOW_NORMAL);
  cv::resizeWindow("Video track", 720, 640);
  capture.set(cv::CAP_PROP_FPS, 60);
  auto frames = capture.get(cv::CAP_PROP_FRAME_COUNT);

  if (!capture.isOpened())
  {
    fmt::println(stderr, "The capture could not be open");
  }

  cv::createTrackbar(
    "Current frame",
    "Video track",
    nullptr,
    frames,
    [](int value, void*)
    {
      fmt::println("current frame: {}", value);
      capture.set(cv::CAP_PROP_POS_FRAMES, value);
    });

  for (;;)
  {
    capture.read(frame);

    if (frame.empty())
    {
      fmt::println(stderr, "Blank frame grabbed");
      //      break;
    }

    imshow("Video track", frame);

    if (cv::waitKey(5) >= 0)
      break;
  }
}

#endif  //

