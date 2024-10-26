#include "AIFiringProjectile.hh"

std::vector<std::size_t> ECS::Systems::AIFiringProjectile::aiFiringBydoShots(
    ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    std::vector<std::size_t> & entities)
{
    std::vector<std::size_t> firingEntities;

    for (std::size_t i = 0; i < entities.size(); i++) {
        if (AIs[entities[i]]->isFiring() && AIs[entities[i]]->getCooldown() < 100)
            AIs[entities[i]]->setFiring(false);
        if (AIs[entities[i]]->getCooldown() > 0)
            AIs[entities[i]]->setCooldown(AIs[entities[i]]->getCooldown() - 1);
        if ((AIs[entities[i]]->getEnemyType() == PATAPATA || AIs[entities[i]]->getEnemyType() == BUG) &&
            positions[entities[i]]->getX() < 2.0 && AIs[entities[i]]->getCooldown() == 0) {
            AIs[entities[i]]->setFiring(true);
            AIs[entities[i]]->setCooldown(200);
            firingEntities.push_back(entities[i]);
        }
        if (AIs[entities[i]]->getEnemyType() == BINK && AIs[entities[i]]->getCooldown() == 0) {
            AIs[entities[i]]->setFiring(true);
            AIs[entities[i]]->setCooldown(150);
        }
        if (AIs[entities[i]]->getEnemyType() == BINK && AIs[entities[i]]->getCooldown() == 125)
            firingEntities.push_back(entities[i]);
    }
    return firingEntities;
}

std::vector<std::size_t> ECS::Systems::AIFiringProjectile::aiFiringMissile(
    ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    std::vector<std::size_t> & entities)
{
    
}
