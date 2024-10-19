/*
** EPITECH PROJECT, 2024
** R-Type - Components : Light
** File description:
** Light Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {
        typedef enum {
            LIGHT_DIRECTIONAL = 0,
            LIGHT_POINT
        } LightType;

        class Light {

        public:
            Light(int type = LIGHT_POINT, raylib::Vector3 position, raylib::Vector3 target = raylib::Vector3(0.0f,0.0f,0.0f), raylib::Color color, const);
            initLight(int idLight, raylib::Shader &shader);
            update();
            void enable();
            void disable();
            ~Light() = default;
        private:
            LightType _type;
            raylib::Vector3 _position;
            raylib::Vector3 _target;
            raylib::Color _color;
            const std::string _shader;
            bool _enabled;
            float _attenuation;
            int _enabledLoc;
            int _typeLoc;
            int _positionLoc;
            int _targetLoc;
            int _colorLoc;
            int _attenuationLoc;
        };
    }
}
