/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-16
 */

#ifndef INCLUDE_IMAGEPROCESSING_ENHANCEMENTS_HPP
#define INCLUDE_IMAGEPROCESSING_ENHANCEMENTS_HPP

#include <opencv2/core/mat.hpp>

namespace Processing::Enhancements
{

void
convolution(const cv::Mat& mat, bool is_open);

void
laplace(const cv::Mat& mat, bool is_open);

void
medianBlur(const cv::Mat& mat, int& kernel_size, bool is_open);

void
sobel(const cv::Mat& mat, bool is_open);

void
thresholding(const cv::Mat& mat, bool is_open);

}  // namespace Processing::Enhancements

#endif  //INCLUDE_IMAGEPROCESSING_ENHANCEMENTS_HPP
