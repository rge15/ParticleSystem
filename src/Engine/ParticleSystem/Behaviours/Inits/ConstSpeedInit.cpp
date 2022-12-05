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
	ConstSpeedInit::init(ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept
	{
		auto& particleSpeed = p_particles.getItem<Speed>(p_particleKey);
		particleSpeed._x = _vx;
		particleSpeed._y = _vy;
	}

}