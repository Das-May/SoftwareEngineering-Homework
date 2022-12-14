#include "Renderer.h"

Renderer::Renderer(Model& model, Shader& shader, Texture2D& texture)
{
	this->model = model;
	this->shader = shader;
	this->texture = texture;
	this->initRenderData();
}

Renderer::~Renderer()
{
	
}

void Renderer::setPbrShaderParameters(glm::vec3 albedo, float metallic, float roughness, float ao)
{
	shader.Use();
	shader.SetVector3f("albedo", albedo);
	shader.SetFloat("metallic", metallic);
	shader.SetFloat("roughness", roughness);
	shader.SetFloat("ao", ao);
}

void Renderer::Draw(glm::vec3 position, glm::vec3 scale)
{
	//������ɫ��
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);//����ģ�;���M
	model = glm::scale(model, scale);
	model = glm::translate(model, position);
	shader.SetMatrix4("model", model);

	// ������
	glActiveTexture(GL_TEXTURE0);
	//glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
	texture.Bind();

	// ����
	for (unsigned int i = 0; i < this->model.size(); i++)
		this->model[i].Draw();

}

void Renderer::initRenderData()
{

}
