#pragma once
#include "BaseInit.hpp"

namespace ParticleSystem
{

	class ConstLifeInit : public BaseInit
	{
	public:
		float _initLifeTime { 1.f };

	public:
		explicit ConstLifeInit(float p_initLifeTime);
		
		~ConstLifeInit() = default;
	
		void
		init(Particle& p_particle) const noexcept override;
	
	};

}