#include "Renderer.h"

Renderer::Renderer(Model& model, Shader& shader, Texture2D& texture)
{
	this->model = model;
	this->shader = shader;
	this->texture = texture;
	this->initRenderData();
}

void Renderer::Draw(glm::vec3 position, glm::vec3 scale)
{
	//激活着色器
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);//配置模型矩阵M
	shader.SetMatrix4("model", model);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
	shader.SetMatrix4("view", model);
	glm::mat4 projection = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);
	// 我也不知道为什么正交投影会无法显示
	//glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f, -1.0f, 1.0f);
	shader.SetMatrix4("projection", projection);

	// 绑定纹理
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	// 绘制
	for (unsigned int i = 0; i < this->model.size(); i++)
		this->model[i].Draw();
}

void Renderer::initRenderData()
{

}
