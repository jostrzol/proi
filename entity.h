#pragma once

#include <functional>

class Entity
{
public:
    Entity(int id = -1);
    virtual ~Entity();

    bool operator==(const Entity &other) const;
    bool operator!=(const Entity &other) const;
    friend std::hash<Entity>;

    int ID() const;
    void SetID(int val);

private:
    int id;
};

namespace std
{
    template <>
    struct hash<Entity>
    {
        std::size_t operator()(const Entity &entity) const;
    };
}