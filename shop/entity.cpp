#include "entity.h"

Entity::Entity(int id) : id(id)
{
    return;
}

Entity::~Entity() {}
int Entity::GetID() const { return id; }
void Entity::SetID(int val) { id = val; }

std::size_t std::hash<Entity>::operator()(const Entity &entity) const
{
    return hash<int>()(entity.GetID());
}

bool Entity::operator==(const Entity &other) const
{
    return id == other.id;
}

bool Entity::operator!=(const Entity &other) const
{
    return id != other.id;
}

std::size_t Entity::PtrHash::operator()(const Entity *product) const
{
    return std::hash<Entity>()(*product);
}
bool Entity::PtrEqualTo::operator()(const Entity *first, const Entity *second) const
{
    return *first == *second;
}