#include "game.h"

#include "resource_manager.h"
#include "Renderer.h"
#include "Camera_FPS.h"
#include "game_object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

// �û�����
Parameter parameter;

// Game-related State data
Renderer* test;
Renderer* scene;
Renderer* obstacle;
Renderer* bag;
Renderer* enemy;

GameObject* player;
vector<GameObject*> enemies;
vector<GameObject*> bags;
vector<GameObject*> obstacles;

// �����
Camera camera(glm::vec3(0.0f, 1.5f, 0.0f)); 
bool firstMouse = true;


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), shooting(false), Width(width), Height(height)
{
    lastX = Game::Width / 2.0f;
    lastY = Game::Height / 2.0f;
}

Game::~Game()
{
    Clear();
}

void Game::Clear()
{
    delete test;
    delete scene;
    delete obstacle;
    delete bag;
    delete enemy;

    enemies.clear();
    bags.clear();
    obstacles.clear();

    //ResourceManager::Clear();
}

void Game::Init()
{
    // ���
    Clear();

    // �����û�����
    parameter = ResourceManager::LoadParameter();
    camera.Position = glm::vec3(parameter.player_parameter.x, 1.5f, parameter.player_parameter.z);
    player = new GameObject(PLAYER, 
        glm::vec2(parameter.player_parameter.x, parameter.player_parameter.z), 1.0f,
        parameter.player_parameter.hp, parameter.player_parameter.atk);

    // ������ɫ��
    ResourceManager::LoadShader("shaders/pbr.vs", "shaders/pbr.fs", nullptr, "��������");
    ResourceManager::LoadShader("shaders/pbr.vs", "shaders/pbr.fs", nullptr, "�ϰ������");
    ResourceManager::LoadShader("shaders/pbr.vs", "shaders/pbr.fs", nullptr, "Ѫ������");
    ResourceManager::LoadShader("shaders/pbr.vs", "shaders/pbr.fs", nullptr, "���˲���");

    // ������ɫ��
    for (auto& s : ResourceManager::Shaders) {
        s.second.Use();
        s.second.SetInteger("texture1", 0);
        s.second.SetVector3f("lightDirection", glm::vec3(-10.0f, 50.0f, 10.0f));
        s.second.SetVector3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    }

    // ��������
    ResourceManager::LoadTexture("textures/CheckerboardLattice.jpg", false, "���̸�");
    ResourceManager::LoadTexture("textures/box/box_basecolor.jpg", false, "Ѫ��_������ͼ");
    ResourceManager::LoadTexture("textures/cannon/Sentry_Turret_ALL_02_-_Default_BaseColor.jpg", false, "��̨_������ͼ");

    // ����ģ��
    ResourceManager::LoadModel("models/scene.obj", "����");
    ResourceManager::LoadModel("models/barrier.obj", "�ϰ���");
    ResourceManager::LoadModel("models/bag.obj", "Ѫ��");
    ResourceManager::LoadModel("models/enemy.obj", "��̨");

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
    Hit();
    // �����������
    if (this->Keys[GLFW_KEY_W] == GLFW_PRESS && !frontHit)
        camera.ProcessKeyboard(FORWARD, dt);
    if (this->Keys[GLFW_KEY_S] == GLFW_PRESS && !backHit)
        camera.ProcessKeyboard(BACKWARD, dt);
    if (this->Keys[GLFW_KEY_A] == GLFW_PRESS && !leftHit)
        camera.ProcessKeyboard(LEFT, dt);
    if (this->Keys[GLFW_KEY_D] == GLFW_PRESS && !rightHit)
        camera.ProcessKeyboard(RIGHT, dt);
    if (this->Keys[GLFW_KEY_0] == GLFW_PRESS)
        this->Init();

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

    if (shooting == true)
    {
        Shoot();
        shooting = false;
    }
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

void Game::Shoot()
{
    //����������һ�� p = p0+t*d
    glm::vec3 p0 = camera.Position;
    glm::vec3 d = camera.Front;
    // �����߻��е���ʱ��p1.y = 0
    // �Դ˿ɵ�һԪ���� p0.y + t*d.y = 0, ��t0 = ((p1.y) -p0.y)/ d.y, ���t0
    float t0 = -p0.y / d.y;
    // ������ϱ����еĵ������p1 = p0+t0*d
    glm::vec3 p1 = p0 + t0 * d;
    cout << "����λ��:" << p1.x << "  " << p1.y << "  " << p1.z << endl;

    // ���������еĶ����λ�ã�����˭��������е�С��1
    for (auto& b : bags)
    {
        if (abs(p1.x - b->position.x) < 1 && abs(p1.z - b->position.y) < 1)
        {
            cout << "* ʰȡ��Ʒ" << endl;
            b->BeAttack(player->character);
        }
            
    }
    for (auto& e : enemies)
    {
        if (abs(p1.x - e->position.x) < 1 && abs(p1.z - e->position.y) < 1)
        {
            cout << "* ���е���" << endl;
            e->BeAttack(player->character);
            //break;
        }
    }
}

void Game::Hit()
{
    frontHit = backHit = leftHit = rightHit = false;
    glm::vec3 p = camera.Position;
    // ���������е��ϰ�����ϰ���ļ���������������ľ���С��10��������ײ
    for (auto& o : obstacles)
    {

        float Dx = abs(o->position.x - p.x);
        float Dz = abs(o->position.y - p.z);
        if (Dx <= 2 && Dz <= 2)
        {
            glm::vec3 DirectionVec = glm::vec3(o->position.x, 0.0, o->position.y) - p;
            float a = glm::dot(camera.Front, DirectionVec);
            float b = glm::dot(camera.Right, DirectionVec);
            if (a > 0.5)
                frontHit = true;
            else if(a < -0.5)
                backHit = true;
            if (b < 0.5)
                leftHit = true;
            else if (b > 0.5)
                rightHit = true;

        }

    }
}
