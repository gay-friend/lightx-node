#include <opencv2/opencv.hpp>

int main()
{
    auto im = cv::imread("E:\\lightx\\lightx-node\\build\\bin\\Debug\\1.png");
    cv::imwrite("11.png", im);
    return 0;
}