#include <iostream>
#include <exception>
//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@inputImage    |<none>| image to edit   }"
    "{@outputImage   |salida.jpg| name of the output image  }"
    ;

void on_mouse(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
      static_cast<int*>(userdata)[0] = x;
      static_cast<int*>(userdata)[1] = y;
    }else if(event==cv::EVENT_LBUTTONUP){
      static_cast<int*>(userdata)[2] = x;
      static_cast<int*>(userdata)[3] = y;
    }
}

int main(int argc, char* const* argv){
  int retCode=EXIT_SUCCESS;

  try {

      //Configuramos el parser
      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Este programa sirve para hacer el realce de una imagen en el rectangulo definido por dos clicks de ratón");
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

      //Cargamos la imagen en una matriz
      cv::Mat img = cv::imread(img_name, cv::IMREAD_COLOR);

      //Comprobamos si hemos podido cargar la imagen
      if (img.empty())
      {
         std::cerr << "Error: no he podido abrir el fichero '" << img_name << "'." << std::endl;
         return EXIT_FAILURE;
      }

      //Creamos la ventana
      cv::namedWindow("IMG");

      //Inicializamos las coordenadas
      int coords[4] = {-1, -1,-1,-1};
      cv::setMouseCallback ("IMG", on_mouse, coords);


      int key = 0;

      cv::imshow("IMG", img);
      //el codigo ascci. Si pasa el tiempo, retorna -1.
      key=cv::waitKey(0) & 0xff;

      cv::Mat imgRealce;
      img.copyTo(imgRealce);
      int negro;
      int punto1[2]={std::min(coords[0],coords[2]),std::min(coords[1],coords[3])};
      int punto2[2]={std::max(coords[0],coords[2]),std::max(coords[1],coords[3])};

      for (int i = 0; i < imgRealce.rows; i++) {
        for (int j = 0; j < imgRealce.cols; j++) {
          if (not (i>punto1[1] and i < punto2[1] and j > punto1[0] and j < punto2[0])) {
            cv::Vec3b v1 = imgRealce.at<cv::Vec3b>(i, j);
            negro=(int)((v1[0]+v1[1]+v1[2])/3);
            v1[0]=negro;
            v1[1]=negro;
            v1[2]=negro;
            imgRealce.at<cv::Vec3b>(i, j)=v1;
          }
        }
      }


      cv::imshow("IMG", imgRealce);
      key=cv::waitKey(0) & 0xff;
      if (key!=27) {
        imwrite(parser.get<cv::String>(1),imgRealce);
      }


  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
