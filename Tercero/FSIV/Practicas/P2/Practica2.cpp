#include <iostream>
#include <exception>
//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


//parametros de linea de comandos
//processImg [-i] [-c <float=1.0>] [-b <float=0.0>] [-g <float=1.0>] <input img> <output img>
const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{i interactive|      | activate interactive mode   }"
    "{c contrast|  1.0    | modify the contrast   }"
    "{b brightness|  0.0    | modify the brightness   }"
    "{g gamma|  1.0    | modify the gamma   }"
    "{@inputImage    |<none>| image to edit   }"
    "{@outputImage   |salida.jpg| name of the output image  }"
    ;

struct Datos{
  cv::Mat vectorImg[2];
  int opciones[3];
};

void NormalizarImagen(cv::Mat &img, cv::Mat &imgAux);

void desNormalizarImagen(cv::Mat &img);

void modificarImagen(cv::Mat &img,const double &c, const double &b, const double &g);

void on_trackbar( int , void* userdata);

int main (int argc, char* const* argv){
      int retCode=EXIT_SUCCESS;

      try {

        struct Datos datos;

        cv::CommandLineParser parser(argc, argv, keys);
        double c=parser.get<float>("c"),b=parser.get<float>("b"),g=parser.get<float>("g");
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

      cv::Mat Aux(img.rows,img.cols,CV_32FC3);


      datos.vectorImg[0]=Aux;

      NormalizarImagen(img,datos.vectorImg[0]);
      datos.vectorImg[0].copyTo(datos.vectorImg[1]);

      struct Datos *datosp;
      datosp=&datos;


      cv::namedWindow("IMG");

      if (parser.has("interactive")) {
        datos.opciones[0]=100;
        datos.opciones[1]=100;
        datos.opciones[2]=100;


        cv::createTrackbar( "brightness", "IMG", &datos.opciones[0], 200, on_trackbar, datosp);
        cv::createTrackbar( "contrast", "IMG", &datos.opciones[1], 200, on_trackbar,datosp);
        cv::createTrackbar( "Gamma", "IMG", &datos.opciones[2], 200, on_trackbar,datosp);
        on_trackbar(0, datosp );

      }else{
        modificarImagen(datosp->vectorImg[1],c,b,g);


        cv::imshow("IMG",datosp->vectorImg[1]);
      }


      int key=cv::waitKey(0) & 0xff;

      datosp->vectorImg[1].copyTo(datosp->vectorImg[0]);

      desNormalizarImagen(datosp->vectorImg[0]);


      if (key!=27) {
        cv::imwrite(parser.get<cv::String>(1),datosp->vectorImg[0]);
      }



  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}

void NormalizarImagen(cv::Mat &img,cv::Mat &imgAux){
  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      cv::Vec3b v1 = img.at<cv::Vec3b>(i, j);
      cv::Vec3f v2 = imgAux.at<cv::Vec3f>(i, j);
      v2[0]=((float)v1[0]/255);
      v2[1]=((float)v1[1]/255);
      v2[2]=((float)v1[2]/255);
      imgAux.at<cv::Vec3f>(i, j)=v2;
    }
  }
}

void desNormalizarImagen(cv::Mat &img){
  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      cv::Vec3f v = img.at<cv::Vec3f>(i, j);
      v[0]=v[0]*255;
      if (v[0]>255) {
        v[0]=255;
      }else if(v[0]<0){
        v[0]=0;
      }
      v[1]=v[1]*255;
      if (v[1]>255) {
        v[1]=255;
      }else if(v[1]<0){
        v[1]=0;
      }
      v[2]=v[2]*255;
      if (v[2]>255) {
        v[2]=255;
      }else if(v[2]<0){
        v[2]=0;
      }
      img.at<cv::Vec3f>(i, j)=v;
    }
  }
}

void modificarImagen(cv::Mat &img,const double &c, const double &b, const double &g){
  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      cv::Vec3f v = img.at<cv::Vec3f>(i, j);
      v[0]=c*pow(v[0],g)+b;
      v[1]=c*pow(v[1],g)+b;
      v[2]=c*pow(v[2],g)+b;
      img.at<cv::Vec3f>(i, j)=v;
    }
  }
}

void on_trackbar( int, void* userdata)
{

  Datos *datos=static_cast<Datos *>(userdata);
  double brillo = ((double)datos->opciones[0]-100)/100;
  double contraste = (double)datos->opciones[1]/100;
  double gamma = (double)datos->opciones[2]/100;

  cv::Mat imgAux=datos->vectorImg[0];
  cv::Mat imgAux2=datos->vectorImg[1];
  imgAux.copyTo(imgAux2);
  modificarImagen(imgAux2,contraste,brillo,gamma);
  cv::imshow("IMG", imgAux2);
}
