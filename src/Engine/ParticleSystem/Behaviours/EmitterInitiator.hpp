#pragma once
#include <utilities/alias.hpp>
#include <Engine/utils/metaProggraming.hpp> 
#include <Engine/utils/concepts.hpp>
#include <Engine/ParticleSystem/Particle.hpp>
#include <Engine/ParticleSystem/Behaviours/Inits/initIncludes.hpp>

namespace ParticleSystem
{

	class EmitterInitiator
	{
	public:
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
		template<initerBehaviour T>
		inline T&
		addInit( MP::Class<T> );
		
		//Template Overloadings
		inline ConstPosInit&
		addInit( MP::Class<ConstPosInit> , int p_x, int p_y );

		inline ConstColorInit&
		addInit( MP::Class<ConstColorInit> , float p_r, float p_g, float p_b, float p_a );

		inline ConstSpeedInit&
		addInit( MP::Class<ConstSpeedInit> , float p_speedX, float p_speedY );

		inline ConstLifeInit&
		addInit( MP::Class<ConstLifeInit> , float p_life );

		inline SquarePosInit&
		addInit( MP::Class<SquarePosInit> , int p_minx, int p_maxx, int p_miny, int p_maxy );

	};	

}

#include "EmitterInitiator.tpp"