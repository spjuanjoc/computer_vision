/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-10
 */

#ifndef HELLO_OPENCV_INCLUDE_1_VIDEO_LOAD_H
#define HELLO_OPENCV_INCLUDE_1_VIDEO_LOAD_H

#include <iostream>

void
loadFromFile()
{
  cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);

  cv::VideoCapture capture("share/videos/perfect-sp.avi");
  cv::Mat          frame;

  if (!capture.isOpened())
  {
    std::cerr << "Error\n";
  }

  for (;;)
  {
    capture.read(frame);

    if (frame.empty())
    {
      std::cerr << "ERROR! blank frame grabbed\n";
      break;
    }

    imshow("Video", frame);

    if (cv::waitKey(5) >= 0)
      break;
  }
}

#endif  //HELLO_OPENCV_INCLUDE_1_VIDEO_LOAD_H
