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

		int totalParticles = vecPosition.size();
		//int totalFloatValues = totalParticles << 1; //? Each pos are 2 floats so size * 2
		int totalSSEPacks = totalParticles >> 1;
		int restCalculus = totalParticles & 0x01;


		for(int i = 0; i < totalSSEPacks; i++)
		{
			const int vecPos = i << 1;
			float * const particlePosPointer = &vecPosition[vecPos].x;
			const __m128 particlePos = _mm_load_ps( particlePosPointer );
			const __m128 particleVel = _mm_load_ps( &vecSpeed[vecPos]._x );
			const __m128 newParticlePos = _mm_add_ps( particlePos, particleVel );
			_mm_store_ps( particlePosPointer, newParticlePos );
		}

		int countCalculatedPos = totalSSEPacks << 1;

		for(int i = countCalculatedPos; i < totalParticles; i++ )
		{
			vecPosition.data()[i].x += vecSpeed.data()[i]._x;
			vecPosition.data()[i].y += vecSpeed.data()[i]._y;	
		}

	}

}