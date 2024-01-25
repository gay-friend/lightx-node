#include "threshold_node.h"

NODE_API Node *create_node(QWidget *parent)
{
    return new ThresholdNode(NODE_NAME, NODE_TYPE);
}
const char *get_node_name()
{
    return NODE_NAME.c_str();
}
const char *get_node_type()
{
    return get_node_type_name(NODE_TYPE);
}

ThresholdNode::ThresholdNode(const std::string &node_name, Type node_type) : Node(node_name, node_type)
{

    this->m_im_port = add_pair_port(0, "图", Port::Image, true);
    this->m_th_port = add_port(1, "阈值", Port::Input, Port::Int);
    this->m_res_port = add_port(1, "二值化图", Port::Output, Port::Image);
    m_build_widget();
}

void ThresholdNode::init()
{
}
void ThresholdNode::uninit()
{
}
void ThresholdNode::execute()
{

    auto mat = this->m_im_port->get_value<cv::Mat>();
    auto th = this->m_th_port->get_value<int>();

    if (mat.empty())
    {
        std::cout << "ThresholdNode get empty input exit..." << std::endl;
        return;
    }

    cv::Mat gray;
    if (mat.type() == CV_8UC1)
    {
        gray = mat.clone();
    }
    else
    {
        cv::cvtColor(mat, gray, cv::COLOR_BGR2GRAY);
    }

    cv::Mat bin_mat;
    cv::threshold(gray, bin_mat, th, 255, cv::THRESH_BINARY);
    this->m_res_port->set_value(bin_mat);
}