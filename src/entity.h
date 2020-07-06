
#pragma once

class Entity
{

public:
    Entity(int x, int y);
    Entity();
    int x{0};
    int y{0};
    int dx{0};
    int dy{0};
    int health{0};

private:
};

class Player: public Entity 
{
public:
    using Entity::Entity;
    int up{0};
    int down{0};
    int left{0};
    int right{0};
};