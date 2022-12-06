#pragma once
#include <utilities/alias.hpp>
#include <Engine/ParticleSystem/Particle.hpp>
#include <Engine/utils/engineAlias.hpp>
#include <utilities/includeSSE.hpp>

namespace ParticleSystem
{
	class BaseUpdater
	{
		public:
			BaseUpdater() = default;
			~BaseUpdater() = default;

			void
			virtual update( ParticleSlotmap& p_particles ) const noexcept = 0;
	};

}