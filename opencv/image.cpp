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

  FastFeatureDetector detector(100);
  vector<KeyPoint> keypoints;
  detector.detect(img, keypoints);
  
  
  namedWindow("matches", 1);
  Mat img_keypoints;
  drawKeypoints( img, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
  imshow("matches", img_keypoints);
  waitKey(0);
  
  // find the top most point.
  KeyPoint * topMostPoint = NULL;
  for (int i = 0; i < keypoints.size(); i++) {
    if(topMostPoint == NULL || keypoints[i].pt.y < topMostPoint->pt.y) {
      topMostPoint = &keypoints[i];
    }
  }
  // render the top point as a check;
  vector<KeyPoint> topPoint;
  topPoint.push_back(*topMostPoint);
  
  namedWindow("top match", 1);
  Mat img_keypoints2;
  drawKeypoints( img, topPoint, img_keypoints2, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
  imshow("top match", img_keypoints2);
  waitKey(0);
 
  // work out how far from the middle it is
  int midY = img.rows / 2;
  int midX = img.cols / 2;
  
  double diffX = topMostPoint->pt.x - midX;
  double diffY = topMostPoint->pt.y - midY;
  
  printf("images: %d : %d \nkeypoint: %f : %f\ndiff: %f : %f\n", midX, midY, topMostPoint->pt.x, topMostPoint->pt.y, diffX, diffY);
  
  
  // work out where we need to move next to make this in the middle 
  // (middle for now, we probably want to adjust the target point for the drone and hook combo)
  
  
  return 0;
}
