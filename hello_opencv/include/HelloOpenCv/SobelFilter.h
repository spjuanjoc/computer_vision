/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-10
 */

#ifndef HELLO_OPENCV_INCLUDE_SOBELFILTER_H
#define HELLO_OPENCV_INCLUDE_SOBELFILTER_H

#include <string>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

static void
showSobel()
{
  std::string filename = "share/images/lena.bmp";
  cv::Mat     image    = cv::imread(filename, cv::IMREAD_UNCHANGED);

  cv::Mat grey;
  cv::Mat sobelx;
  cv::Mat draw;
  double  minVal = 0;
  double  maxVal = 0;

  cvtColor(image, grey, cv::COLOR_BGR2GRAY);
  cv::Sobel(grey, sobelx, CV_32F, 1, 0);
  minMaxLoc(sobelx, &minVal, &maxVal);
  sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

  cv::namedWindow("Gray", cv::WINDOW_AUTOSIZE);
  cv::imshow("Gray", grey);
  cv::namedWindow("Sobel", cv::WINDOW_AUTOSIZE);
  cv::imshow("Sobel", draw);
}

#endif  //HELLO_OPENCV_INCLUDE_SOBELFILTER_H
