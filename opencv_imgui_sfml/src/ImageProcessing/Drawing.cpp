/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-16
 */

#include "ImageProcessing/Drawing.h"

#include "ImageProcessing/Constants.hpp"
#include "ImageProcessing/Conversions.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <opencv2/core/types.hpp>

namespace Processing
{

void
createCvMat(bool is_open)
{
  const auto         bgr_color = cv::Scalar(0, 0, 255);
  const cv::Mat      mat       = cv::Mat(512, 512, CV_8UC3, bgr_color);
  static sf::Image   image_src = cvMat2sfImage(mat);
  static sf::Texture texture_src;

  texture_src.loadFromImage(image_src);

  if (is_open)
  {
    ImGui::Begin("cv::Mat", &is_open, WINDOWS_FLAGS);
    {
      ImGui::Image(texture_src);
    }
    ImGui::End();
  }
}

void
drawSrcImage(const sf::Texture& texture_src, bool& is_open)
{
  // ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(512, 512));
  if (is_open)
  {
    ImGui::Begin("Original", &is_open, WINDOWS_FLAGS);
    {
      ImGui::Image(texture_src);
    }
    ImGui::End();
  }
}

}  // namespace Processing
