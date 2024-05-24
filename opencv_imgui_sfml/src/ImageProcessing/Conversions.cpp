/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-16
 */

#include "ImageProcessing/Conversions.h"

#include <imgui.h>
#include <map>

namespace Processing
{

static const std::map<cv::ColorConversionCodes, std::string_view> COLOR_SPACES {
  { cv::COLOR_RGB2GRAY, "Gray Space" },
  { cv::COLOR_RGB2HLS, "HLS Space" },
  { cv::COLOR_RGB2HSV, "HSV Space" },
  { cv::COLOR_RGB2Lab, "CIE Lab Space" },
  { cv::COLOR_RGB2Luv, "CIE Luv Space" },
  { cv::COLOR_RGB2YCrCb, "Y Cr Cb Space" },
};

sf::Image
cvMat2sfImage(const cv::Mat& cv_mat)
{
  sf::Image sf_image;
  cv::Mat   cv_image_alpha;

  cv::cvtColor(cv_mat, cv_image_alpha, cv::COLOR_BGR2RGBA);
  auto width  = static_cast<uint32_t>(cv_image_alpha.cols);
  auto height = static_cast<uint32_t>(cv_image_alpha.rows);
  sf_image.create(width, height, cv_image_alpha.ptr());

  return sf_image;
}

cv::Mat
sfImage2cvMat(const sf::Image& sf_image)
{
  sf::Image  image { sf_image };
  const auto width  = static_cast<int32_t>(image.getSize().x);
  const auto height = static_cast<int32_t>(image.getSize().y);
  cv::Size   size(width, height);
  void*      image_pixels = const_cast<void*>(reinterpret_cast<const void*>(image.getPixelsPtr()));
  cv::Mat    cv_mat(size, CV_8UC4, image_pixels, cv::Mat::AUTO_STEP);

  cv::cvtColor(cv_mat, cv_mat, cv::COLOR_RGBA2BGRA);

  return cv_mat.clone();
}

cv::Mat
applyLaplaceFilter(const cv::Mat& image, int depth, const int& kernel_size)
{
  static cv::Mat filter_image;

  cv::Laplacian(image, filter_image, depth, kernel_size);

  return filter_image;
}

cv::Mat
applyMedianFilter(const cv::Mat& image, const int& kernel_size)
{
  static cv::Mat filter_image;

  cv::medianBlur(image, filter_image, kernel_size);

  return filter_image;
}

cv::Mat
applySobelFilter(const cv::Mat& mat)
{
  static cv::Mat grey;
  static cv::Mat sobel_x;
  static cv::Mat sobel_y;
  static cv::Mat sobel_x_abs;
  static cv::Mat sobel_y_abs;
  static cv::Mat filter;

  cvtColor(mat, grey, cv::COLOR_BGR2GRAY);
  cv::Sobel(grey, sobel_x, CV_32F, 1, 0);
  cv::Sobel(grey, sobel_y, CV_32F, 0, 1);
  cv::convertScaleAbs(sobel_x, sobel_x_abs);
  cv::convertScaleAbs(sobel_y, sobel_y_abs);
  cv::addWeighted(sobel_x_abs, 0.5, sobel_y_abs, 0.5, 0, filter);

  cvtColor(filter, filter, cv::COLOR_GRAY2RGB);

  return filter;
}

cv::Mat
applyThresholdFilter(const cv::Mat& image, const int value, const std::size_t type)
{
  cv::Mat   filter;
  const int max_type_value = 255;

  cv::threshold(image, filter, value, max_type_value, static_cast<int>(type));

  return filter;
}

std::size_t
getThresholdType()
{
  static const std::array<std::string_view, 5> types = { "Binary", "Binary Inverted", "Truncate", "To Zero", "To Zero Inverted" };
  static std::size_t current_index       = 3;
  auto               combo_preview_value = types[current_index];

  if (ImGui::BeginCombo("Type", combo_preview_value.data()))
  {
    for (std::size_t index = 0; index < types.size(); index++)
    {
      const bool is_selected = (current_index == index);
      if (ImGui::Selectable(types[index].data(), is_selected))
      {
        current_index = index;
      }

      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  }

  return current_index;
}

std::string
toColorSpaceName(const cv::ColorConversionCodes code)
{
  std::string name = "Not found";

  if (const auto& space = COLOR_SPACES.find(code); space != COLOR_SPACES.end())
  {
    name = space->second;
  }

  return name;
}

}  // namespace Processing
