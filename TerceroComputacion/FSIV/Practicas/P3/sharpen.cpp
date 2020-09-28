#include <iostream>
#include <exception>
#include <cassert>
//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

struct Datos{
  cv::Mat vectorImg[2];
  int opciones[2];
};

//parametros de linea de comandos
const String keys =
    "{help h usage ? |          | print this message   }"
    "{i interactive|      | activate interactive mode   }"
    "{f tipo         |  0       | type of filter   }"
    "{g ganancia     |  1.0     | ganancia  }"
    "{@inputImage    |<none>    | image to edit   }"
    "{@outputImage   |salida.jpg| name of the output image  }"
    ;

void on_trackbar( int, void* userdata);

Mat create_sharp_filter(int tipo, float g);

void convolve(const Mat& in, const Mat& filter, cv::Mat& out, int border_type=0);

int main (int argc, char* const* argv){
      int retCode=EXIT_SUCCESS;

      try {


        CommandLineParser parser(argc, argv, keys);
        float g=parser.get<float>("g");
        int f=parser.get<float>("f");
        parser.about("Aplica un sharp filter");
        if (parser.has("help"))
        {
          parser.printMessage();
          return 0;
        }
      String img_name = parser.get<String>(0);

      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }


      Mat img = imread(img_name, IMREAD_COLOR);

      if (img.empty())
      {
         std::cerr << "Error: no he podido abrir el fichero '" << img_name << "'." << std::endl;
         return EXIT_FAILURE;
      }


      img.convertTo(img, CV_32FC3);

      int key=0;
      if (!parser.has("interactive")) {
        Mat filter(create_sharp_filter(f, g));
        std::vector <Mat> channels(3);
        std::vector<Mat> mergeChannels(3);

        Mat ejemplo;
        img.copyTo(ejemplo);

        filter2D(ejemplo,ejemplo,-1,filter);

        split(img,channels);


        convolve(channels[0],filter,mergeChannels[0]);
        convolve(channels[1],filter,mergeChannels[1]);
        convolve(channels[2],filter,mergeChannels[2]);

        merge(mergeChannels,img);

        namedWindow("IMG");
        imshow("IMG",ejemplo);
        waitKey(0);

        imshow("IMG",img);
        waitKey(0);

        imshow("IMG",ejemplo-img);
        waitKey(0);

        img.convertTo(img, CV_8UC3);
        imwrite(parser.get<String>(1),img);
      }else{
        namedWindow("IMG");
        Datos datos;
        img.copyTo(datos.vectorImg[0]);
        datos.vectorImg[0].copyTo(datos.vectorImg[1]);
        int gint=g*100;
        datos.opciones[0]=gint;
        datos.opciones[1]=f;
        Datos *datosp=&datos;


        cv::createTrackbar( "Ganancia", "IMG", &datos.opciones[0], 300, on_trackbar, datosp);
        cv::createTrackbar( "Tipo de filtro", "IMG", &datos.opciones[1], 1,on_trackbar, datosp);

        on_trackbar(0, datosp );

        key=cv::waitKey(0) & 0xff;

        if(key!=27){
          imwrite(parser.get<String>(1),datosp->vectorImg[1]);
        }
      }

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}


Mat create_sharp_filter(int tipo, float g){

  assert((tipo==0 or tipo==1) and (g>=0.0));
  Mat filter(3,3,CV_32FC1);

  if(tipo==0){
    filter.at<float>(0,0)=filter.at<float>(0,2)=filter.at<float>(2,0)=filter.at<float>(2,2)=0;
    filter.at<float>(0,1)=filter.at<float>(1,0)=filter.at<float>(1,2)=filter.at<float>(2,1)=-1;
    filter.at<float>(1,1)=g+4;
  }else{
    filter.at<float>(0,0)=filter.at<float>(0,2)=filter.at<float>(2,0)=filter.at<float>(2,2)=
    filter.at<float>(0,1)=filter.at<float>(1,0)=filter.at<float>(1,2)=filter.at<float>(2,1)=-1;
    filter.at<float>(1,1)=g+8;
  }
  return filter;
}

void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out, int border_type){
  assert(in.type()==CV_32FC1);
  assert(filter.type()==CV_32FC1);

  int PadRows=filter.rows-1;
  int PadCols=filter.cols-1;


  Mat aux=Mat::zeros(in.rows+PadRows,in.cols+PadCols,in.type());

  for (int i = 0; i < in.rows; i++) {
    for (int j = 0; j < in.cols; j++) {
      aux.at<float>(i+(PadRows/2),j+(PadCols/2))=in.at<float>(i,j);
    }
  }

  out.create(in.rows,in.cols,in.type());

  float suma;
  for (int i = (PadRows/2); i < aux.rows-(PadRows/2); i++) {
    for (int j = (PadCols/2); j < aux.cols-(PadCols/2); j++) {
      suma=0;
      for (int a = 0; a < filter.rows; a++) {
        for (int b = 0; b < filter.cols; b++) {
          suma+=filter.at<float>(a,b)*aux.at<float>(i-1+a,j-1+b);
        }
      }
      out.at<float>(i-1,j-1)=suma;
    }
  }

}

void on_trackbar( int, void* userdata)
{

  Datos *datos=static_cast<Datos *>(userdata);
  double g = ((double)datos->opciones[0]/100);
  double f = (double)datos->opciones[1];

  cv::Mat imgAux=datos->vectorImg[0];
  cv::Mat imgAux2=datos->vectorImg[1];
  imgAux.copyTo(imgAux2);
  Mat filter(create_sharp_filter(f,g));
  std::vector <Mat> channels(3);
  std::vector<Mat> mergeChannels(3);

  split(imgAux2,channels);

  convolve(channels[0],filter,mergeChannels[0]);
  convolve(channels[1],filter,mergeChannels[1]);
  convolve(channels[2],filter,mergeChannels[2]);

  merge(mergeChannels,imgAux2);
  imgAux2.convertTo(imgAux2, CV_8UC3);
  cv::imshow("IMG", imgAux2);

}
