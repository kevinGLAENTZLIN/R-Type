#include "Light.hh"
#include "raylib.h"  // Assurez-vous d'inclure l'en-tête raylib approprié

ECS::Components::Light::Light(int type, Vector3 position, Vector3 target, Color color, const std::string& shader)
    : _type(static_cast<LightType>(type)),
      _position(position),
      _target(target),
      _color(color),
      _shader(shader),
      _enabled(true),
      _attenuation(0.0f),
      _enabledLoc(0),
      _typeLoc(0),
      _positionLoc(0),
      _targetLoc(0),
      _colorLoc(0),
      _attenuationLoc(0)
{
}

void ECS::Components::Light::update()
{
}

void ECS::Components::Light::enable()
{
    _enabled = true;
}

void ECS::Components::Light::disable()
{
    _enabled = false;
}
