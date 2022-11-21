#pragma once
#include <utilities/alias.hpp>
#include <Engine/utils/Timer.hpp>
#include "ParticleEmitter.hpp"

namespace ParticleSystem
{
	class ParticleSystem
	{
		using Emitters = Vector<uniqPtr<Emitter>>;

	private:
		Emitters _emiters {};

		int _updateRate { 60 };

		Timer _timer { _updateRate };

	public:
		ParticleSystem( int p_updateRate = 60 );
		~ParticleSystem() = default;

		Emitter&
		addEmitter( Emitter&& p_emitter ) noexcept;

		void
		updateSystem() noexcept;

	};

}