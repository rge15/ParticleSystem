#pragma once
#include "BaseInit.hpp"

namespace ParticleSystem
{

	class ConstColorInit : public BaseInit
	{
	private:
		float _r { 0.f }, _g { 0.f }, _b { 0.f}, _a{ 0.f };
	public:
		ConstColorInit(float p_r = 0.f, float p_g = 0.f, float p_b = 0.f, float p_a = 0.f ) noexcept;
		~ConstColorInit() = default;

		void
		init(Particle& p_particle) const noexcept override;
		
	};

}