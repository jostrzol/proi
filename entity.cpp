#include "entity.h"

Entity::Entity(int id = -1) : id(id) {}
int Entity::Id() { return id; }
void Entity::SetId(int val) { id = val; }
