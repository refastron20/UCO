#include <iostream>
#include <exception>
//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//Funciones de realce
#include "enhanceFunctions.hpp"

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@inputImage    |<none>| image to edit   }"
    "{@outputImage   |out.jpg| name of the output image  }"
    ;

int main(int argc, char const *argv[]) {
  int retCode=EXIT_SUCCESS;

  try{

    //Configuramos el parser
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Este programa sirve para hacer el realce de una imagen en el rectangulo definido por dos clicks de ratón");
    if (parser.has("help")) {
      parser.printMessage();
      return retCode;
    }

    //Declaramos la imagen recibida por linea de comandos
    //Obtenemos el nombre
    cv::String nameOfImageToEnhance = parser.get<cv::String>(0);

    //Cargamos la imagen en una matriz de opencv
    cv::Mat imageToEnhance = cv::imread(nameOfImageToEnhance, cv::IMREAD_COLOR);

    //Comprobamos que no esté vacía
    if (imageToEnhance.empty()) {
      std::cerr << "The image <" << nameOfImageToEnhance << "> couldn't been load." << '\n';
      return retCode;
    }

    //Obtenemos el nombre para la imagen de salida
    cv::String nameOfTheFinalEnhanceImage = parser.get<cv::String>(1);

    enhanceImageFunction(imageToEnhance,nameOfTheFinalEnhanceImage);

  }catch(std::exception& e){
    std::cout << "Exception: " << e.what() << '\n';
    retCode=EXIT_FAILURE;
  }

  return retCode;
}
