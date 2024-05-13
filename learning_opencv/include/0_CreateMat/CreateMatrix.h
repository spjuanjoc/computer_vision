/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-10
 */

#ifndef HELLO_OPENCV_INCLUDE_CREATEMATRIX_H
#define HELLO_OPENCV_INCLUDE_CREATEMATRIX_H

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

static void
createMatrix()
{
  const auto color = cv::Scalar(0, 0, 255);
  const auto image = cv::Mat(480, 640, CV_8UC3, color);

  cv::imshow("cv::Mat", image);
}

#endif  //HELLO_OPENCV_INCLUDE_CREATEMATRIX_H
