#include "ApplySpeedUpdater.hpp"

namespace ParticleSystem
{
	// void
	// ApplySpeedUpdater::update( ParticleSlotmap& p_particles ) const noexcept
	// {
	// 	auto& vecPosition = p_particles.getDataVector<Position>();
	// 	auto& vecSpeed = p_particles.getDataVector<Speed>();

	// 	for(int i = 0; i < vecPosition.size(); i++ )
	// 	{
	// 		vecPosition.data()[i].x += vecSpeed.data()[i]._x;
	// 		vecPosition.data()[i].y += vecSpeed.data()[i]._y;
	// 	}
	// }

	void
	ApplySpeedUpdater::update( ParticleSlotmap& p_particles ) const noexcept
	{
		auto& vecPosition = p_particles.getDataVector<Position>();
		auto& vecSpeed = p_particles.getDataVector<Speed>();

		for(__m128* iPos = reinterpret_cast<__m128*>(&vecPosition.data()[0].x), 
			*endPos = reinterpret_cast<__m128*>(&vecPosition.back().x),
			*iSpeed = reinterpret_cast<__m128*>(&vecSpeed.data()[0]._x);
			iPos < endPos ; iPos++ , iSpeed++ )
		{
			*iPos = _mm_add_ps( *iPos, *iSpeed );
		}

		//for(int i = 0; i < vecPosition.size(); i++ )
		//{
		//	vecPosition.data()[i].x += vecSpeed.data()[i]._x;
		//	vecPosition.data()[i].y += vecSpeed.data()[i]._y;
		//}
	}

}