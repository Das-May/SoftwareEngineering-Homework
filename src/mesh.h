#ifndef MESH_H
#define MESH_H

// OpenGL����#error: gl.h included before glew.h
//#include <GL/glew.h>    // https://blog.csdn.net/m0_48776220/article/details/127716715
#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

// ������Ϣ�ṹ�塾ע���Դ����ö�����ɫ�������롿
// layout (location = 0) in vec3 aPos;
// layout(location = 1) in vec3 aNormal;
// layout(location = 2) in vec2 aTexCoords;
struct Vertex {
    // λ��
    glm::vec3 Position;
    // ����
    glm::vec3 Normal;
    // ��������
    glm::vec2 TexCoords;
    // ����
    glm::vec3 Tangent;
    // ������
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};



class Mesh {
public:
    // ��������
    vector<Vertex>       vertices;  // ����
    vector<unsigned int> indices;   // ����
    unsigned int VAO;

    // ���캯��
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices);

    // ��Ⱦ����
    void Draw();

private:
    // ������Ⱦ������
    unsigned int VBO, EBO;

    // ��ʼ�����л�������
    void setupMesh();
};

typedef vector<Mesh> Model;

#endif