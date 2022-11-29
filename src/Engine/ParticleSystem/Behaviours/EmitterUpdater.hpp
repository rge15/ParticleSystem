#pragma once
#include <Engine/ParticleSystem/Behaviours/Updates/updateIncludes.hpp>
#include <Engine/utils/concepts.hpp>
#include <Engine/utils/metaProggraming.hpp>

namespace ParticleSystem
{

	class EmitterUpdater
	{
	private:

		Vector<uniqPtr<BaseUpdater>> _updates{};

	public:
		EmitterUpdater() = default;
		~EmitterUpdater() = default;

		void
		updateParticles( Vector<Particle>& p_particles ) const noexcept;

		template<updateBehaviour T, typename... args>
		T&
		addUpdater( args&&... p_params ) noexcept;

	private:

		//No params Update Class
		template<updateBehaviour T>
		T&
		addUpdater( MP::Class<T> ) noexcept;

	};
}

#include "EmitterUpdater.tpp"