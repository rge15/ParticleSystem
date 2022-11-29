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
	ConstLifeInit::init(Particle& p_particle) const noexcept
	{
		p_particle._totalLifeTime = _initLifeTime;
	}

}
