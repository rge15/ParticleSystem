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
	RatioSpawner::spawn( Vector<Particle>& p_particles, Vector<uniqPtr<BaseInit>>& p_initBehaviour ) noexcept
	{
		if(_ratioSpawnerTimer.update())
		{
			//TODO : Q reciba los initers y las partículas
			//TODO : Añade partícula y la inicia
		}
	}

}