#include "EmitterUpdater.hpp"

namespace ParticleSystem
{

	void
	EmitterUpdater::updateParticles( ParticleSlotmap& p_particles ) const noexcept
	{
		
		for(auto& updater : _updates)
			updater.get()->update( p_particles );
	}


}