# Learning opencv

The goal of this project is to revisit and practice some OpenCV functionalities
in C++, using ImGUI with SFML as back-end.
In Ubuntu Jammy 20.04 the used version is OpenCV 4.5, since there are some
inconvenient with Wayland and opencv greater versions.

See the [imgui interactive manual](https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html)


## Lessons

- [x] Show and image
- [x] Load a video and add a trackbar
- [x] Preprocessing:
  - [x] Grayworld algorithm
  - [x] Enhancements
    - [x] Convolution
    - [x] Laplace
    - [x] Median blur
    - [x] Sobel
    - [x] Threshold
  - [x] Color spaces
    - [x] Gray
    - [x] HLS (hue lightness saturation)
    - [x] HSV (hue saturation value)
    - [x] Cie Lab
    - [x] YUV (Y Cr Cb)
- [x] Morphology in Black and White / Grayscale
  - [x] Dilation
  - [x] Erosion
  - [x] Opening
  - [x] Closing
  - [x] Gradient
- [ ] Morphology in Color
- [x] Histograms
  - [x] Grayscale
  - [x] Color
- [ ] Histograms comparison
- [ ] Matching Template
- [ ] Video Recording
- [ ] Machine Learning

## To Do

- [ ] Fixed size windows
- [ ] Fixed position windows
- [ ] Update menu to 'Context menu inside a regular window'
- [ ] Load file.
- [ ] Save file.
- [ ] ~~Dock windows: Requires using the imgui branch with the docking features.~~

## Troubleshooting

1. When running `conan install`:

   > dpkg-query: no packages found matching libva-dev.

   Solution:

        sudo apt install libva-dev libvdpau-dev libgtk2.0-dev

2. When running the program:

   > Gtk-Message: Failed to load module "canberra-gtk-module"

   Solution

        sudo apt install libcanberra-gtk-module
