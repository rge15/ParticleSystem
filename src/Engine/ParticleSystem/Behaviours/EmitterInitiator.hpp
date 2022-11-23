#pragma once
#include <utilities/alias.hpp>
#include <Engine/utils/metaProggraming.hpp> 
#include <Engine/ParticleSystem/Behaviours/Inits/initIncludes.hpp>
#include <Engine/utils/concepts.hpp>
#include <Engine/ParticleSystem/Particle.hpp>

namespace ParticleSystem
{

	class EmitterInitiator
	{
	private:
		Vector<uniqPtr<BaseInit>> _inits {};

	public:
		EmitterInitiator() = default;
		~EmitterInitiator() = default;
	
		//Base Template Overloading with Tag Dispatching Definition
		template<initerBehaviour T, typename... args>
		T&
		addInit( args&&... p_params ) noexcept;

	private:
		//Template Overloadings
		inline ConstPosInit&
		addInit( MP::Class<ConstPosInit> , float p_x, float p_y, float p_z );

		inline ConstColorInit&
		addInit( MP::Class<ConstColorInit> , float p_r, float p_g, float p_b, float p_a );

		inline ConstSpeedInit&
		addInit( MP::Class<ConstSpeedInit> , float p_speedX, float p_speedY, float p_speedZ );

		inline ConstLifeInit&
		addInit( MP::Class<ConstLifeInit> , float p_life );

	};	

}

#include "EmitterInitiator.tpp"