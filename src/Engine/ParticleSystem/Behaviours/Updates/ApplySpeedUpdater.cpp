#include "ApplySpeedUpdater.hpp"

namespace ParticleSystem
{
	void
	ApplySpeedUpdater::update( ParticleSlotmap& p_particles ) const noexcept
	{
		auto& vecPosition = p_particles.getDataVector<Position>();
		auto& vecSpeed = p_particles.getDataVector<Speed>();

		for(int i = 0; i < vecPosition.size(); i++ )
		{
			vecPosition.data()[i].x += vecSpeed.data()[i]._x;
			vecPosition.data()[i].y += vecSpeed.data()[i]._y;
		}
	}

}