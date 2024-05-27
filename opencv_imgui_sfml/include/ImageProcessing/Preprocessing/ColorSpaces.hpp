/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-24
 */

#ifndef IMAGEPROCESSING_COLORSPACES_HPP
#define IMAGEPROCESSING_COLORSPACES_HPP

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

namespace Processing::Spaces
{

void
toColorSpace(const cv::Mat& mat, bool is_open, cv::ColorConversionCodes conversion_code);

void
hlsSpace();

void
hsvSpace();

}  // namespace Processing::Spaces

#endif  // IMAGEPROCESSING_COLORSPACES_HPP
