#pragma once
#include <utilities/alias.hpp>
#include <Engine/ParticleSystem/Particle.hpp>

namespace ParticleSystem
{

	class BaseInit
	{
	public:
		explicit BaseInit() = default;
		virtual ~BaseInit() = default;
	
		void
		virtual init(Particle& p_particle) const noexcept = 0;
	};
}