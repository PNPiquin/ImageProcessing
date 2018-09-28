# ImageProcessing
Small C++ soft to use image processing algorithms from a Qt GUI

The purpose of this project is to implement image processing algorithms in C++ to understand them and to use them on small examples.
This project is built with Qt, using Eigen, boost, libpng and libjpeg libraries.

# How to build
To build the project, you will need to install the needed libraries:
   --> Eigen : https://eigen.tuxfamily.org/dox/GettingStarted.html
   --> Boost : https://www.boost.org/
   --> libjpeg : http://libjpeg.sourceforge.net/
   --> libpng : http://www.libpng.org/pub/png/libpng.html
   
Then, using Qt creator, you need to link these libraries to the project by setting the link paths inside the ImageProcessing.pro file.
The compiler flags used are set inside this same ImageProcessing.pro file.
