#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

cv::Mat src, src_gray;
int thresh = 100;
int max_thresh = 255;
const char *source_window = "Source image";
const char *corners_window = "Corners detected";
void cornerHarris_demo(int, void *);
int main(int argc, char **argv) {
  cv::CommandLineParser parser(argc, argv,
                               "{@input | building.jpg | input image}");
  src = cv::imread(cv::samples::findFile(parser.get<cv::String>("@input")));
  if (src.empty()) {
    std::cout << "Could not open or find the image!\n" << std::endl;
    std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
    return -1;
  }
  cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
  cv::namedWindow(source_window);
  cv::createTrackbar("Threshold: ", source_window, &thresh, max_thresh,
                     cornerHarris_demo);
  cv::imshow(source_window, src);
  cornerHarris_demo(0, 0);
  cv::waitKey();
  return 0;
}

void cornerHarris_demo(int, void *) {
  int blockSize = 2;
  int apertureSize = 3;
  double k = 0.04;
  cv::Mat dst = cv::Mat::zeros(src.size(), CV_32FC1);
  cv::cornerHarris(src_gray, dst, blockSize, apertureSize, k);
  cv::Mat dst_norm, dst_norm_scaled;
  normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
  convertScaleAbs(dst_norm, dst_norm_scaled);
  for (int i = 0; i < dst_norm.rows; i++) {
    for (int j = 0; j < dst_norm.cols; j++) {
      if ((int)dst_norm.at<float>(i, j) > thresh) {
        circle(dst_norm_scaled, cv::Point(j, i), 5, cv::Scalar(0), 2, 8, 0);
      }
    }
  }
  cv::namedWindow(corners_window);
  cv::imshow(corners_window, dst_norm_scaled);
}
