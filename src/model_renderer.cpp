#include "model_renderer.h"

ModelRenderer::ModelRenderer(string const& modelPath, Shader shader)
{
	this->model = Model(modelPath);
	this->shader = shader;
	this->initRenderData();
}

ModelRenderer::~ModelRenderer()
{

}

void ModelRenderer::initRenderData()
{

}
