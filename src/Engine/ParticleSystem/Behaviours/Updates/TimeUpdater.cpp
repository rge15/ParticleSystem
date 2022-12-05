#include "TimeUpdater.hpp"

namespace ParticleSystem
{
	void
	TimeUpdater::update( ParticleSlotmap& p_particles ) const noexcept
	{
		auto& lifeVec = p_particles.getDataVector<Life>();

		for(auto& life : lifeVec)
		{
			float lifeTime = std::chrono::duration_cast<std::chrono::milliseconds>(demoClock::now() - life._initLife).count()/1000.;

			life._currLifeTime = lifeTime;
			life._currNormalizedLifeTime = lifeTime / life._totalLifeTime;
		}

	}

}