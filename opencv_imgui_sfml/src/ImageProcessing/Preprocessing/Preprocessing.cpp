/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-16
 */

#include <ImageProcessing/Conversions.h>

#include "ImageProcessing/Preprocessing/GrayWorld.hpp"

#include <imgui.h>

#include "bindings/imgui-SFML.h"
#include <ImageProcessing/Constants.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

namespace Processing::Preprocessing
{

void
grayWorld(const cv::Mat& mat, bool is_open)
{
  static cv::Mat     grayworld_image;
  static sf::Image   image;
  static sf::Texture texture;

  std::array<cv::Mat, 3> channels {};
  std::array<cv::Mat, 3> transformed {};

  // Step 2: Split to the RGB channels
  cv::split(mat, channels);

  const auto [r_channel, g_channel, b_channel] = channels;

  // Step 3: Calculate the mean for each channel
  const auto r_average = cv::mean(r_channel);
  const auto g_average = cv::mean(g_channel);
  const auto b_average = cv::mean(b_channel);

  // Step 4: Calculate the gray average
  const auto average = (r_average[0] + g_average[0] + b_average[0]) / 3.0;

  // Step 5: transform the channels
  const double r_scale = average / r_average[0];
  const double g_scale = average / g_average[0];
  const double b_scale = average / b_average[0];

  auto& [r_transformed, g_transformed, b_transformed] = transformed;

  cv::convertScaleAbs(r_channel, r_transformed, r_scale);
  cv::convertScaleAbs(g_channel, g_transformed, g_scale);
  cv::convertScaleAbs(b_channel, b_transformed, b_scale);

  // Step 6: Merge the channels to an image
  cv::merge(transformed.data(), 3, grayworld_image);

  image = cvMat2sfImage(grayworld_image);
  texture.loadFromImage(image);

  if (is_open)
  {
    ImGui::Begin("Grayworld", &is_open, WINDOWS_FLAGS);
    {
      ImGui::Image(texture);
    }
    ImGui::End();
  }
}

}  // namespace Processing::Preprocessing
