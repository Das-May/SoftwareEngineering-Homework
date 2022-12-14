#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ��ʾ��Ϸ�ĵ�ǰ״̬
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game���ں���������Ϸ��صĺ���
// ����������Ϸ��ص����ݺϲ���һ������
// ���ڷ���ÿ����������пɹ�����
class Game
{
public:
    // game state
    GameState               State;
    bool                    Keys[1024], shooting;
    float                   lastX, lastY, xpos, ypos;
    unsigned int            Width, Height;
    // ���캯��/��������
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/models)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
private:
    void Clear();
    void Shoot();
};

#endif