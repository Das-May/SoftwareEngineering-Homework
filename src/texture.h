#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

// Texture2D�ܹ���OpenGL�д洢����������
// ��������ʵ�ú������Ա��ڹ���
class Texture2D
{
public:
    // ������������ID���������ø��ض�����������������
    unsigned int ID;
    // ����ͼ��ߴ�
    unsigned int Width, Height; // ����ͼ��Ŀ�Ⱥ͸߶�(������Ϊ��λ)
    // �����ʽ
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image
    // ��������
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels
    // Ĭ�Ϲ��캯��(����Ĭ������ģʽ)
    Texture2D();
    // ��ͼ��������������
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    // �󶨵�ǰ����Ϊ��ǰ���GL_TEXTURE_2D�������
    void Bind() const;
};

#endif