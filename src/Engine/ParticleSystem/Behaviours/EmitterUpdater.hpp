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

		inline ApplySpeedUpdater&
		addUpdater( MP::Class<ApplySpeedUpdater> ) noexcept;

	};
}

#include "EmitterUpdater.tpp"