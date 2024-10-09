#include "UpdateVelocityPataPata.hh"

void ECS::Systems::UpdateVelocityPataPata::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
    std::vector<std::size_t> pataPatas, float timeElapsed) {
        for (auto entity : entities) {
                if (!velocities[entity].has_value()) {
                    continue;
                }

                ECS::Components::Velocity& velocity = velocities[entity].value();

                float amplitude = 0.05f;
                float frequency = 2.0f;

                velocity.setX(amplitude * std::sin(frequency * timeElapsed));
        }
}
