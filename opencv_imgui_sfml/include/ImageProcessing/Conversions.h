/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-15
 */

#ifndef IMAGEPROCESSING_CONVERSIONS_H
#define IMAGEPROCESSING_CONVERSIONS_H

#include <SFML/Graphics/Image.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace Processing
{

sf::Image
cvMat2sfImage(const cv::Mat& cv_mat)
{
  sf::Image sf_image;
  cv::Mat   cv_image_alpha;

  cv::cvtColor(cv_mat, cv_image_alpha, cv::COLOR_BGR2RGBA);
  auto width  = static_cast<uint32_t>(cv_image_alpha.cols);
  auto height = static_cast<uint32_t>(cv_image_alpha.rows);
  sf_image.create(width, height, cv_image_alpha.ptr());

  return sf_image;
}

cv::Mat
sfImage2cvMat(const sf::Image& sf_image)
{
  sf::Image  image { sf_image };
  const auto width  = static_cast<int32_t>(image.getSize().x);
  const auto height = static_cast<int32_t>(image.getSize().y);
  cv::Size   size(width, height);
  void*      image_pixels = const_cast<void*>(reinterpret_cast<const void*>(image.getPixelsPtr()));
  cv::Mat    cv_mat(size, CV_8UC4, image_pixels, cv::Mat::AUTO_STEP);

  cv::cvtColor(cv_mat, cv_mat, cv::COLOR_RGBA2BGRA);

  return cv_mat.clone();
}

cv::Mat
applyMedianFilter(const cv::Mat& image, const int& kernel_size)
{
  cv::Mat filter_image;

  cv::medianBlur(image, filter_image, kernel_size);

  return filter_image;
}

}  // namespace Processing

#endif  //IMAGEPROCESSING_CONVERSIONS_H
