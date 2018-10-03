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

# How to use it

Once it's built and launched, load a picture from the input/output tab (path = working dir + image name)
Then, when the image is loaded, go through the other tabs to find the algorithm you want to apply on this image.
Each algorithm will create a new image as a result. To go through the images, use the select on the upper right corner.
