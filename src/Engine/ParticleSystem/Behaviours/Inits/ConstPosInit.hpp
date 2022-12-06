#pragma once
#include "BaseInit.hpp"

namespace ParticleSystem
{

	class ConstPosInit : public BaseInit
	{
	private:
		float _x { 0.f }, _y { 0.f };
	public:
		ConstPosInit( float p_x = 0.f , float p_y = 0.f ) noexcept;
		~ConstPosInit() = default;

		void
		init(ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept override;
		
	};

}