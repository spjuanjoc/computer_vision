/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-31
 */

#ifndef GRAY_HISTOGRAM_HPP
#define GRAY_HISTOGRAM_HPP

#include <opencv2/core/mat.hpp>

namespace Processing
{

void
grayHistogram(const cv::Mat& source, bool is_open);

void
colorHistogram(const cv::Mat& source, bool is_open);

}


#endif //GRAY_HISTOGRAM_HPP
