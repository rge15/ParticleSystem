#pragma once
#include "BaseInit.hpp"

namespace ParticleSystem
{

	class ConstPosInit : public BaseInit
	{
	private:
		int _x { 0 }, _y { 0 };
	public:
		ConstPosInit( int p_x = 0 , int p_y = 0 ) noexcept;
		~ConstPosInit() = default;

		void
		init(Particle& p_particle) const noexcept override;
		
	};

}