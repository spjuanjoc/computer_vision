/**
 * @brief
 *
 * @author  juanjose
 * @date    2024-05-13
 */

#ifndef LEARNING_OPENCV_INCLUDE_MENU_H
#define LEARNING_OPENCV_INCLUDE_MENU_H

#include "0_CreateMat/CreateMatrix.h"
#include "1_ShowImage/ShowImage.h"
#include "1_ShowImage/SobelFilter.h"
#include "2_Video/Load.h"
#include "2_Video/TrackBar.h"
#include "3A_GrayWorld/Grayworld.h"
#include "3B_Enhancement/Enhancements.h"
#include "3C_ColorSpaces/ColorSpaces.h"

#include <string>

const std::string menu_main = R"(
 0. Raw images
 1. Show image
 2. Video
 3. Enhancements
-1. End

Select an option: )";

constexpr std::string_view menu_video = R"(
 0. Load from file
 1. Show track bar
-1. Back

Select an option: )";

constexpr std::string_view menu_enhance = R"(
 0. Grayworld
 1. Enhancements
 2. Color space
-1. Back

Select an option: )";

constexpr std::string_view menu_enhancements = R"(
 1. Convolution
 2. Laplace filter
 3. Median blur
 4. Sobel filter
 5. Thresholding
-1. Back

Select an option: )";

constexpr std::string_view menu_color_spaces = R"(
 1. Gray
 2. HLS
 3. HSV
 4. CIEluv
 5. CIElab
-1. Back

Select an option: )";

// DECLARATIONS

void
parseOptionsMain(const std::string& option);

void
parseOptionsVideo(const std::string& option);

void
parseOptionsEnhancement(const std::string& option);

void
parseOptionsColorSpaces(const std::string& option);

void
parseOptionsEnhance(const std::string& option);

std::string
showMenu(const std::string& menu);

// DEFINITIONS

void
parseOptionsMain(const std::string& option)
{
  std::int32_t value = 0;

  try
  {
    value = std::stoi(option);
  }
  catch (const std::exception& exception)
  {
    fmt::println(stderr, "Unrecognized option '{}'", option, exception.what());
    value = 0;
  }

  switch (value)
  {
    case -1:
      fmt::println("End");
      break;
    case 0:
      createMatrix();
      break;
    case 1:
      showImage();
      break;
    case 2:
      parseOptionsVideo(showMenu(menu_video.data()));
      break;
    case 3:
      parseOptionsEnhance(showMenu(menu_enhance.data()));
      break;
    default:
      fmt::println("Invalid option");
      break;
  }
}

void
parseOptionsVideo(const std::string& option)
{
  std::int32_t value = 0;

  try
  {
    value = std::stoi(option);
  }
  catch (const std::exception& exception)
  {
    fmt::println(stderr, "Unrecognized option '{}'", option, exception.what());
    value = 0;
  }

  switch (value)
  {
    case -1:
      break;
    case 0:
      loadFromFile();
      break;
    case 1:
      showTrackbar();
      break;
  }
}

void
parseOptionsEnhance(const std::string& option)
{
  std::int32_t value = 0;

  try
  {
    value = std::stoi(option);
  }
  catch (const std::exception& exception)
  {
    fmt::println(stderr, "Unrecognized option '{}'", option, exception.what());
    value = 0;
  }

  switch (value)
  {
    case -1:
      break;
    case 0:
      grayWorld();
      break;
    case 1:
      parseOptionsEnhancement(showMenu(menu_enhancements.data()));
      break;
    case 2:
      parseOptionsColorSpaces(showMenu(menu_color_spaces.data()));
      break;
  }
}

void
parseOptionsEnhancement(const std::string& option)
{
  std::int32_t value = 0;

  try
  {
    value = std::stoi(option);
  }
  catch (const std::exception& exception)
  {
    fmt::println(stderr, "Unrecognized option '{}'", option, exception.what());
    value = 0;
  }

  switch (value)
  {
    case -1: break;
    case 1: convolution(); break;
    case 2: laplace(); break;
    case 3: medianBlur(); break;
    case 4: sobel(); break;
    case 5: thresholding(); break;
    default:
      break;
  }
}

void
parseOptionsColorSpaces(const std::string& option)
{
  std::int32_t value = 0;

  try
  {
    value = std::stoi(option);
  }
  catch (const std::exception& exception)
  {
    fmt::println(stderr, "Unrecognized option '{}'", option, exception.what());
    value = 0;
  }

  switch (value)
  {
    case -1: break;
    case 1: graySpace(); break;
    case 2: hlsSpace(); break;
    case 3: hsvSpace(); break;
    case 4: fmt::println("HSV"); break;
    case 5: fmt::println("CIElab"); break;
    default:
      break;
  }
}


std::string
showMenu(const std::string& menu)
{
  std::string option;
  fmt::print(menu);
  std::cin >> option;

  return option;
}

#endif  //LEARNING_OPENCV_INCLUDE_MENU_H
