#include "ConstPosInit.hpp"

namespace ParticleSystem
{
	ConstPosInit::ConstPosInit(float p_x, float p_y, float p_z ) noexcept
	: _x { p_x }, _y { p_y }, _z { p_z }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstPosInit::init(Particle& p_particle) const noexcept
	{
		p_particle._posX = _x;
		p_particle._posY = _y;
		p_particle._posZ = _z;
	}

}