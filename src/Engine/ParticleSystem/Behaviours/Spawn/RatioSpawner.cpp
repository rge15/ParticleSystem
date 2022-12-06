#include "RatioSpawner.hpp"


namespace ParticleSystem
{


	RatioSpawner::RatioSpawner( int p_spawnParticles, float p_spawnRateSeconds ) noexcept
	: _spawnParticlesNum { p_spawnParticles }
	, _secondsSpawnRate { p_spawnRateSeconds }
	{
		_ratioSpawnerTimer.setManualRefreshRate( _secondsSpawnRate );
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RatioSpawner::spawn( ParticleSlotmap& p_particles, Vector<uniqPtr<BaseInit>>& p_initBehaviour ) noexcept
	{
		if(_ratioSpawnerTimer.update())
		{
			for(int i = 0 ; i < _spawnParticlesNum; i++)
			{
				auto particleKey = p_particles.addSlot();

				for(auto& initer : p_initBehaviour)
					initer.get()->init( p_particles, particleKey );
			}
		}
	}

}