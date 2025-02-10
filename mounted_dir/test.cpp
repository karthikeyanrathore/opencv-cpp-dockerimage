// made some changes 
// check if these changes are shown in docker container
//
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){

  cout << "check if OpenCV lib is correctly installed" << endl;
  cout << "edge detection on image.. " << endl;
  // This detects both horizontal and vertical edges 
  // Sobel Derivatives

  // Sobel filter
  //
  
  Mat src, img, src_gray;
  // read image
  img = imread("Nj9fM.png", IMREAD_COLOR);
  
  // reduce noise
  GaussianBlur(img, src, Size(3,3), 0, 0, BORDER_DEFAULT);

  // convert it to grayscale image
  cvtColor(src, src_gray, COLOR_BGR2GRAY);

 // following this blog: https://docs.opencv.org/4.x/d2/d2c/tutorial_sobel_derivatives.html
 // we now need to take derivatice in both x and y plane to get the difference in intensity 
 // from 1 point to its neightbors points.

  Mat grad_x, grad_y, grad, abs_grad_x, abs_grad_y;
  // detects horizontal edges
  // X
  // ddepth: CV_16S to avoid overflow during gradient calculation
  Sobel(src_gray, grad_x, CV_16S, 1, 0, -1, 1, 0, BORDER_DEFAULT);
  // detects vertical edges
  // Y 
  Sobel(src_gray, grad_y, CV_16S, 0, 1, -1, 1, 0, BORDER_DEFAULT);

  // convert output to CV_8U image
  convertScaleAbs(grad_x, abs_grad_x);
  convertScaleAbs(grad_y, abs_grad_y);

  // gradient add up
  addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

  // write image to disk
  imwrite("grad_newimage.png", grad);

}

