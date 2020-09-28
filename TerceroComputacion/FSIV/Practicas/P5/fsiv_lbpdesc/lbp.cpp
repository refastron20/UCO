//! \file lbp.cpp
//! Utils for LBP

#include "lbp.h"
#include <vector>
#include <iostream>

using namespace std;

static const int uniform[256] =
{
0,1,2,3,4,58,5,6,7,58,58,58,8,58,9,10,11,58,58,58,58,58,58,58,12,58,58,58,13,58,
14,15,16,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,17,58,58,58,58,58,58,58,18,
58,58,58,19,58,20,21,22,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,58,58,58,58,58,58,58,58,58,58,58,23,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,58,24,58,58,58,58,58,58,58,25,58,58,58,26,58,27,28,29,30,58,31,58,58,58,32,58,
58,58,58,58,58,58,33,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,34,58,58,58,58,
58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,35,36,37,58,38,58,58,58,39,58,58,58,58,58,58,58,40,58,58,58,58,58,58,58,58,58,
58,58,58,58,58,58,41,42,43,58,44,58,58,58,45,58,58,58,58,58,58,58,46,47,48,58,49,
58,58,58,50,51,52,58,53,54,55,56,57
};

uchar getCode(std::vector<uchar> &v, const uchar &medio){
  for (int i = 0; i < v.size(); i++) {
    if (v[i]>=medio) {
      v[i]=0;
    }else{
      v[i]=1;
    }
  }
  uchar suma=0;
  for (int i = 0; i < v.size(); i++) {
    if (v[i]) {
      suma+=pow(2,i);
    }
  }
  return suma;
}

void fsiv_lbp(const cv::Mat & imagem, cv::Mat & lbp)
{

    assert(imagem.type()==CV_8UC1);
    lbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);

    cv::Mat aux;
    cv::copyMakeBorder(imagem,aux,1,1,1,1,cv::BORDER_CONSTANT,0);

    for (int i = 1; i < aux.rows-1; i++) {
      for (int j = 1; j < aux.cols-1; j++) {
        std::vector<uchar> v={
          aux.at<uchar>(i,j-1),
          aux.at<uchar>(i+1,j-1),
          aux.at<uchar>(i+1,j),
          aux.at<uchar>(i+1,j+1),
          aux.at<uchar>(i,j+1),
          aux.at<uchar>(i-1,j+1),
          aux.at<uchar>(i-1,j),
          aux.at<uchar>(i-1,j-1),
        };
        lbp.at<uchar>(i-1,j-1)=getCode(v,aux.at<uchar>(i,j));
      }
    }
}

void fsiv_ulbp(const cv::Mat & imagem, cv::Mat & ulbp)
{
    ulbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);
	//TODO compute u-LBP codes.
}

void fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, bool normalize, int nbins)
{
	 lbp_hist == cv::Mat::zeros(1, nbins, CV_32FC1);
   float ranges[] = {0, 256};
   const float *PointerRanges[]={ranges};
   cv::calcHist( &lbp, 1, 0, cv::Mat(), lbp_hist, 1, &nbins, PointerRanges);

    // Normalize?
    if (normalize)
    {
		cv::normalize(lbp_hist,lbp_hist,0,1,cv::NORM_MINMAX);
    }
}

void fsiv_lbp_desc(const cv::Mat & image, cv::Mat & lbp_desc, const int *ncells, bool normalize, int nbins)
{
	//TODO compute lbp desc.
    if (normalize)
    {
		//TODO normaliza lbp_desc to mett cv::sum(lbp_desc)[0] == 1.0
		;
    }
}

void fsiv_lbp_disp(const cv::Mat & lbpmat, const std::string & winname)
{
	cv::namedWindow(winname);
  cv::imshow(winname,lbpmat);
  cv::waitKey(0);
}

float fsiv_chisquared_dist(const cv::Mat & h1, const cv::Mat & h2)
{
	 float dist= 0.0;
	  for (int i = 0; i < h1.cols; i++) {
      float x=(h1.at<float>(0,i)-h2.at<float>(0,i));
      float y=(h1.at<float>(0,i)+h2.at<float>(0,i));
      if (y==0){
        y=1;
      }
      dist+=(x*x)/(y);
    }
    return dist*0.5;
}
