// /*
// ** EPITECH PROJECT, 2024
// ** hitbox.hh
// ** File description:
// ** System hitbox class
// */

// #pragma once

// #include <vector>
// #include "../System/System.hpp"
// #include "../../Component/ComponentManager/SparseArray.hpp"
// #include "../../Component/Position/Position.hpp"
// #include "../../Component/Hitbox/Hitbox.hh"

// namespace Systems {

//     class Hitbox : public System {

//         public:
//             Hitbox() = default;
//             ~Hitbox() = default;
//             bool isHit(ComponentManager::SparseArray<Components::Position> &positions,
//                 ComponentManager::SparseArray<Components::Hitbox> &hitboxes,
//                std::vector<std::size_t> &entities);


//         protected:

//         private:

//     };
// };


/*
** EPITECH PROJECT, 2024
** R-Type - System : Hitbox
** File description:
** System hitbox class
*/

#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Hitbox/Hitbox.hh"

namespace ECS {

    namespace Systems {

        class Hitbox : public System {
            public:
                Hitbox() = default;
                ~Hitbox() = default;

                void isHit(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                   ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
                   std::vector<std::size_t> &entities);

                bool checkCollision(const ECS::Components::Position &posA, const ECS::Components::Hitbox &hitboxA,
                            const ECS::Components::Position &posB, const ECS::Components::Hitbox &hitboxB);
        };
    }
}
