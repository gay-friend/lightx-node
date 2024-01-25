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
    this->m_im_port = add_pair_port(0, "图", Port::Image, true);
    this->m_res_port = add_port(1, "结果图", Port::Output, Port::Image);
    std::vector<std::string> items = {"BGR2RGB",
                                      "RGB2BGR",
                                      "BGR2GRAY",
                                      "RGB2GRAY",
                                      "GRAY2BGR",
                                      "GRAY2RGB"};
    this->m_cv_type_port = add_port(1, "转换类型", Port::Input, Port::Enum, items);
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
    auto mat = this->m_im_port->get_value<cv::Mat>();
    auto cvt_type = this->m_cv_type_port->get_value<std::string>();

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
                this->m_res_port->set_value(res);
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
                this->m_res_port->set_value(res);
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
    this->m_res_port->set_value(res);

    std::cout << "CvtColorNode running..." << std::endl;
}