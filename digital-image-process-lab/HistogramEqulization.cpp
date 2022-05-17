#include <iostream>
#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Please input an image file path as the only arg."
              << std::endl;
    return -1;
  }

  std::string file_name(argv[1]);

  cv::Mat src, dst;

  src = cv::imread(file_name, cv::IMREAD_COLOR);
  if (src.empty()) {
    std::cerr << "Failed to load image file: " << file_name << std::endl;
    return -2;
  }

  cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);

  cv::equalizeHist(src, dst);

  cv::imshow("Source Image", src);
  cv::imshow("Equalized Image", dst);
  cv::waitKey();

  return 0;
}
