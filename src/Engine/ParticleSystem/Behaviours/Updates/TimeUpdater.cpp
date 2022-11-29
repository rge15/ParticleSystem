#include "TimeUpdater.hpp"

namespace ParticleSystem
{
	void
	TimeUpdater::update( Particle& p_particle ) const noexcept
	{
		float lifeTime = std::chrono::duration_cast<std::chrono::milliseconds>(demoClock::now() - p_particle._initLife).count()/1000.;

		p_particle._lifeTime = lifeTime;
		p_particle._normalizedLifeTime = lifeTime / p_particle._totalLifeTime;
	}

}