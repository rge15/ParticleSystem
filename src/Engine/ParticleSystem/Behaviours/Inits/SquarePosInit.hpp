#pragma once
#include "BaseInit.hpp"

namespace ParticleSystem
{

	class SquarePosInit : public BaseInit
	{
	private:
		float _minx { 0 }, _maxx { 0 }, _miny { 0 } , _maxy { 0 };
        int _xDiff, _yDiff;
	public:
		SquarePosInit( float p_minx = 0.f , float p_maxx = 200.f , float p_miny = 0.f , float p_maxy = 200.f ) noexcept;
		~SquarePosInit() = default;

		void
		init(ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept override;
		
	};

}