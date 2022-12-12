/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game_object.h"


GameObject::GameObject(): tag(UNDEFINED), position(0, 0), scale(1), character(10, 10), destroyed(false) {}

GameObject::GameObject(tagType tag, glm::vec2 pos, float scale, int hp, int atk)
    : tag(tag), position(pos), scale(scale), character(hp, atk), destroyed(false) { }

void GameObject::Draw(Renderer& renderer)
{
    if(!destroyed)
        renderer.Draw(glm::vec3(position.x, 0.0f, position.y), glm::vec3(scale, scale, scale));
}