#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;
int main(int argc, char ** argv) {

  Mat img = imread("./IMG_3117_small.jpg");
  
  if( !img.data )
  {
    printf( "No image data \n" );
    return -1;
  }
  
  printf("loaded image\n");
  namedWindow("image", CV_WINDOW_AUTOSIZE);
  printf("created window\n");
  imshow("image", img);
  printf("shown image\n");
  waitKey(0); 
  
  FastFeatureDetector detector(100);
  vector<KeyPoint> keypoints;
  detector.detect(img, keypoints);
  
  
  namedWindow("matches", 1);
  Mat img_keypoints;
  drawKeypoints( img, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
  imshow("matches", img_keypoints);
  waitKey(0);
  
  return 0;
}
