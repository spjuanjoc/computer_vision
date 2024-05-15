# Hello OpenCV

Hello world with OpenCV. Load and show "Lena"

For OpenCV version greater than 4.8 it is not working with wayland in Ubuntu
Jammy.

## Lessons


- P1 Mostrar imagen
- P2 Video Barra
- P3 Realces, grayworld, espacios de colores + inf
- P4 Morfologia
- P5 Morf Color
- P6 Histograma
- P7 Comparacion de histogramas
- P8 Matching Template
- P9 VideoRec
- P10 Machine Learning


## Troubleshooting

1. When running `conan install`:

    > dpkg-query: no packages found matching libva-dev.

    Solution:

        sudo apt install libva-dev libvdpau-dev libgtk2.0-dev

2. When running the program:

    > Gtk-Message: Failed to load module "canberra-gtk-module"

    Solution

        sudo apt install libcanberra-gtk-module
