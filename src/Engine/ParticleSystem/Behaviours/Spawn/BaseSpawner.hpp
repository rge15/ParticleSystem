#pragma once
#include <utilities/alias.hpp>
#include <Engine/ParticleSystem/Particle.hpp>
#include <Engine/ParticleSystem/Behaviours/Inits/BaseInit.hpp>

namespace ParticleSystem
{
	class BaseSpawner
	{
	public:
		explicit BaseSpawner() = default;

		virtual ~BaseSpawner() = default;

		void
		virtual spawn( Vector<Particle>& p_particles, Vector<uniqPtr<BaseInit>>& p_initBehaviour ) = 0;
	};
}