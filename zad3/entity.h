#pragma once

class Entity
{
public:
    Entity(int id = -1);

    int Id();
    void SetId(int val);

private:
    int id;
};