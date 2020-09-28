//! \file test_lbp.cpp
//! \author FSIV-UCO

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "lbp.h"

using namespace std;

const cv::String keys =
    "{help h usage ? |      | print this message.}"
//    "{u uniform      |      | use uLBP.}"
//    "{c colunms      |0     | Build descriptor using a grid with c colums.}"
//    "{r rows         |0     | Build descriptor using a grid with r rows.}"
    "{@image1        |<none>| path to input image.}"
    "{@image2        |      | path to second image, for comparison.}"
    ;

int main(int argc, char * argv[])
{
   cv::CommandLineParser parser(argc, argv, keys);
   parser.about("Test LBP implementation.");
   if (parser.has("help"))
   {
      parser.printMessage();
      return 0;
   }

   cv::Mat image1;
   image1=cv::imread(parser.get<cv::String>(0),cv::IMREAD_COLOR);


   cv::Mat image2;

   if (!parser.get<cv::String>(1).empty()) {
     image2=cv::imread(parser.get<cv::String>(1),cv::IMREAD_COLOR);
   }else{
     cv::flip(image1,image2,0);
   }

   cv::Mat img1Gray,img2Gray;

   cv::cvtColor(image1,img1Gray,cv::COLOR_BGR2GRAY);
   cv::cvtColor(image2,img2Gray,cv::COLOR_BGR2GRAY);
   cv::Mat lbp1,lbp2;
   fsiv_lbp(img1Gray,lbp1);
   fsiv_lbp(img2Gray,lbp2);

   fsiv_lbp_disp(lbp1,"IMG1");
   fsiv_lbp_disp(lbp2,"IMG2");


   cv::Mat lbp_h1, lbp_h2;
   fsiv_lbp_hist(lbp1,lbp_h1);
   fsiv_lbp_hist(lbp2,lbp_h2);


	float dist = 0.0;
  dist = fsiv_chisquared_dist(lbp_h1,lbp_h2);



   std::cerr << "Distance between image1, image2 = " << dist << std::endl;
	std::cout << "End! " <<std::endl;

   return 0;
}
