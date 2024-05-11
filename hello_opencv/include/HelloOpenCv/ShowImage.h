/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    10/05/24
 */

#ifndef HELLO_OPENCV_INCLUDE_SHOWIMAGE_H
#define HELLO_OPENCV_INCLUDE_SHOWIMAGE_H

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <string>

static void showImage()
{
  std::string filename = "share/images/lena.bmp";
  cv::Mat     image    = cv::imread(filename, cv::IMREAD_UNCHANGED);

  cv::namedWindow("Lena", cv::WINDOW_AUTOSIZE);
  cv::imshow("Lena", image);

}

#endif  //HELLO_OPENCV_INCLUDE_SHOWIMAGE_H
