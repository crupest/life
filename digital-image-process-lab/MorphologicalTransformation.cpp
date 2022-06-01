#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

cv::Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

void Erosion(int, void *);
void Dilation(int, void *);

int main(int argc, char **argv) {

  cv::CommandLineParser parser(argc, argv,
                               "{@input | LinuxLogo.jpg | input image}");
  src = imread(cv::samples::findFile(parser.get<cv::String>("@input")),
               cv::IMREAD_COLOR);
  if (src.empty()) {
    std::cout << "Could not open or find the image!\n" << std::endl;
    std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
    return -1;
  }
  namedWindow("Erosion Demo", cv::WINDOW_AUTOSIZE);
  namedWindow("Dilation Demo", cv::WINDOW_AUTOSIZE);
  cv::moveWindow("Dilation Demo", src.cols, 0);
  cv::createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse",
                     "Erosion Demo", &erosion_elem, max_elem, Erosion);
  cv::createTrackbar("Kernel size:\n 2n +1", "Erosion Demo", &erosion_size,
                     max_kernel_size, Erosion);
  cv::createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse",
                     "Dilation Demo", &dilation_elem, max_elem, Dilation);
  cv::createTrackbar("Kernel size:\n 2n +1", "Dilation Demo", &dilation_size,
                     max_kernel_size, Dilation);
  Erosion(0, 0);
  Dilation(0, 0);
  cv::waitKey(0);
  return 0;
}

void Erosion(int, void *) {
  int erosion_type = 0;
  if (erosion_elem == 0) {
    erosion_type = cv::MORPH_RECT;
  } else if (erosion_elem == 1) {
    erosion_type = cv::MORPH_CROSS;
  } else if (erosion_elem == 2) {
    erosion_type = cv::MORPH_ELLIPSE;
  }
  cv::Mat element = getStructuringElement(
      erosion_type, cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
      cv::Point(erosion_size, erosion_size));
  cv::erode(src, erosion_dst, element);
  imshow("Erosion Demo", erosion_dst);
}

void Dilation(int, void *) {
  int dilation_type = 0;
  if (dilation_elem == 0) {
    dilation_type = cv::MORPH_RECT;
  } else if (dilation_elem == 1) {
    dilation_type = cv::MORPH_CROSS;
  } else if (dilation_elem == 2) {
    dilation_type = cv::MORPH_ELLIPSE;
  }
  cv::Mat element = getStructuringElement(
      dilation_type, cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
      cv::Point(dilation_size, dilation_size));
  dilate(src, dilation_dst, element);
  imshow("Dilation Demo", dilation_dst);
}
