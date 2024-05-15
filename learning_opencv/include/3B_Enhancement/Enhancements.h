/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-13
 */

#ifndef INCLUDE_3B_REALCES_ENHANCEMENTS_H
#define INCLUDE_3B_REALCES_ENHANCEMENTS_H

void
convolution()
{
  const std::string filename    = "share/images/lena.bmp";
  const cv::Mat     input_image = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cv::Mat           filter_image;
  cv::Mat           result_image;
  const cv::Mat     kernel { 1, 1, 1, 0, 0, 0, -1, -1, -1 };

  cv::filter2D(input_image, filter_image, -1, kernel);
  cv::add(input_image, filter_image, result_image);

  cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Convolution filter", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);

  cv::imshow("Input", input_image);
  cv::imshow("Convolution filter", filter_image);
  cv::imshow("Result", result_image);
}

void
laplace()
{
  const std::string filename    = "share/images/lena.bmp";
  const cv::Mat     input_image = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cv::Mat           filter_image;
  cv::Mat           result_image;
  int               depth       = 0;
  int               kernel_size = 3;

  cv::Laplacian(input_image, filter_image, depth, kernel_size);
  cv::add(input_image, filter_image, result_image);

  cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Laplace filter", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);

  cv::imshow("Input", input_image);
  cv::imshow("Laplace filter", filter_image);
  cv::imshow("Result", result_image);
}

void
medianBlur()
{
  const std::string filename    = "share/images/lena.bmp";
  const cv::Mat     input_image = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cv::Mat           filter_image;
  int               kernel_size = 5;

  cv::medianBlur(input_image, filter_image, kernel_size);

  cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Median blur", cv::WINDOW_AUTOSIZE);

  cv::imshow("Input", input_image);
  cv::imshow("Median blur", filter_image);
}

void
sobel()
{
  const std::string filename    = "share/images/lena.bmp";
  const cv::Mat     input_image = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cv::Mat           filter_image;
  cv::Mat           result_image;
  cv::Mat           grey;
  cv::Mat           sobel_x;
  cv::Mat           sobel_y;
  cv::Mat           sobel_x_abs;
  cv::Mat           sobel_y_abs;

  cvtColor(input_image, grey, cv::COLOR_BGR2GRAY);
  cv::Sobel(grey, sobel_x, CV_32F, 1, 0);
  cv::Sobel(grey, sobel_y, CV_32F, 0, 1);
  cv::convertScaleAbs(sobel_x, sobel_x_abs);
  cv::convertScaleAbs(sobel_y, sobel_y_abs);
  cv::addWeighted(sobel_x_abs, 0.5, sobel_y_abs, 0.5, 0, filter_image);

  cvtColor(filter_image, filter_image, cv::COLOR_GRAY2RGB);
  cv::add(input_image, filter_image, result_image);

  cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Sobel filter", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);

  cv::imshow("Input", input_image);
  cv::imshow("Sobel filter", filter_image);
  cv::imshow("Result", result_image);
}

void
thresholding()
{
  constexpr auto trackbar_type
    = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
  constexpr auto       trackbar_value   = "Value";
  static int           threshold_value  = 0;
  static int           threshold_type   = 3;
  const int            max_type         = 4;
  const int            max_value        = 255;
  const int            max_type_value   = 255;
  const std::string    filename         = "share/images/lena.bmp";
  static const cv::Mat input_image_th   = cv::imread(filename, cv::IMREAD_UNCHANGED);
  static cv::Mat       filter_image;

  cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Thresholding", cv::WINDOW_AUTOSIZE);

  auto changeThreshold = [](int, void*)
  {
    threshold(input_image_th, filter_image, threshold_value, max_type_value, threshold_type);

    cv::imshow("Thresholding", filter_image);
  };

  cv::createTrackbar(trackbar_type, "Thresholding", &threshold_type, max_type, changeThreshold);
  cv::createTrackbar(trackbar_value, "Thresholding", &threshold_value, max_value, changeThreshold);

  cv::imshow("Input", input_image_th);
}

#endif  //INCLUDE_3B_REALCES_ENHANCEMENTS_H
