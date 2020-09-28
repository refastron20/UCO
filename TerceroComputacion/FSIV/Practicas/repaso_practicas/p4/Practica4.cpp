/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <exception>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;

std::vector<Point3f> create_obj_points(int cols,int rows,float size){
  std::vector<Point3f> v;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      v.push_back(Point3f(i*size,j*size,0));
    }
  }
  return v;
}

void draw_model(Mat &img, const float &size, const Mat &camera_mat, const Mat &coef_mat, const Mat &rvec, const Mat &tvec){
  std::vector<Point2f> img_points;
  std::vector<Point3f> ejes=
  {Point3f(0,0,0)/*0*/,Point3f(2*size,0,0)/*1*/,Point3f(0,2*size,0)/*2*/,Point3f(0,0,2*size)/*3*/,
    Point3f(0,2*size,2*size)/*4*/,Point3f(2*size,2*size,0)/*5*/,Point3f(2*size,0,2*size)/*6*/,Point3f(2*size,2*size,2*size)/*7*/};
  projectPoints(ejes,rvec,tvec,camera_mat,coef_mat,img_points);
  //Base
  line(img,img_points[0],img_points[1],Scalar(255,0,0),1);//
  line(img,img_points[1],img_points[5],Scalar(255,0,0),1);//
  line(img,img_points[0],img_points[2],Scalar(255,0,0),1);//
  line(img,img_points[5],img_points[2],Scalar(255,0,0),1);//
  //aristas verticales
  line(img,img_points[0],img_points[3],Scalar(0,255,0),1);//
  line(img,img_points[1],img_points[6],Scalar(0,255,0),1);//
  line(img,img_points[2],img_points[4],Scalar(0,255,0),1);//
  line(img,img_points[5],img_points[7],Scalar(0,255,0),1);//
  //Cuadrado superior
  line(img,img_points[3],img_points[4],Scalar(0,0,255),1);//
  line(img,img_points[4],img_points[7],Scalar(0,0,255),1);//
  line(img,img_points[7],img_points[6],Scalar(0,0,255),1);//
  line(img,img_points[6],img_points[3],Scalar(0,0,255),1);//
}

void draw_image(Mat &img,const Mat &img2, const int &cols,const int &rows, const float &size, const Mat &camera_mat, const Mat &coef_mat, const Mat &rvec, const Mat &tvec){
  std::vector<Point2f> img_points;
  std::vector<Point3f> ejes={Point3f(-size,-size,0),Point3f(-size,(cols-1)*size,0),Point3f((rows-1)*size,(cols-1)*size,0),Point3f((rows-1)*size,-size,0)};
  projectPoints(ejes,rvec,tvec,camera_mat,coef_mat,img_points);
  std::vector<Point2f> aux2={Point2f(0,0),Point2f(img2.cols,0),Point2f(img2.cols,img2.rows),Point2f(0,img2.rows)};
  Mat aux=getPerspectiveTransform(aux2,img_points);
  Mat img3;
  warpPerspective(img2,img3,aux,Size(img.cols,img.rows));
  std::vector<Point> img_points_int;
  for (int i = 0; i < img_points.size(); i++) {
    img_points_int.push_back(Point((int)img_points[i].x,(int)img_points[i].y));
  }
  fillConvexPoly(img,img_points_int,Scalar(0,0,0));
  img=img|img3;
}

const cv::String keys =
    "{help h usage ?  |      | print this message }"
    "{@rows           |<none>| calib.pattern rows }"
    "{@cols           |<none>| calib.pattern cols }"
    "{@size           |<none>| calib.pattern size }"
    "{@calibfile      |<none>| intrinsics file    }"
    "{@input          |<none>| input video        }"
    "{image i         |<none>| image        }"
    "{video v         |<none>| image        }"
    "{@imageVid       |<none>| input video        }"
    ;

using namespace cv;

int main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;

  try {

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Application name v1.0.0");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      int rows = parser.get<int>(0);
      int cols = parser.get<int>(1);
      float size = parser.get<float>(2);
      String calibfile = parser.get<String>(3);
      String input_file = parser.get<String>(4);
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

      VideoCapture vid;
      vid.open(input_file);
      if (!vid.isOpened()) {
        std::cerr << "No se pudo abrir el vídeo" << '\n';
        return EXIT_FAILURE;
      }

      FileStorage intr(calibfile, FileStorage::READ);
      if (!intr.isOpened()) {
        std::cerr << "No se pudo abrir el archivo" << '\n';
        return EXIT_FAILURE;
      }

      Mat camera_mat;
      Mat coef_mat;
      intr["Camera_Matrix"]>>camera_mat;
      if (camera_mat.empty()) {
        std::cerr << "camera_matrix esta vacía" << '\n';
        return EXIT_FAILURE;
      }
      intr["Distortion_Coefficients"] >> coef_mat;
      if (coef_mat.empty()) {
        std::cerr << "distortion-coefficients esta vacía" << '\n';
        return EXIT_FAILURE;
      }

      namedWindow("VIDEO");
      Mat frame;

      vid >> frame;

      int key=0;

      std::vector<Point3f> obj_pts=create_obj_points(cols-1,rows-1,size);

      String img2Name=parser.get<String>(5);
      Mat img2;

      String vid2Name=parser.get<String>(5);
      VideoCapture vid2;

      if (parser.has("image")) {
        img2=imread(img2Name, cv::IMREAD_COLOR);
      }else if(parser.has("video")){
        vid2.open(vid2Name);
        vid2 >> img2;
        if (!vid.isOpened()){
          std::cerr << "No se pudo abrir el vídeo" << '\n';
          return EXIT_FAILURE;
        }
      }



      while(!frame.empty() and key!=27){
        if (parser.has("video") and img2.empty()) {
          vid2.release();
          vid2.open(vid2Name);
          vid2>>img2;
        }

        std::vector<Point2f> corners;
        if (findChessboardCorners(frame,Size(cols-1,rows-1),corners)) {
          Mat gray;
          cvtColor(frame,gray,COLOR_BGR2GRAY);
          cornerSubPix(gray,corners,Size(11,11),Size(-1,-1),TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));
          Mat rvec, tvec;
          solvePnP(obj_pts, corners, camera_mat, coef_mat, rvec, tvec);
          if (parser.has("image") or parser.has("video")) {
            draw_image(frame,img2,cols,rows,size,camera_mat, coef_mat, rvec, tvec);
          }else{
            draw_model(frame, size, camera_mat, coef_mat, rvec, tvec);
          }
          imshow("VIDEO",frame);
        }else{
          imshow("VIDEO",frame);
        }


        if (parser.has("video")) {
          vid2>>img2;
        }
        vid >> frame;
        key=cv::waitKey(20);
      }
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
