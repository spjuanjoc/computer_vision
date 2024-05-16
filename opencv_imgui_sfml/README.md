# Learning opencv

The goal of this project is to revisit and practice some OpenCV functionalities
in C++, using ImGUI with SFML as back-end.
In Ubuntu Jammy 20.04 the used version is OpenCV 4.5, since there are some
inconvenients with Wayland and opencv greater versions.

See the [imgui interactive manual](https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html)


## Lessons

- [X] Basic show image
- [ ] Load a video and add a trackbar
- [ ] Preprocessing:
  - [ ] Grayworld algorithm
  - [ ] Enhancements
    - [x] Median blur
  - [ ] Color spaces
- [ ] Morphology
- [ ] Morf Color
- [ ] Histograms
- [ ] Histograms comparison
- [ ] Matching Template
- [ ] Video Recording
- [ ] Machine Learning



## Troubleshooting

1. When running `conan install`:

   > dpkg-query: no packages found matching libva-dev.

   Solution:

        sudo apt install libva-dev libvdpau-dev libgtk2.0-dev

2. When running the program:

   > Gtk-Message: Failed to load module "canberra-gtk-module"

   Solution

        sudo apt install libcanberra-gtk-module
