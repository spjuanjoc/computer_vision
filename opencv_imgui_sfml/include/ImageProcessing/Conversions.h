/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-15
 */

#ifndef IMAGEPROCESSING_CONVERSIONS_H
#define IMAGEPROCESSING_CONVERSIONS_H

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace Processing
{

sf::Image
cvMat2sfImage(const cv::Mat& cv_mat);

cv::Mat
sfImage2cvMat(const sf::Image& sf_image);

cv::Mat
applyLaplaceFilter(const cv::Mat& image, int depth, const int& kernel_size);

cv::Mat
applyMedianFilter(const cv::Mat& image, const int& kernel_size);

cv::Mat
applySobelFilter(const cv::Mat& mat);

cv::Mat
applyThresholdFilter(const cv::Mat& image, const int value, const std::size_t type);

std::size_t
getThresholdType();

std::string
toColorSpaceName(const cv::ColorConversionCodes code);

}  // namespace Processing

#endif  //IMAGEPROCESSING_CONVERSIONS_H
