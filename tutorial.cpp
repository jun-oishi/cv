# include <opencv2/opencv.hpp>
# include <iostream>
using namespace std;

int main() {
  string filename;
  cin >> filename;
  cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
  vector<cv::Mat> channels;
  cv::split(image, channels);

  string window = "window";
  cv::namedWindow(window, cv::WINDOW_AUTOSIZE);
  cv::imshow(window, channels[1]);
  cv::waitKey(0);
}