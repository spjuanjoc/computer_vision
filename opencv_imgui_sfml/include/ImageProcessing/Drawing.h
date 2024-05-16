/**
 * @brief
 *
 * @author  spjuanjoc
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
drawSrcImage(const sf::Texture& texture_src, bool& is_open)
{
  if (is_open)
  {
    ImGui::Begin("Original", &is_open, ImGuiWindowFlags_AlwaysAutoResize);
    {
      ImGui::Image(texture_src);
    }
    ImGui::End();
  }
}

void
drawMedian(const cv::Mat& mat, int& kernel_size, sf::Texture& texture_dst, bool& is_open)
{
  constexpr const auto step_size = 2;

  if (is_open)
  {
    ImGui::Begin("Filtered", &is_open, ImGuiWindowFlags_AlwaysAutoResize);
    {
      texture_dst.update(cvMat2sfImage(applyMedianFilter(mat, kernel_size)));
      ImGui::Image(texture_dst);
      ImGui::InputInt("Kernel size", &kernel_size, step_size);
      kernel_size = (kernel_size < 1) ? 1 : kernel_size;
    }
    ImGui::End();
  }
}

}  // namespace Processing

#endif  //INCLUDE_IMAGEPROCESSING_DRAWING_H
