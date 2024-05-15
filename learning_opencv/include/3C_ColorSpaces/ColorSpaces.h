/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2024-05-14
 */

#ifndef LEARNING_OPENCV_INCLUDE_3C_COLORSPACES_COLORSPACES_H
#define LEARNING_OPENCV_INCLUDE_3C_COLORSPACES_COLORSPACES_H

/*
RGB: rojo(R), verde(G) y azul(B).
HSI: Tono(Hue), Saturación(Saturation) y Brillo(Intensity).
XYZ. Espacio de colores rojo, verde y azul crudos.
CMY. Espacio de color cian, magenta y amarillo, indicado
para impresoras en color.
CMYK. Espacio de color cian, magenta, amarillo y negro,
indicado para impresoras en color.
GRAY. Espacio de color gris, indicado para imágenes
monocromáticas.
HLS. Espacio de color profundidad, luz y saturación.
HSB. Espacio de color profundidad, saturación y brillo.
HSV. Espacio de color profundidad, saturación y valor.
Lab. Espacio de color de brillo y color.
Luv. Espacio de color de intensidad y color.
RGB. Espacio de color rojo, verde y azul.

 */

void
graySpace()
{
  const std::string filename    = "share/images/lena.bmp";
  const cv::Mat     input_image = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cv::Mat           result_image;
  cv::Mat           result_image2;

  cv::cvtColor(input_image, result_image, cv::COLOR_RGB2GRAY);
  cv::cvtColor(input_image, result_image2, cv::COLOR_BGR2GRAY);

  cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Result RGB to Gray", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Result BGR to Gray", cv::WINDOW_AUTOSIZE);

  cv::imshow("Input", input_image);
  cv::imshow("Result RGB to Gray", result_image);
  cv::imshow("Result BGR to Gray", result_image2);
}

// COLOR_BGR2HLS HLS (hue lightness saturation)
void
hlsSpace()
{
  const std::string filename    = "share/images/lena.bmp";
  const cv::Mat     input_image = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cv::Mat           result_image;
  cv::Mat           result_image2;

  cv::cvtColor(input_image, result_image, cv::COLOR_BGR2HLS);

  cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Result HLS", cv::WINDOW_AUTOSIZE);

  cv::imshow("Input", input_image);
  cv::imshow("Result HLS", result_image);
}

// COLOR_BGR2HSV HSV (hue saturation value)
void
hsvSpace()
{
  const std::string filename    = "share/images/lena.bmp";
  const cv::Mat     input_image = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cv::Mat           result_image;
  cv::Mat           result_image2;

  cv::cvtColor(input_image, result_image, cv::COLOR_BGR2HSV);

  cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Result HSV", cv::WINDOW_AUTOSIZE);

  cv::imshow("Input", input_image);
  cv::imshow("Result HSV", result_image);
}



// COLOR_BGR2Lab CIE Lab
// COLOR_BGR2Luv
/*
 *
auto cb = [](int, void*){};
cv::createButton("Button0", cb, nullptr, cv::QT_PUSH_BUTTON);
cv::createButton("Button1", cb, nullptr, cv::QT_CHECKBOX);
cv::createButton("Button2", cb, nullptr, cv::QT_RADIOBOX);
cv::createButton("Button3", cb, nullptr, cv::QT_NEW_BUTTONBAR);
 */
#endif  //LEARNING_OPENCV_INCLUDE_3C_COLORSPACES_COLORSPACES_H
