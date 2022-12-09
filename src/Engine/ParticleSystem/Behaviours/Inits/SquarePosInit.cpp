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
		float randX { 0.f }, randY { 0.f }; 
		if( _xDiff > 0 )
        	randX = rand()%_xDiff - _minx;
        
		if( _yDiff > 0 )
			randY = rand()%_yDiff - _miny;

		auto& particlePos = p_particles.getItem<Position>(p_particleKey);

		particlePos.x = randX;
		particlePos.y = randY;
	}

}