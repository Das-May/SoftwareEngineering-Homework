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
	//������ɫ��
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);//����ģ�;���M
	shader.SetMatrix4("model", model);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
	shader.SetMatrix4("view", model);
	glm::mat4 projection = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);
	// ��Ҳ��֪��Ϊʲô����ͶӰ���޷���ʾ
	//glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f, -1.0f, 1.0f);
	shader.SetMatrix4("projection", projection);

	// ������
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	// ����
	for (unsigned int i = 0; i < this->model.size(); i++)
		this->model[i].Draw();
}

void Renderer::initRenderData()
{

}
