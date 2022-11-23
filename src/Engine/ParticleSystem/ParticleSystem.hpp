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

		//Aquí habrá que ver el constructor de copia de cada emiiter pq sinos va a ser locura reutilizar emmiters
		Emitter&
		addEmitter(  ) noexcept;

		void
		updateSystem() noexcept;

	};

}