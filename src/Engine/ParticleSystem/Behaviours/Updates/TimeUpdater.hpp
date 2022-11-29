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
		update( Particle& p_particle ) const noexcept override;

	};
}