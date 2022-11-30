#pragma once
#include "BaseInit.hpp"

namespace ParticleSystem
{

	class SquarePosInit : public BaseInit
	{
	private:
		int _minx { 0 }, _maxx { 0 }, _miny { 0 } , _maxy { 0 };
        int _xDiff, _yDiff;
	public:
		SquarePosInit( int p_minx = 0 , int p_maxx = 200 , int p_miny = 0, int p_maxy = 200 ) noexcept;
		~SquarePosInit() = default;

		void
		init(Particle& p_particle) const noexcept override;
		
	};

}