//TODO : Hacer concept para cada tipo de ParticleBehaviour
#pragma once
#include <type_traits>
#include <Engine/ParticleSystem/Behaviours/Spawn/BaseSpawner.hpp>
#include <Engine/ParticleSystem/Behaviours/Inits/BaseInit.hpp>
// #include <Engine/ParticleSystem/Behaviours/Inits/BaseUpdate.hpp>

template<class T>
concept spawnBehaviour = std::is_base_of_v<ParticleSystem::BaseSpawner,T>;

template<class T>
concept initerBehaviour = std::is_base_of_v<ParticleSystem::BaseInit,T>;

// template<class T>
// concept updateBehaviour = std::is_base_of_v<ParticleSystem::BaseUpdate,T>;
