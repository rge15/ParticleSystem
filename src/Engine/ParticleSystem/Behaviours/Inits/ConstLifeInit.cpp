#include "ConstLifeInit.hpp"

namespace ParticleSystem
{

	ConstLifeInit::ConstLifeInit(float p_initLifeTime)
	: _initLifeTime { p_initLifeTime }
	{
	}
	
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstLifeInit::init(ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept
	{
		auto& particleLife = p_particles.getItem<Life>(p_particleKey);
		particleLife._totalLifeTime = _initLifeTime;
	}

}
