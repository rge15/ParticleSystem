#include "EmitterUpdater.hpp"

namespace ParticleSystem
{

	void
	EmitterUpdater::updateParticles( Vector<Particle>& p_particles ) const noexcept
	{
		for(auto& updater : _updates)
			for(auto& particle : p_particles)
				updater.get()->update( particle );
	}


}