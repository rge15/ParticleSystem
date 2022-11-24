#include "ApplySpeedUpdater.hpp"

namespace ParticleSystem
{
	void
	ApplySpeedUpdater::update( Particle& p_particle ) const noexcept
	{
		p_particle._pos.x += p_particle._velX;
		p_particle._pos.y += p_particle._velY;
	}

}