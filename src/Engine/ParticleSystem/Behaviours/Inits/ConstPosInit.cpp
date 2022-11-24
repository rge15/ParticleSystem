#include "ConstPosInit.hpp"

namespace ParticleSystem
{
	ConstPosInit::ConstPosInit(int p_x, int p_y ) noexcept
	: _x { p_x }, _y { p_y }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstPosInit::init(Particle& p_particle) const noexcept
	{
		p_particle._pos.x = _x;
		p_particle._pos.y = _y;
	}

}