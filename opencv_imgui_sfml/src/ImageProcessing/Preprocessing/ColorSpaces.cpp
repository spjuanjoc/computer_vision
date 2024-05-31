/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-24
 */

#include "ImageProcessing/Preprocessing/ColorSpaces.hpp"

#include "ImageProcessing/Constants.hpp"
#include "ImageProcessing/Conversions.h"

#include <imgui.h>

#include "bindings/imgui-SFML.h"
#include <SFML/Graphics/Texture.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

namespace Processing::Spaces
{

void
toColorSpace(const cv::Mat& mat, bool is_open, const cv::ColorConversionCodes conversion_code)
{
  static cv::Mat     result;
  static sf::Image   image;
  static sf::Texture texture;

  cv::cvtColor(mat, result, conversion_code);

  image = cvMat2sfImage(result);
  texture.loadFromImage(image);

  if (is_open)
  {
    const auto window_name = toColorSpaceName(conversion_code);
    ImGui::Begin(window_name.c_str(), &is_open, WINDOWS_FLAGS);
    {
      ImGui::Image(texture);
    }
    ImGui::End();
  }
}

}  // namespace Processing::Spaces
