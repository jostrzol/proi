#pragma once

#include <functional>

class Entity
{
public:
    struct PtrHash
    {
        std::size_t operator()(const Entity *product) const;
    };
    struct PtrEqualTo
    {
        bool operator()(const Entity *first, const Entity *second) const;
    };

    Entity(int id = -1);
    virtual ~Entity();

    bool operator==(const Entity &other) const;
    bool operator!=(const Entity &other) const;
    friend std::hash<Entity>;

    int GetID() const;
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