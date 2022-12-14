#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "mesh.h"


// ����һ����װ��Ⱦ����Ĺ�����
class Renderer
{
public:
    // ���캯�� (��ʼ��ģ�͡���ɫ��������)
    Renderer(Model& model, Shader &shader, Texture2D &texture);
    // ��������
    ~Renderer();
    // ����
    void setPbrShaderParameters(glm::vec3 albedo, float metallic, float roughness, float ao);
    void Draw(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
private:
    Model model;
    Shader shader;
    Texture2D texture;
    void initRenderData();

};

#endif

