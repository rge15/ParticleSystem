#pragma once
#include "BaseInit.hpp"
#include <Engine/utils/macros.hpp>
#include <Engine/DataTypes/Color.hpp>
namespace ParticleSystem
{

	class ConstColorInit : public BaseInit
	{
	private:
		Color _initColor;
		// uint8_t A,R,G,B;
		// uint32_t _ARGB {};
	public:
		ConstColorInit(float p_r = 0.f, float p_g = 0.f, float p_b = 0.f, float p_a = 0.f ) noexcept;
		~ConstColorInit() = default;

		void
		init(Particle& p_particle) const noexcept override;
		
	};

}