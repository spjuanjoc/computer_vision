/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-31
 */

#include "ImageProcessing/Histogram/Histogram.hpp"

#include "ImageProcessing/Constants.hpp"
#include "ImageProcessing/Conversions.h"

#include <imgui.h>

#include "bindings/imgui-SFML.h"
#include <SFML/Graphics/Texture.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

namespace Processing
{

cv::Mat
grayHistogramLines(const cv::Mat& source)
{
  constexpr int    size              = 256;
  constexpr float  range_values[]    = { 0, 256 };
  const float*     range[]           = { range_values };
  constexpr bool   is_uniform        = true;
  constexpr bool   should_accumulate = false;
  constexpr int    width             = 512;
  constexpr int    height            = 512;
  const cv::Scalar color_gray(150, 150, 150);
  cv::Mat          histogram_values;

  cv::calcHist(&source, 1, nullptr, cv::Mat(), histogram_values, 1, &size, range, is_uniform, should_accumulate);

  const int bin_width = static_cast<int>(std::round(width / size));

  cv::Mat result(height, width, CV_8UC1, cv::Scalar(0, 0, 0));

  normalize(histogram_values, histogram_values, 0, result.rows, cv::NORM_MINMAX, -1, cv::Mat());

  for (std::size_t i = 1; i < size; i++)
  {
    const size_t x_1 = bin_width * (i - 1);
    const size_t y_1 = height - static_cast<size_t>(std::round(histogram_values.at<float>(i - 1)));
    const size_t x_2 = bin_width * (i);
    const size_t y_2 = height - static_cast<size_t>(std::round(histogram_values.at<float>(i)));

    const cv::Point point_1(x_1, y_1);
    const cv::Point point_2(x_2, y_2);

    cv::line(result, point_1, point_2, color_gray, 2);
  }

  return result;
}

cv::Mat
brgHistogramLines(const cv::Mat& src)
{
  std::vector<cv::Mat> bgr_planes;
  constexpr int        histSize    = 256;
  float                range[]     = { 0, 256 };  //the upper boundary is exclusive
  const float*         histRange[] = { range };
  constexpr bool       uniform     = true;
  constexpr bool       accumulate  = false;
  cv::Mat              b_hist, g_hist, r_hist;
  cv::Mat              result;

  cv::split(src, bgr_planes);

  cv::calcHist(&bgr_planes[0], 1, nullptr, cv::Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate);
  cv::calcHist(&bgr_planes[1], 1, nullptr, cv::Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate);
  cv::calcHist(&bgr_planes[2], 1, nullptr, cv::Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate);

  constexpr int hist_w = 512;
  constexpr int hist_h = 400;
  const int     bin_w  = cvRound(static_cast<double>(hist_w) / histSize);

  cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

  normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
  normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
  normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

  for (int i = 1; i < histSize; i++)
  {
    cv::line(
      histImage,
      cv::Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
      cv::Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
      cv::Scalar(255, 0, 0),
      2,
      8,
      0);

    cv::line(
      histImage,
      cv::Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
      cv::Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
      cv::Scalar(0, 255, 0),
      2,
      8,
      0);

    cv::line(
      histImage,
      cv::Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
      cv::Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
      cv::Scalar(0, 0, 255),
      2,
      8,
      0);
  }

  return histImage;
}

void
grayHistogram(const cv::Mat& source, bool is_open)
{
  static cv::Mat gray;

  cv::cvtColor(source, gray, cv::COLOR_RGB2GRAY);

  static cv::Mat     result = grayHistogramLines(gray);
  static sf::Image   image  = cvMat2sfImage(result);
  static sf::Texture texture;

  texture.loadFromImage(image);

  if (is_open)
  {
    ImGui::Begin("Grayscale histogram", &is_open, WINDOWS_FLAGS);
    {
      ImGui::Image(texture);
    }
    ImGui::End();
  }
}

void
colorHistogram(const cv::Mat& source, bool is_open)
{
  static cv::Mat     result = brgHistogramLines(source);
  static sf::Image   image  = cvMat2sfImage(result);
  static sf::Texture texture;

  texture.loadFromImage(image);

  if (is_open)
  {
    ImGui::Begin("Histogram", &is_open, WINDOWS_FLAGS);
    {
      ImGui::Image(texture);
    }
    ImGui::End();
  }
}

}  // namespace Processing
