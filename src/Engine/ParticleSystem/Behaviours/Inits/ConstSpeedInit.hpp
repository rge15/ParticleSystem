#pragma once
#include "BaseInit.hpp"

namespace ParticleSystem
{

	class ConstSpeedInit : public BaseInit
	{
	private:
		float _vx { 0.f }, _vy { 0.f };
	public:
		ConstSpeedInit(float p_x = 0.f, float p_y = 0.f ) noexcept;
		~ConstSpeedInit() = default;

		void
		init(ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept override;
		
	};

}