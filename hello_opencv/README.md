# Hello OpenCV

Hello world with OpenCV.


## Troubleshooting

1. When running `conan install`:

    > dpkg-query: no packages found matching libva-dev.

    Solution:

        sudo apt install libva-dev libvdpau-dev libgtk2.0-dev

2. When running the program:

    > Gtk-Message: Failed to load module "canberra-gtk-module"

    Solution

        sudo apt install libcanberra-gtk-module
