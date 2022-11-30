#include "SquarePosInit.hpp"

namespace ParticleSystem
{
	SquarePosInit::SquarePosInit(int p_minx, int p_maxx, int p_miny, int p_maxy ) noexcept
	: _minx { p_minx }, _maxx { p_maxx }, _miny { p_miny }, _maxy { p_maxy }
	{
        _xDiff = p_maxx - p_minx;
        _yDiff = p_maxy - p_miny;
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	SquarePosInit::init(Particle& p_particle) const noexcept
	{
        int randX = rand()%_xDiff - _minx;
        int randY = rand()%_yDiff - _miny;

		p_particle._pos.x = randX;
		p_particle._pos.y = randY;
	}

}