/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-27
 */

#ifndef MORPHOLOGY_MORPHOLOGICALOPERATIONS_HPP
#define MORPHOLOGY_MORPHOLOGICALOPERATIONS_HPP

#include <opencv2/imgproc.hpp>

namespace Processing::Morphology
{

void
dilation(const cv::Mat& mat, bool is_open, const std::size_t& structuring_element, const std::size_t& image_type);

void
erosion(const cv::Mat& mat, bool is_open, const std::size_t& structuring_element, const std::size_t& image_type);

void
morphology(
  const cv::Mat&       mat,
  bool                 is_open,
  const std::size_t&   structuring_element,
  const std::size_t&   image_type,
  const cv::MorphTypes operation);

}  // namespace Processing::Morphology

#endif  //MORPHOLOGY_MORPHOLOGICALOPERATIONS_HPP
