#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

// Texture2D能够在OpenGL中存储和配置纹理
// 它还承载实用函数，以便于管理
class Texture2D
{
public:
    // 保存纹理对象的ID，用于引用该特定纹理的所有纹理操作
    unsigned int ID;
    // 纹理图像尺寸
    unsigned int Width, Height; // 载入图像的宽度和高度(以像素为单位)
    // 纹理格式
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image
    // 纹理配置
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels
    // 默认构造函数(设置默认纹理模式)
    Texture2D();
    // 从图像数据生成纹理
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    // 绑定当前纹理为当前活动的GL_TEXTURE_2D纹理对象
    void Bind() const;
};

#endif