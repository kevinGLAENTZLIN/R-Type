#include "GetDeadEntities.hh"

std::vector<std::size_t> ECS::Systems::GetDeadEntities::getDeadEntities(
    ECS::ComponentManager::SparseArray<ECS::Components::Health> healths,
    const std::vector<std::size_t> & entities)
{
    std::vector<std::size_t> deadEntities;

    for (std::size_t i = 0; i < entities.size(); i++) {
        if (healths[entities[i]]->getHealth() <= 0)
            deadEntities.push_back(entities[i]);
    }
    return deadEntities;
}
