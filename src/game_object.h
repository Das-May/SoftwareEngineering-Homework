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
    // ����״̬
    glm::vec2   position;
    float scale;
    Character character;
    GLboolean   destroyed;
    tagType tag;
    // ���캯��
    GameObject();
    GameObject(tagType tag, glm::vec2 pos, float scale, int hp, int atk);
    // ���ܺ���
    void BeAttack(Character& character);//������
    virtual void Draw(Renderer& renderer);// ����
};

#endif