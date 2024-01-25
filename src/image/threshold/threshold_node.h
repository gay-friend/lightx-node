#pragma once

#include "node/node.h"
#include "utils/common.h"
#include "utils/image_utils.hpp"
#include <QImage>
#include <iostream>

NODE_API Node *create_node(QWidget *parent);
NODE_API const char *get_node_name();
NODE_API const char *get_node_type();
static const Node::Type NODE_TYPE{Node::CameraNode};
static const std::string &NODE_NAME{"Thresold"};

class ThresholdNode : public Node
{
public:
    /// @brief 构造函数
    /// @param pos 坐标
    ThresholdNode(const std::string &node_name, Type node_type);
    /// @brief 执行节点
    virtual void execute() override;
    /// @brief 初始化
    virtual void init() override;
    /// @brief 反初始化
    virtual void uninit() override;

protected:
    Port *m_im_port{nullptr};
    Port *m_res_port{nullptr};
    Port *m_th_port{nullptr};
};