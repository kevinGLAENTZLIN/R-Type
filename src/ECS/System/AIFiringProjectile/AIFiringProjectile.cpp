#include "AIFiringProjectile.hh"

std::vector<std::size_t> ECS::Systems::AIFiringProjectile::aiFiringProjectile(
    ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    std::vector<std::size_t> & entities)
{
    std::vector<std::size_t> firingEntities;

    for (std::size_t i = 0; i < entities.size(); i++) {
        if (AIs[entities[i]]->isFiring() && AIs[entities[i]]->getCooldown() == 0) {
            AIs[entities[i]]->setFiring(false);
            continue;
        } else if (AIs[entities[i]]->isFiring()) {
            AIs[entities[i]]->setCooldown(AIs[entities[i]]->getCooldown() - 1);
            continue;
        }
        if (AIs[entities[i]]->getEnemyType() == PATAPATA && positions[entities[i]]->getX() < 2.0) {
            AIs[entities[i]]->setFiring(true);
            AIs[entities[i]]->setCooldown(50);
            firingEntities.push_back(entities[i]);
        }
    }
    return firingEntities;
}
