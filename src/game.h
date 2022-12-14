#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// 表示游戏的当前状态
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game类内含所有与游戏相关的函数
// 将所有与游戏相关的数据合并到一个类中
// 易于访问每个组件，具有可管理性
class Game
{
public:
    // game state
    GameState               State;
    bool                    Keys[1024], shooting;
    float                   lastX, lastY, xpos, ypos;
    unsigned int            Width, Height;
    // 构造函数/析构函数
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