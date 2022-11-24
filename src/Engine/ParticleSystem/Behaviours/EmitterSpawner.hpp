#pragma once
#include <utilities/alias.hpp>
#include <Engine/utils/metaProggraming.hpp> 
#include <Engine/utils/concepts.hpp>
#include <Engine/ParticleSystem/Particle.hpp>
#include <Engine/ParticleSystem/Behaviours/Spawn/spawnerIncludes.hpp>

namespace ParticleSystem
{

	class EmitterSpawner
	{
	public:
		Vector<uniqPtr<BaseSpawner>> _spawners {};	
	
	public:
		EmitterSpawner() = default;
		~EmitterSpawner() = default;

		//Base Template Overloading with Tag Dispatching Definition
		template<spawnBehaviour T, typename... args>
		T&
		addSpawn( args&&... p_params ) noexcept;

	private:
		//Template Overloadings
		inline RatioSpawner&
		addSpawn( MP::Class<RatioSpawner> , int p_spawnParticles = 5, float p_spawnRateSeconds = 1.f );

	};

}

#include "EmitterSpawner.tpp"