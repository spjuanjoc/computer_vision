/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-27
 */

#include "ImageProcessing/Video/LoadVideo.hpp"

#include "Core/Logging/Logger.h"
#include "ImageProcessing/Constants.hpp"
#include "ImageProcessing/Conversions.h"

#include <imgui.h>

#include "bindings/imgui-SFML.h"
#include <opencv2/videoio.hpp>

namespace Processing::Video
{

void
loadFromFile(const std::string& filename, bool is_open)
{
  static cv::VideoCapture capture(filename);
  const int               width  = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_WIDTH));
  const int               height = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_HEIGHT));
  const auto              bgr_color     = cv::Scalar(0, 0, 0);
  static const cv::Mat    start_frame   = cv::Mat(height, width, CV_8UC3, bgr_color);
  static const int        min_frame     = 0;
  static int              current_frame = 0;
  static sf::Texture      texture;
  cv::Mat                 frame;

//  capture.set(cv::CAP_PROP_FRAME_WIDTH, width);
//  capture.set(cv::CAP_PROP_FRAME_HEIGHT, height);

  sf::Image        image_src = cvMat2sfImage(start_frame);
  static const int max_frame = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_COUNT));

  capture.set(cv::CAP_PROP_FPS, 30);
  texture.loadFromImage(image_src);

  if (capture.isOpened())
  {
    if (is_open)
    {
      ImGui::Begin("Video", &is_open, WINDOWS_FLAGS);
      {
        capture.read(frame);

        if (!frame.empty())
        {
          capture.set(cv::CAP_PROP_POS_FRAMES, current_frame);
          image_src = cvMat2sfImage(frame);
          texture.update(image_src);
          ImGui::Text("(%d,%d)", width, height);
          ImGui::Image(texture);
          ImGui::SliderInt("Current frame", &current_frame, min_frame, max_frame);

          ++current_frame;
        }
        else
        {
          Logger::Error("The frame {} is empty", current_frame);
        }
      }
      ImGui::End();
    }
  }
  else
  {
    Logger::Error("The video {} could not be loaded", filename);
  }
}

}  // namespace Processing::Video
