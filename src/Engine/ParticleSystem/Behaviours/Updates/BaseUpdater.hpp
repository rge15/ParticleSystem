#pragma once
#include <utilities/alias.hpp>
#include <Engine/ParticleSystem/Particle.hpp>

namespace ParticleSystem
{
	class BaseUpdater
	{
		public:
			BaseUpdater() = default;
			~BaseUpdater() = default;

			void
			virtual update( Particle& p_particle ) const noexcept = 0;
	};

}