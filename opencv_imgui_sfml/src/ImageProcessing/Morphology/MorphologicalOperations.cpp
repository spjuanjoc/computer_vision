/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-27
 */

#include "ImageProcessing/Morphology/MorphologicalOperations.hpp"

#include <ImageProcessing/Conversions.h>

#include <imgui.h>

#include "bindings/imgui-SFML.h"
#include <ImageProcessing/Constants.hpp>
#include <SFML/Graphics/Image.hpp>
#include <opencv2/core/mat.hpp>

namespace Processing::Morphology
{

//"1. Dilate "
//"2. Erode "
//"3. Opening "
//"4. Closing "
//"5. Morphological Gradient"

void
dilation(const cv::Mat& mat, bool is_open, const std::size_t& structuring_element, const std::size_t& image_type)
{
  static sf::Texture           texture;
  static cv::Mat               result;
  static sf::Image             image       = cvMat2sfImage(mat);
  static const cv::MorphShapes shape       = toShape(structuring_element);
  static const cv::Size        kernel_size = { 3, 3 };
  static const cv::Mat         kernel      = cv::getStructuringElement(shape, kernel_size);
  cv::Mat                      mat1channel = to1ChannelImage(mat, image_type);

  cv::dilate(mat1channel, result, kernel);

  texture.loadFromImage(image);

  if (is_open)
  {
    ImGui::Begin("Dilation", &is_open, WINDOWS_FLAGS);
    {
      texture.update(cvMat2sfImage(result));
      ImGui::Image(texture);
    }
    ImGui::End();
  }
}

void
erosion(const cv::Mat& mat, bool is_open, const std::size_t& structuring_element, const std::size_t& image_type)
{
  static sf::Texture           texture;
  static cv::Mat               result;
  static sf::Image             image       = cvMat2sfImage(mat);
  static const cv::MorphShapes shape       = toShape(structuring_element);
  static const cv::Size        kernel_size = { 3, 3 };
  static const cv::Mat         kernel      = cv::getStructuringElement(shape, kernel_size);
  cv::Mat                      mat1channel = to1ChannelImage(mat, image_type);

  cv::erode(mat1channel, result, kernel);

  texture.loadFromImage(image);

  if (is_open)
  {
    ImGui::Begin("Erosion", &is_open, WINDOWS_FLAGS);
    {
      texture.update(cvMat2sfImage(result));
      ImGui::Image(texture);
    }
    ImGui::End();
  }
}

}  // namespace Processing::Morphology
