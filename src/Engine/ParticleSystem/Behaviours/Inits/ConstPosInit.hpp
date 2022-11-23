#pragma once
#include "BaseInit.hpp"

namespace ParticleSystem
{

	class ConstPosInit : public BaseInit
	{
	private:
		float _x { 0.f }, _y { 0.f }, _z { 0.f};
	public:
		ConstPosInit(float p_x = 0.f, float p_y = 0.f, float p_z = 0.f ) noexcept;
		~ConstPosInit() = default;

		void
		init(Particle& p_particle) const noexcept override;
		
	};

}