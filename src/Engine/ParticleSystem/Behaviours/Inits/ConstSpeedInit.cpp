#include "ConstSpeedInit.hpp"

namespace ParticleSystem
{
	ConstSpeedInit::ConstSpeedInit(float p_x, float p_y ) noexcept
	: _vx { p_x }, _vy { p_y }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstSpeedInit::init(Particle& p_particle) const noexcept
	{
		p_particle._velX = _vx;
		p_particle._velY = _vy;
	}

}