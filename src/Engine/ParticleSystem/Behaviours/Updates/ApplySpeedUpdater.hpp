#pragma once
#include "BaseUpdater.hpp"

namespace ParticleSystem
{
	class ApplySpeedUpdater : public BaseUpdater
	{
	public:
		ApplySpeedUpdater() = default;
		~ApplySpeedUpdater() = default;

		void
		update( Particle& p_particle ) const noexcept override;

	};
}