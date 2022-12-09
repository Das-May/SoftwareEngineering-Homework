#include "game.h"

#include "resource_manager.h"
#include "Renderer.h"
#include "Camera_FPS.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Game-related State data
Renderer *test;


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete test;
}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/model_loading.vs", "shaders/model_loading.fs", nullptr, "��ɫ������");
    Shader s = ResourceManager::GetShader("��ɫ������");
    ResourceManager::LoadTexture("textures/top.jpg", false, "�������");
    Texture2D t = ResourceManager::GetTexture("�������");
    s.Use().SetInteger("texture1", 0);
    ResourceManager::LoadModel("models/FPS_cube.obj", "ģ�Ͳ���");
    Model m = ResourceManager::GetModel("ģ�Ͳ���");
    test = new Renderer(m, s, t);
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
    test->Draw();
}