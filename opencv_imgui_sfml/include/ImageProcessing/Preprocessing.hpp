/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-16
 */

#ifndef IMAGEPROCESSING_PREPROCESSING_HPP
#define IMAGEPROCESSING_PREPROCESSING_HPP

#include <opencv2/core/mat.hpp>

namespace Processing::Preprocessing
{

void
grayWorld(const cv::Mat& mat, bool is_open);

}  // namespace Processing::Preprocessing

#endif  //IMAGEPROCESSING_PREPROCESSING_HPP
