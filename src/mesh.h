#ifndef MESH_H
#define MESH_H

// OpenGL报错#error: gl.h included before glew.h
//#include <GL/glew.h>    // https://blog.csdn.net/m0_48776220/article/details/127716715
#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

// 顶点信息结构体【注意以此配置顶点着色器的输入】
// layout (location = 0) in vec3 aPos;
// layout(location = 1) in vec3 aNormal;
// layout(location = 2) in vec2 aTexCoords;
struct Vertex {
    // 位置
    glm::vec3 Position;
    // 法线
    glm::vec3 Normal;
    // 纹理坐标
    glm::vec2 TexCoords;
    // 切线
    glm::vec3 Tangent;
    // 副切线
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
    // 网格数据
    vector<Vertex>       vertices;  // 顶点
    vector<unsigned int> indices;   // 索引
    unsigned int VAO;

    // 构造函数
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices);

    // 渲染网格
    void Draw();

private:
    // 用于渲染的数据
    unsigned int VBO, EBO;

    // 初始化所有缓冲数组
    void setupMesh();
};

typedef vector<Mesh> Model;

#endif