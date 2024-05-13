/**
 * @brief Implementation of the Grayworld algorithm.
 *
 * @author  spjuanjoc
 * @date    2024-05-13
 */

#ifndef HELLO_OPENCV_INCLUDE_3_GRAYWORLD_GRAYWORLD_H
#define HELLO_OPENCV_INCLUDE_3_GRAYWORLD_GRAYWORLD_H

#include <filesystem>
#include <string>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

void
grayWorld()
{
  // Step 1: Load image
  std::string filename = "share/images/lena.bmp";

  if (std::filesystem::exists(filename))
  {
    cv::Mat original_image = cv::imread(filename, cv::IMREAD_UNCHANGED);
    cv::Mat grayworld_image;

    std::array<cv::Mat, 3> channels {};
    std::array<cv::Mat, 3> transformed {};

    // Step 2: Split to the RGB channels
    cv::split(original_image, channels);

    const auto [r_channel, g_channel, b_channel] = channels;

    // Step 3: Calculate the mean for each channel
    const auto r_average = cv::mean(r_channel);
    const auto g_average = cv::mean(g_channel);
    const auto b_average = cv::mean(b_channel);

    // Step 4: Calculate the gray average
    const auto average = (r_average[0] + g_average[0] + b_average[0]) / 3.0F;

    // Step 5: transform the channels
    const double r_scale = average / r_average[0];
    const double g_scale = average / g_average[0];
    const double b_scale = average / b_average[0];

    auto& [r_transformed, g_transformed, b_transformed] = transformed;

    cv::convertScaleAbs(r_channel, r_transformed, r_scale);
    cv::convertScaleAbs(g_channel, g_transformed, g_scale);
    cv::convertScaleAbs(b_channel, b_transformed, b_scale);

    // Step 6: Merge the channels to an image
    cv::merge(transformed.data(), 3, grayworld_image);

    // Show
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Grayworld", cv::WINDOW_AUTOSIZE);

    cv::imshow("Original", original_image);
    cv::imshow("Grayworld", grayworld_image);
  }
  else
  {
    fmt::println("File not found '{}'", filename);
  }
}

#endif  //HELLO_OPENCV_INCLUDE_3_GRAYWORLD_GRAYWORLD_H
