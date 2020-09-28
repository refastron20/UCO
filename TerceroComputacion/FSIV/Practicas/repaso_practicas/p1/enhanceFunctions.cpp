#include "enhanceFunctions.hpp"
#include <iostream>

void on_mouse(int event, int x, int y, int flags, void *userdata){
  if (event == cv::EVENT_LBUTTONDOWN and static_cast<int*>(userdata)[4]== 0) {
    static_cast<int*>(userdata)[0]=x;
    static_cast<int*>(userdata)[1]=y;
    static_cast<int*>(userdata)[4]=1;
  }else if (event == cv::EVENT_LBUTTONDOWN) {
    static_cast<int*>(userdata)[2]=x;
    static_cast<int*>(userdata)[3]=y;
    static_cast<int*>(userdata)[4]=0;
  }
}

void enhance(const cv::Mat &imageToEnhance,cv::Mat &outImage,const int coordinates[]){
  imageToEnhance.copyTo(outImage);
  cv::Point2i Point1(std::min(coordinates[0],coordinates[2]),std::min(coordinates[1],coordinates[3])),
  Point2(std::max(coordinates[0],coordinates[2]),std::max(coordinates[1],coordinates[3]));
  //pasamos a gris
  cv::cvtColor(imageToEnhance, outImage, cv::COLOR_BGR2GRAY);
  cv::cvtColor(outImage, outImage, cv::COLOR_GRAY2BGR);
  //copiamos
  cv::Mat roi = imageToEnhance(cv::Rect(Point1.x, Point1.y, Point2.x-Point1.x, Point2.y-Point1.y));
  roi.copyTo(outImage(cv::Rect(Point1.x, Point1.y, Point2.x-Point1.x, Point2.y-Point1.y)));
}

void enhanceImageFunction(const cv::Mat &imageToEnhance,const cv::String &nameOfTheFinalEnhanceImage){

  //Creamos la ventana
  cv::namedWindow("ENHANCE");
  //Inicializamos la función on_mouse
  int coordinates[5] = { -1, -1, -1, -1, 0};
  cv::setMouseCallback("ENHANCE", on_mouse, coordinates);
  //Mostramos la imagen para trabajar sobre ella
  cv::imshow("ENHANCE", imageToEnhance);
  cv::waitKey();

  cv::Mat outImage;

  enhance(imageToEnhance, outImage, coordinates);

  cv::imshow("ENHANCE", outImage);
  int key = cv::waitKey() & 0xff;
  //Si no pulsa esc(27) se guarda la imagen
  if (key!=27) {
    cv::imwrite(nameOfTheFinalEnhanceImage, outImage);
  }

}
