#pragma once
#include <utilities/alias.hpp>
#include <Engine/ParticleSystem/Particle.hpp>
#include <Engine/utils/engineAlias.hpp>

namespace ParticleSystem
{

	class BaseInit
	{
	public:
		explicit BaseInit() = default;
		virtual ~BaseInit() = default;
	
		void
		virtual init( ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept = 0;
	};
}