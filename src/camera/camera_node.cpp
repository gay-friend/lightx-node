#include "camera_node.h"

namespace fs = std::filesystem;

NODE_API Node *create_node(QWidget *parent)
{
    return new CameraNode(NODE_NAME, NODE_TYPE);
}
const char *get_node_name()
{
    return NODE_NAME.c_str();
}
const char *get_node_type()
{
    return get_node_type_name(NODE_TYPE);
}

CameraNode::CameraNode(const std::string &node_name, Type node_type) : Node(node_name, node_type)
{
    this->m_im_port = add_port(0, "图", Port::Output, Port::Image);
    this->m_path_port = add_port(0, "路径", Port::Input, Port::File);
    m_build_widget();
    this->init();
    QObject::connect(this->m_path_port, &Port::on_value_change, [this](QVariant *data)
                     { this->init(); });
}
void CameraNode::init()
{
    auto dir = this->m_path_port->get_value<std::string>();
    fs::path path(dir);
    if (!fs::exists(path))
    {
        return;
    }
    fs::directory_entry entry(path);
    if (entry.status().type() != fs::file_type::directory)
    {
        return;
    }

    for (auto it : fs::directory_iterator(dir))
    {
        m_image_files.push_back(it.path().generic_string());
    }
}
void CameraNode::uninit()
{
}

void CameraNode::execute()
{
    if (m_image_files.size() == 0)
    {
        return;
    }
    m_index = m_index >= m_image_files.size() ? 0 : m_index;
    auto filename = m_image_files[m_index];
    auto mat = cv::imread(filename, cv::IMREAD_COLOR);
    this->m_im_port->set_value(mat);
    m_index++;
    std::cout << filename << std::endl;
    std::cout << "CameraNode running...222" << std::endl;
}
