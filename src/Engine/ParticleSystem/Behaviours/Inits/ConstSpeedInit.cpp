#include "ConstSpeedInit.hpp"

namespace ParticleSystem
{
	ConstSpeedInit::ConstSpeedInit(float p_x, float p_y, float p_z ) noexcept
	: _vx { p_x }, _vy { p_y }, _vz { p_z }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstSpeedInit::init(Particle& p_particle) const noexcept
	{
		p_particle._velX = _vx;
		p_particle._velY = _vy;
		p_particle._velZ = _vz;
	}

}