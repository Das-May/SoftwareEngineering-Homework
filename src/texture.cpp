#include <iostream>

#include "texture.h"


Texture2D::Texture2D()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), 
    Filter_Min(GL_LINEAR_MIPMAP_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);//生成1个纹理，并绑定id
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);//自动生成相应的多级渐远纹理
    // 设置纹理的 wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);// x轴
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);// y轴循环
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);// 纹理缩小过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);// 纹理放大过滤
    // 解绑纹理
    glBindTexture(GL_TEXTURE_2D, 0);// 看，这里是0
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
