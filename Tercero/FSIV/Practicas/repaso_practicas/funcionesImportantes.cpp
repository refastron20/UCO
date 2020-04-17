//basico

//CommandLineParser
cv::CommandLineParser parser(argc, argv, keys);
parser.about("Application name v1.0.0");
if (parser.has("help"))
{
    parser.printMessage();
    return 0;
}
int algo = parser.get<int>(0);

//declarar imagen
cv::String imgName = parser.get<cv::String>(0);
cv::Mat img = cv::imread(imgName, cv::IMREAD_COLOR);
if (imageToEnhance.empty()) {
  std::cerr << "The image <" << nameOfImageToEnhance << "> couldn't been load." << '\n';
  return retCode;
}

//mostrar imagen
cv::namedWindow(winname);
cv::imshow(winname,img);
cv::waitKey(0);

//declarar video
VideoCapture vid;
vid.open(vidName);
if (!vid.isOpened()) {
  std::cerr << "No se pudo abrir el vídeo" << '\n';
  return EXIT_FAILURE;
}

//reproducir video
cv::Mat frame;
vid>>frame
while (!frame.empty()) {
  imshow(winname, frame);
  vid>>frame;
  cv::waitKey(20);
}

//Practica 1
cv::setMouseCallback("ENHANCE", on_mouse, coordinates);

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

//Practica 2

//normalizar
img.convertTo(img, CV_32FC3, 1/255.0);

//trackbar
                   //nombre    ventana  valor inicial  tope  funcion      datos
cv::createTrackbar("contraste", "IMG", &data.contraste, 200, on_trackbar, &data);
//  siempre 0   datos
on_trackbar(0, &data);

//modificar contraste, gamma y brillo
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


//practica 3

//filtro de mierda
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

//convolucion de mierda

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

//Practica 4

//puntos objeto
std::vector<Point3f> create_obj_points(int cols,int rows,float size){
  std::vector<Point3f> v;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      v.push_back(Point3f(i*size,j*size,0));
    }
  }
  return v;
}

//funciones del main
                    //imagen //tamaño          //vector vacío
findChessboardCorners(frame,Size(cols-1,rows-1),corners)
Mat gray;
cvtColor(frame,gray,COLOR_BGR2GRAY);
      //imagen vector de esquinas todo igual
cornerSubPix(gray,corners,Size(11,11),Size(-1,-1),TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));
Mat rvec, tvec;
        //           matrices del archivo raro   matrices mágicas
solvePnP(obj_pts, corners, camera_mat, coef_mat, rvec, tvec);

//pa dibujar cosicas
std::vector<Point3f> ejes=
{Point3f(0,0,0)/*0*/,Point3f(2*size,0,0)/*1*/,Point3f(0,2*size,0)/*2*/,Point3f(0,0,2*size)/*3*/,
  Point3f(0,2*size,2*size)/*4*/,Point3f(2*size,2*size,0)/*5*/,Point3f(2*size,0,2*size)/*6*/,Point3f(2*size,2*size,2*size)/*7*/};
projectPoints(ejes,rvec,tvec,camera_mat,coef_mat,img_points);


//Practica 5

//obtener lbp
uchar getCode(const std::vector<uchar> &v){
  std::vector<uchar> binary = {128,64,32,16,8,4,2,1};
  uchar suma=0;
  for (int i = 1; i < v.size(); i++) {
    if (v[i]>=v[0]) {
      suma+=binary[i-1];
    }
  }
  return suma;
}


void fsiv_lbp(const cv::Mat & imagem, cv::Mat & lbp)
{
  assert(imagem.type()==CV_8UC1);

  lbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);

  cv::Mat readAuxImage = cv::Mat::zeros(imagem.rows+2, imagem.cols+2, CV_8UC1);
  cv::copyMakeBorder(imagem, readAuxImage, 1, 1, 1, 1, cv::BORDER_CONSTANT, 0);

  for (int i = 1; i < readAuxImage.rows-1; i++) {
    for (int j = 1; j < readAuxImage.cols-1; j++) {
      std::vector<uchar> v={readAuxImage.at<uchar>(i,j), readAuxImage.at<uchar>(i,j-1), readAuxImage.at<uchar>(i+1,j-1),
        readAuxImage.at<uchar>(i+1,j), readAuxImage.at<uchar>(i+1,j+1), readAuxImage.at<uchar>(i,j+1),
        readAuxImage.at<uchar>(i-1,j+1), readAuxImage.at<uchar>(i-1,j), readAuxImage.at<uchar>(i-1,j-1),
      };
      lbp.at<uchar>(i-1,j-1) = getCode(v);
    }
  }
}


//histograma

void fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, bool normalize, int nbins)
{
  float ranges[] = {0, 256};
  const float *pointer = {ranges};
  cv::calcHist(&lbp, 1, 0, cv::Mat(), lbp_hist, 1, &nbins, &pointer);

  lbp_hist = lbp_hist.reshape(0, 1);

  if (normalize) {
    cv::normalize(lbp_hist, lbp_hist, 0, 1, cv::NORM_MINMAX);
  }

}

//chi maincra
float fsiv_chisquared_dist(const cv::Mat & h1, const cv::Mat & h2)
{
  float suma = 0;
  for (int i = 0; i < h1.cols; i++) {
    float x = h1.at<float>(0,i)-h2.at<float>(0,i);
    float y = h1.at<float>(0,i)+h2.at<float>(0,i);
    if (y == 0.0) {
      y = 1;
    }
    suma+=(x*x)/y;
  }
  return 0.5*suma;
}
