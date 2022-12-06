#include "SquarePosInit.hpp"

namespace ParticleSystem
{
	SquarePosInit::SquarePosInit(float p_minx, float p_maxx, float p_miny, float p_maxy ) noexcept
	: _minx { p_minx }, _maxx { p_maxx }, _miny { p_miny }, _maxy { p_maxy }
	{
        _xDiff = p_maxx - p_minx;
        _yDiff = p_maxy - p_miny;
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	SquarePosInit::init(ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept
	{
        float randX = rand()%_xDiff - _minx;
        float randY = rand()%_yDiff - _miny;

		auto& particlePos = p_particles.getItem<Position>(p_particleKey);

		particlePos.x = randX;
		particlePos.y = randY;
	}

}