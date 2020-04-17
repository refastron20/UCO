#include <iostream>
#include <exception>
#include <cassert>
//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//parametros de linea de comandos
const cv::String keys =
    "{help h usage ? |          | print this message   }"
    "{i interactive|      | activate interactive mode   }"
    "{f tipo         |  0       | type of filter   }"
    "{g ganancia     |  1.0     | ganancia  }"
    "{@inputImage    |<none>    | image to edit   }"
    "{@outputImage   |salida.jpg| name of the output image  }"
    ;

cv::Mat create_sharp_filter(const int &tipo, const float &g){
  assert(tipo==0 or tipo==1);
  cv::Mat filter( 3, 3, CV_32FC1);
  if (tipo==0) {
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

void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out, int border_type=0){
  assert(in.type()==CV_32FC1);
  assert(filter.type()==CV_32FC1);
  int padrows = filter.rows-1;
	int padcols = filter.cols-1;

	cv::Mat aux = cv::Mat::zeros(in.rows+padrows, in.cols+padcols, CV_32F);
	cv::Mat reserva = cv::Mat::zeros(in.rows+padrows, in.cols+padcols, CV_32F);

  cv::Mat roi = aux(cv::Rect(padcols/2,padrows/2,in.cols,in.rows));
  in.copyTo(roi);

  aux.copyTo(reserva);

  for (int i = padrows/2; i < aux.rows-padrows/2; i++) {
    for (int j = padcols/2; j < aux.cols-padcols/2; j++) {
      float sum=0;
      for (int n = 0; n < padrows; n++) {
        for (int m = 0; m < padcols; m++) {
          sum+= reserva.at<float>(i+n-1,j+m-1)*filter.at<float>(n,m);
        }
      }
      aux.at<float>(i,j)=sum;
    }
  }

  roi.copyTo(out);
}

int main (int argc, char* const* argv){
      int retCode=EXIT_SUCCESS;

      try {


        cv::CommandLineParser parser(argc, argv, keys);
        float g=parser.get<float>("g");
        int f=parser.get<float>("f");
        parser.about("Aplica un sharp filter");
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


      cv::Mat img = imread(img_name, cv::IMREAD_COLOR);

      if (img.empty())
      {
         std::cerr << "Error: no he podido abrir el fichero '" << img_name << "'." << std::endl;
         return EXIT_FAILURE;
      }

      cv::Mat mask = create_sharp_filter(f,g);

      std::vector<cv::Mat> splitChannels(3);
      std::vector<cv::Mat> mergeChannels(3);

      cv::namedWindow("IMG");
      cv::namedWindow("IMG2");

      cv::Mat merge;
      img.convertTo(merge, CV_32FC3, 1/255.0 );

      cv::split(merge, splitChannels);

      //llamo a mi funcion convolve
  		convolve(splitChannels[0], mask, mergeChannels[0]);
  		convolve(splitChannels[1], mask, mergeChannels[1]);
  		convolve(splitChannels[2], mask, mergeChannels[2]);

      cv::merge(mergeChannels, merge);



      cv::imshow("IMG", img);
  		cv::imshow("IMG2", merge);
      cv::waitKey();



  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
