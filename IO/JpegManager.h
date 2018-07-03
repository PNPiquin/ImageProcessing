#ifndef JPEG_MANAGER_H
#define JPEG_MANAGER_H

#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <boost/algorithm/string/split.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/filesystem.hpp>


class JpegManager{
public:
  JpegManager(std::string file_path);

  void GetImage(boost::gil::rgb8_image_t &img);
  void GetGrayscaleMatrixImg(Eigen::MatrixXi &mat_img);

  static void SaveGrayscaleMatrixImg(Eigen::MatrixXi &mat_img, std::string save_path);

private:
  std::string path;

  static boost::gil::gray8_image_t GrayscaleMatrixImgToGrayImg(Eigen::MatrixXi &mat_img);
};

#endif
