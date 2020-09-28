#include <iostream>
#include <exception>
//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <cmath>

typedef struct datos{
  cv::Mat img[2];
  int contraste;
  int brillo;
  int gamma;
}datos;

//parametros de linea de comandos
//processImg [-i] [-c <float=1.0>] [-b <float=0.0>] [-g <float=1.0>] <input img> <output img>
const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{i interactive  |      | activate interactive mode   }"
    "{c contrast     | 1.0  | modify the contrast   }"
    "{b brightness   | 0.0  | modify the brightness   }"
    "{g gamma        | 1.0  | modify the gamma   }"
    "{@inputImage    |<none>| image to edit   }"
    "{@outputImage   |salida.jpg| name of the output image  }"
    ;

void on_trackbar( int , void* userdata);

void modificarImagen(const cv::Mat &img, const float &c, const float &g, const float &b, cv::Mat &out);

int main (int argc, char* const* argv){
  int retCode=EXIT_SUCCESS;

  try {

    cv::CommandLineParser parser(argc, argv, keys);
    double c=parser.get<float>("c"), b=parser.get<float>("b"), g=parser.get<float>("g");
    parser.about("Modifica la imagen");
    if (parser.has("help"))
    {
      parser.printMessage();
      return 0;
    }
    cv::String img_name = parser.get<cv::String>(0);

    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }


    cv::Mat img = cv::imread(img_name, cv::IMREAD_COLOR);

    if (img.empty())
    {
       std::cerr << "Error: no he podido abrir el fichero '" << img_name << "'." << std::endl;
       return EXIT_FAILURE;
    }

    img.convertTo(img, CV_32FC3, 1/255.0);

    cv::namedWindow("IMG");

    cv::Mat out;

    if (parser.has("interactive")) {
      datos data;
      data.img[0]=img;
      data.contraste=100;
      data.brillo=100;
      data.gamma=100;
      cv::createTrackbar("contraste", "IMG", &data.contraste, 200, on_trackbar, &data);
      cv::createTrackbar("brillo", "IMG", &data.brillo, 200, on_trackbar, &data);
      cv::createTrackbar("gamma", "IMG", &data.gamma, 200, on_trackbar, &data);
      on_trackbar(0, &data);
      cv::waitKey();

    }else{
      cv::namedWindow("IMG2");
      modificarImagen(img, c, g, b, out);
      cv::imshow("IMG", img);
      cv::imshow("IMG2", out);
      cv::waitKey();
    }

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}

void on_trackbar( int, void* userdata)
{
  datos data=*static_cast<datos *>(userdata);
  float c=(float)(data.contraste)/100;
  float b=(float)(data.brillo-100)/100;
  float g=(float)(data.gamma)/100;
  std::cout << "c= " <<c<< '\n';
  std::cout << "b= " <<b<< '\n';
  std::cout << "g= " <<g<< '\n';
  modificarImagen(data.img[0],c,g,b,data.img[1]);
  cv::imshow("IMG", data.img[1]);
}

void modificarImagen(const cv::Mat &img, const float &c, const float &g, const float &b, cv::Mat &out){
  img.copyTo(out);
  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++) {
      cv::Vec3f v = out.at<cv::Vec3f>(i,j);
      v[0]=c*pow(v[0],g)+b;
      v[1]=c*pow(v[1],g)+b;
      v[2]=c*pow(v[2],g)+b;
      out.at<cv::Vec3f>(i,j) = v;
    }
  }
}
