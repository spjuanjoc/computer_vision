/**
 * @brief
 *
 * @author  juanjose
 * @date    2024-05-15
 */

#ifndef INCLUDE_IMAGEPROCESSING_DRAWING_H
#define INCLUDE_IMAGEPROCESSING_DRAWING_H

#include "Conversions.h"

#include <imgui.h>

#include "bindings/imgui-SFML.h"
#include <SFML/Graphics/Texture.hpp>
#include <opencv2/core/mat.hpp>

namespace Processing
{

void
drawSrcImage(ImGuiWindowFlags window_flags, const sf::Texture& texture_src)
{
  ImGui::Begin("Original", nullptr, window_flags);
  {
    ImGui::Image(texture_src);
  }
  ImGui::End();
}

void
drawMedian(
  ImGuiWindowFlags window_flags,
  sf::Texture&     texture_dst,
  int&             kernel_size,
  const int        step,
  const cv::Mat&   mat,
  sf::Image&       image_dst)
{
  ImGui::Begin("Filtered", nullptr, window_flags);
  {
    image_dst = cvMat2sfImage(applyMedianFilter(mat, kernel_size));
    texture_dst.update(image_dst);
    ImGui::Image(texture_dst);
    ImGui::InputInt("Kernel size", &kernel_size, step);
    kernel_size = (kernel_size < 1) ? 1 : kernel_size;
  }
  ImGui::End();
}

}  // namespace Processing

#endif  //INCLUDE_IMAGEPROCESSING_DRAWING_H
