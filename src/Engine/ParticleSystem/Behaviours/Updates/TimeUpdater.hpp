#pragma once
#include "BaseUpdater.hpp"

namespace ParticleSystem
{
	class TimeUpdater : public BaseUpdater
	{

	public:
		TimeUpdater() = default;
		~TimeUpdater() = default;

		void
		update( ParticleSlotmap& p_particles ) const noexcept override;

	};
}