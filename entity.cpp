#include "entity.h"

Entity::Entity(int id) : id(id) {}

Entity::~Entity() {}
int Entity::ID() const { return id; }
void Entity::SetID(int val) { id = val; }

std::size_t std::hash<Entity>::operator()(const Entity &entity) const
{
    return hash<int>()(entity.ID());
}

bool Entity::operator==(const Entity &other) const
{
    return id == other.id;
}

bool Entity::operator!=(const Entity &other) const
{
    return id != other.id;
}
