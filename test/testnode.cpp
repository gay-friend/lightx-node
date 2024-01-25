#include "node/node.h"
#include "utils/common.h"
#include "opencv2/opencv.hpp"

NODE_API Node *create_node(QWidget *parent)
{
    return nullptr;
}
NODE_API const char *get_node_name()
{
    cv::imread("test.png");
    return "get_node_name";
}
NODE_API const char *get_node_type()
{
    return "get_node_type";
}