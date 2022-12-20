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

		float* pos = &vecPosition.data()[0].x;

		int vecPositions = vecPosition.size();
		int SSEParticles = (vecPosition.size() & ~0x03);
		int SSEPackNumber = SSEParticles >> 2;
		int lastParticles = (vecPosition.size() & 0x03);

		int i = 0;
		int ctr = 0;

		for(int i = 0 ; i < SSEPackNumber; i++, ctr+=4)
		{
			const __m128 iPos = _mm_load_ps( &vecPosition.data()[i<<2].x );
			const __m128 iSpeed = _mm_load_ps( &vecSpeed.data()[i<<2]._x );
			const __m128 newPos = _mm_add_ps( iPos, iSpeed );
			_mm_store_ps( &vecPosition.data()[i<<2].x, newPos );
		}

		for( int j = SSEParticles; j < SSEParticles + lastParticles; j++)
		{
			vecPosition.data()[j].x += vecSpeed.data()[j]._x;
			vecPosition.data()[j].y += vecSpeed.data()[j]._y;
			ctr++;
		}

	}

}