#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Character.h"
#include "Renderer.h"

enum tagType {
    PLAYER, ENEMY, BAG, UNDEFINED
};
// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // 对象状态
    glm::vec2   position;
    float scale;
    Character character;
    GLboolean   destroyed;
    tagType tag;
    // 构造函数
    GameObject();
    GameObject(tagType tag, glm::vec2 pos, float scale, int hp, int atk);
    // 功能函数
    void BeAttack(Character& character);//被攻击
    virtual void Draw(Renderer& renderer);// 绘制
};

#endif