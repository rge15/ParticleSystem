#include "ConstPosInit.hpp"

namespace ParticleSystem
{
	ConstPosInit::ConstPosInit(float p_x, float p_y ) noexcept
	: _x { p_x }, _y { p_y }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstPosInit::init(ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept
	{
		auto& particlePos = p_particles.getItem<Position>(p_particleKey);
		particlePos.x = _x;
		particlePos.y = _y;
	}

}