#pragma once

#include "node/node.h"
#include "utils/common.h"
// #include "utils/image_utils.hpp"
#include <iostream>
#include <QImage>
#include <filesystem>

/// @brief 创建节点
/// @param pos 坐标
/// @return
NODE_API Node *create_node(QWidget *parent);
NODE_API const char *get_node_name();
NODE_API const char *get_node_type();
static const Node::Type NODE_TYPE{Node::CameraNode};
static const std::string &NODE_NAME{"Camera"};

/// @brief 相机节点
class CameraNode : public Node
{
public:
    CameraNode(const std::string &node_name, Type node_type);
    /// @brief 执行节点
    virtual void execute() override;
    /// @brief 初始化
    virtual void init() override;
    /// @brief 反初始化
    virtual void uninit() override;

private:
    std::vector<std::string> m_image_files;
    int m_index{0};
};
