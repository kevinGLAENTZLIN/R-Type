#pragma once

#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Health/Health.hh"

namespace ECS {
    namespace Systems {

        class GetDeadEntities : public System{
        public:
            
            std::vector<std::size_t> getDeadEntities(
                ECS::ComponentManager::SparseArray<ECS::Components::Health>,
                const std::vector<std::size_t> & entities);
        };
    }
}
