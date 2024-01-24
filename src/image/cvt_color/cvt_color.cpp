#include "cvt_color.h"

NODE_API Node *create_node(QWidget *parent)
{
    return new CvtColorNode(NODE_NAME, NODE_TYPE);
}
const char *get_node_name()
{
    return NODE_NAME.c_str();
}
const char *get_node_type()
{
    return get_node_type_name(NODE_TYPE);
}

CvtColorNode::CvtColorNode(const std::string &node_name, Type node_type) : Node(node_name, node_type)
{
    add_pair_port(0, "im", Port::Image, true);
    add_port(1, "res im", Port::Output, Port::Image);
    auto port = add_port(1, "cvt type", Port::Input, Port::Enum);
    port->set_combo_items({"BGR2RGB", "RGB2BGR", "BGR2GRAY", "RGB2GRAY", "GRAY2BGR", "GRAY2RGB"});
    m_build_widget();
}

void CvtColorNode::init()
{
}
void CvtColorNode::uninit()
{
}
void CvtColorNode::execute()
{
    auto mat = get_port_value<cv::Mat>(0, Port::InputForce);
    auto cvt_type = get_port_value<std::string>(1, Port::Input);

    cv::Mat res;
    auto cvt_color_type = cv::COLOR_BGR2GRAY;
    if (cvt_type == "BGR2RGB")
    {
        if (mat.type() != CV_8UC3)
        {
            std::cout << "im not CV_8UC3" << std::endl;
            return;
        }
        cvt_color_type = cv::COLOR_BGR2RGB;
    }
    else if (cvt_type == "RGB2BGR")
    {
        if (mat.type() != CV_8UC3)
        {
            std::cout << "im not CV_8UC3" << std::endl;
            return;
        }
        cvt_color_type = cv::COLOR_RGB2BGR;
    }
    else if (cvt_type == "BGR2GRAY")
    {
        if (mat.type() != CV_8UC3)
        {
            std::cout << "im not CV_8UC3" << std::endl;
            if (mat.type() == CV_8UC1)
            {
                res = mat.clone();
                set_port_value(1, Port::Output, res);
            }
            return;
        }
        cvt_color_type = cv::COLOR_BGR2GRAY;
    }
    else if (cvt_type == "RGB2GRAY")
    {
        if (mat.type() != CV_8UC3)
        {
            std::cout << "im not CV_8UC3" << std::endl;
            if (mat.type() == CV_8UC1)
            {
                res = mat.clone();
                set_port_value(1, Port::Output, res);
            }
            return;
        }
        cvt_color_type = cv::COLOR_RGB2GRAY;
    }
    else if (cvt_type == "GRAY2BGR")
    {
        if (mat.type() != CV_8UC1)
        {
            std::cout << "im not CV_8UC1" << std::endl;
            return;
        }
        cvt_color_type = cv::COLOR_GRAY2BGR;
    }
    else if (cvt_type == "GRAY2RGB")
    {
        if (mat.type() != CV_8UC1)
        {
            std::cout << "im not CV_8UC1" << std::endl;
            return;
        }
        cvt_color_type = cv::COLOR_GRAY2RGB;
    }

    cv::cvtColor(mat, res, cvt_color_type);
    // 输出灰度图
    set_port_value(1, Port::Output, res);

    std::cout << "CvtColorNode running..." << std::endl;
}