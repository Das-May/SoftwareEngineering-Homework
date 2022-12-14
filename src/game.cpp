#include "game.h"

#include "resource_manager.h"
#include "Renderer.h"
#include "Camera_FPS.h"
#include "game_object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// �û�����
Parameter parameter;

// Game-related State data
Renderer* test;
Renderer* scene;
Renderer* obstacle;
Renderer* bag;
Renderer* enemy;

vector<GameObject*> enemies;
vector<GameObject*> bags;
vector<GameObject*> obstacles;

// �����
Camera camera(glm::vec3(0.0f, 1.5f, 3.0f)); 
bool firstMouse = true;


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
    lastX = Game::Width / 2.0f;
    lastY = Game::Height / 2.0f;
}

Game::~Game()
{
    delete test;
}

void Game::Init()
{
    // �����û�����
    parameter = ResourceManager::LoadParameter();

    // ������ɫ��
    ResourceManager::LoadShader("shaders/pbr.vs", "shaders/pbr.fs", nullptr, "��������");
    ResourceManager::LoadShader("shaders/pbr.vs", "shaders/pbr.fs", nullptr, "�ϰ������");
    ResourceManager::LoadShader("shaders/pbr.vs", "shaders/pbr.fs", nullptr, "Ѫ������");
    ResourceManager::LoadShader("shaders/pbr.vs", "shaders/pbr.fs", nullptr, "���˲���");

    // ������ɫ��
    for (auto& s : ResourceManager::Shaders) {
        s.second.Use();
        s.second.SetInteger("texture1", 0);
        s.second.SetVector3f("lightDirection", glm::vec3(-10.0f, 50.0f, 0.0f));
        s.second.SetVector3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    }

    // ��������
    ResourceManager::LoadTexture("textures/CheckerboardLattice.jpg", false, "���̸�");
    ResourceManager::LoadTexture("textures/box/XZ_XiangGai_BaseColor.png", false, "Ѫ��_������ͼ");
    ResourceManager::LoadTexture("textures/cannon/Sentry_Turret_ALL_02_-_Default_BaseColor.png", false, "��̨_������ͼ");

    // ����ģ��
    ResourceManager::LoadModel("models/FPS_box.obj", "����");
    ResourceManager::LoadModel("models/cube.obj", "�ϰ���");
    ResourceManager::LoadModel("models/box.obj", "Ѫ��");
    ResourceManager::LoadModel("models/cannon.obj", "��̨");

    // ������Ⱦ����
    bag = new Renderer(ResourceManager::GetModel("Ѫ��"),
        ResourceManager::GetShader("Ѫ������"),
        ResourceManager::GetTexture("Ѫ��_������ͼ"));
    bag->setPbrShaderParameters(glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 1.0f, 0.1f);
    scene = new Renderer(ResourceManager::GetModel("����"),
        ResourceManager::GetShader("��������"),
        ResourceManager::GetTexture("���̸�"));
    scene->setPbrShaderParameters(glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.5f, 0.1f);
    obstacle = new Renderer(ResourceManager::GetModel("�ϰ���"),
        ResourceManager::GetShader("�ϰ������"),
        ResourceManager::GetTexture("���̸�"));
    obstacle->setPbrShaderParameters(glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 1.0f, 0.1f);
    enemy = new Renderer(ResourceManager::GetModel("��̨"),
        ResourceManager::GetShader("���˲���"),
        ResourceManager::GetTexture("��̨_������ͼ"));
    enemy->setPbrShaderParameters(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0.1f);

    // ������Ϸ����
    SceneParameter temp_sp = parameter.scene_parameter;
    for (int i = 0; i < temp_sp.obstacles_postion_x.size(); i++)
    {
        obstacles.push_back(new GameObject(BAG, glm::vec2(temp_sp.obstacles_postion_x[i], temp_sp.obstacles_postion_z[i]), 1, 0, 0));
    }
    for (int i = 0; i < parameter.bag_parameter.size(); i++)
    {
        CharacterParameter bag = parameter.bag_parameter[i];
        bags.push_back(new GameObject(BAG, glm::vec2(bag.x, bag.z), 0.01, bag.hp, bag.atk));
    }
    for (int i = 0; i < parameter.enemy_parameter.size(); i++)
    {
        CharacterParameter enemy = parameter.enemy_parameter[i];
        enemies.push_back(new GameObject(ENEMY, glm::vec2(enemy.x, enemy.z), 1, enemy.hp, enemy.atk));
    }

}

void Game::Update(float dt)
{
    for (auto& s : ResourceManager::Shaders) {
        s.second.Use().SetMatrix4("view", camera.GetViewMatrix());
        glm::mat4 projection = glm::perspective(45.0f, (float)Width / (float)Height, 0.1f, 100.0f);
        s.second.SetMatrix4("projection", projection);
        s.second.SetVector3f("camPos", camera.Position);
    }
}

void Game::ProcessInput(float dt)
{
    // �����������
    if (this->Keys[GLFW_KEY_W] == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, dt);
    if (this->Keys[GLFW_KEY_S] == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, dt);
    if (this->Keys[GLFW_KEY_A] == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, dt);
    if (this->Keys[GLFW_KEY_D] == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, dt);

    // �����������
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void Game::Render()
{
    scene->Draw(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(parameter.scene_parameter.width,  1.0f, parameter.scene_parameter.length));
    for (auto& o : obstacles)
        o->Draw(*obstacle);
    for (auto& b : bags)
        b->Draw(*bag);
    for (auto& e : enemies)
        e->Draw(*enemy);
}