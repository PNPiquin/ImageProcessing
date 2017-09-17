#include "JpegManager.h"

JpegManager::JpegManager(std::string file_path) : path(file_path){

}

void JpegManager::GetImage(boost::gil::rgb8_image_t &img){
    if(boost::filesystem::exists(path)){
        boost::gil::jpeg_read_image(path, img);
    } else if (boost::filesystem::exists(path + ".jpeg")){
        boost::gil::jpeg_read_image(path + ".jpeg", img);
    } else if (boost::filesystem::exists(path + ".jpg")){
        boost::gil::jpeg_read_image(path + ".jpg", img);
    } else if (boost::filesystem::exists(path + ".JPG")){
        boost::gil::jpeg_read_image(path + ".JPG", img);
    } else {
        return;
    }

    printf("%s\n", "Reading image --> Success");
}

void JpegManager::GetGrayscaleMatrixImg(Eigen::MatrixXi &mat_img){
  boost::gil::rgb8_image_t img;
  GetImage(img);
  int width = img.width();
  int height = img.height();
  mat_img.resize(width, height);
  int tab[3];
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      tab[0] = static_cast<int>((uint8_t)boost::gil::view(img)(i,j)[0]);
      tab[1] = static_cast<int>((uint8_t)boost::gil::view(img)(i,j)[1]);
      tab[2] = static_cast<int>((uint8_t)boost::gil::view(img)(i,j)[2]);
      int gray_value = static_cast<int>(0.21*tab[0] + 0.72*tab[1] + 0.07*tab[2]);
      mat_img(i, j) = gray_value;
    }
  }
  printf("%s\n", "Img matrix created");
}

void JpegManager::SaveGrayscaleMatrixImg(Eigen::MatrixXi &mat_img, std::string save_path){
  boost::gil::gray8_image_t img = GrayscaleMatrixImgToGrayImg(mat_img);
  try{
      boost::gil::jpeg_write_view( save_path + ".jpeg", boost::gil::view(img));
      printf("%s\n", "Img saved successfully");
  }
  catch(std::ios_base::failure e){
      std::cout << "Error in SaveGrayscaleMatrixImg : " << e.what() << std::endl;
  }
  catch(...){
      std::cout << "ERROR !!" << std::endl;
  }
}

boost::gil::gray8_image_t JpegManager::GrayscaleMatrixImgToGrayImg(Eigen::MatrixXi &mat_img){
  int width = mat_img.rows();
  int height = mat_img.cols();
  boost::gil::gray8_image_t result_img(width, height);
  boost::gil::fill_pixels(view(result_img), boost::gil::gray8_pixel_t(0));
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      boost::gil::view(result_img)(i, j) = boost::gil::gray8_pixel_t(mat_img(i, j));
    }
  }
  return result_img;
}
