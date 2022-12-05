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
		update( ParticleSlotmap& p_particles ) const noexcept override;

	};
}