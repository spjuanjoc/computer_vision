/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-16
 */

#include "ImageProcessing/Preprocessing/Enhancements.hpp"

#include "ImageProcessing/Constants.hpp"
#include "ImageProcessing/Conversions.h"

#include <imgui.h>

#include "bindings/imgui-SFML.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <opencv2/core/mat.hpp>

namespace Processing::Enhancements
{

void
convolution(const cv::Mat& mat, bool is_open)
{
  static cv::Mat       filter;
  static cv::Mat       result;
  static const cv::Mat kernel { 1, 1, 1, 0, 0, 0, -1, -1, -1 };
  constexpr int        depth = -1;

  cv::filter2D(mat, filter, depth, kernel);
  cv::add(mat, filter, result);

  static sf::Image   image_filter = cvMat2sfImage(filter);
  static sf::Image   image        = cvMat2sfImage(result);
  static sf::Texture texture_filter;
  static sf::Texture texture;

  texture.loadFromImage(image);
  texture_filter.loadFromImage(image_filter);

  if (is_open)
  {
    ImGui::Begin("Convolution##1", &is_open, WINDOWS_FLAGS);
    {
      ImGui::Image(texture_filter);
    }
    ImGui::End();
  }

  if (is_open)
  {
    ImGui::Begin("Convolution##2", &is_open, WINDOWS_FLAGS);
    {
      ImGui::Image(texture);
    }
    ImGui::End();
  }
}

void
laplace(const cv::Mat& mat, bool is_open)
{
  constexpr int        depth       = 0;
  constexpr int        kernel_size = 3;
  static cv::Mat       filter;
  static cv::Mat       result;
  static const cv::Mat kernel { 1, 1, 1, 0, 0, 0, -1, -1, -1 };

  cv::Laplacian(mat, filter, depth, kernel_size);
  cv::add(mat, filter, result);

  static sf::Image   image_filter = cvMat2sfImage(filter);
  static sf::Image   image        = cvMat2sfImage(result);
  static sf::Texture texture_filter;
  static sf::Texture texture;

  texture.loadFromImage(image);
  texture_filter.loadFromImage(image_filter);

  if (is_open)
  {
    ImGui::Begin("Laplace##1", &is_open, WINDOWS_FLAGS);
    {
      filter = applyLaplaceFilter(mat, depth, kernel_size);
      texture_filter.update(cvMat2sfImage(filter));
      ImGui::Image(texture_filter);
    }
    ImGui::End();
  }

  if (is_open)
  {
    ImGui::Begin("Laplace##2", &is_open, WINDOWS_FLAGS);
    {
      cv::add(mat, filter, result);
      texture.update(cvMat2sfImage(result));
      ImGui::Image(texture);
    }
    ImGui::End();
  }
}

void
medianBlur(const cv::Mat& mat, int& kernel_size, bool is_open)
{
  constexpr auto     step_size = 2;
  static sf::Image   image     = cvMat2sfImage(mat);
  static sf::Texture texture;

  texture.loadFromImage(image);

  if (is_open)
  {
    ImGui::Begin("Median blur", &is_open, WINDOWS_FLAGS);
    {
      texture.update(cvMat2sfImage(applyMedianFilter(mat, kernel_size)));
      ImGui::Image(texture);
      ImGui::InputInt("Kernel size", &kernel_size, step_size);
      kernel_size = (kernel_size < 1) ? 1 : kernel_size;
    }
    ImGui::End();
  }
}

void
sobel(const cv::Mat& mat, bool is_open)
{
  static cv::Mat filter = applySobelFilter(mat);
  static cv::Mat result;

  cv::add(mat, filter, result);

  static sf::Image   image_filter = cvMat2sfImage(filter);
  static sf::Image   image        = cvMat2sfImage(result);
  static sf::Texture texture_filter;
  static sf::Texture texture;

  texture.loadFromImage(image);
  texture_filter.loadFromImage(image_filter);

  if (is_open)
  {
    ImGui::Begin("Sobel##1", &is_open, WINDOWS_FLAGS);
    {
      filter = applySobelFilter(mat);
      texture_filter.update(cvMat2sfImage(filter));
      ImGui::Image(texture_filter);
    }
    ImGui::End();
  }

  if (is_open)
  {
    ImGui::Begin("Sobel##2", &is_open, WINDOWS_FLAGS);
    {
      cv::add(mat, filter, result);
      texture.update(cvMat2sfImage(result));
      ImGui::Image(texture);
    }
    ImGui::End();
  }
}

void
thresholding(const cv::Mat& mat, bool is_open)
{
  static int           value     = 128;
  static constexpr int min_value = 0;
  static constexpr int max_value = 255;
  static std::size_t   type      = 3;
  static cv::Mat       filter    = applyThresholdFilter(mat, value, type);
  static sf::Image     image     = cvMat2sfImage(filter);
  static sf::Texture   texture;

  texture.loadFromImage(image);

  if (is_open)
  {
    ImGui::Begin("Threshold", &is_open, WINDOWS_FLAGS);
    {
      texture.update(cvMat2sfImage(applyThresholdFilter(mat, value, type)));
      ImGui::Image(texture);
      ImGui::SliderInt("Value", &value, min_value, max_value);
      type = getThresholdType();
    }
    ImGui::End();
  }
}

}  // namespace Processing::Enhancements
