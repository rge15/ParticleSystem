#pragma once
#include <utilities/alias.hpp>
#include "ParticleEmitter.hpp"

namespace ParticleSystem
{
	class ParticleSystem
	{
		using Emitters = Vector<uniqPtr<Emitter>>;

	private:
		Emitters _emiters {};

	public:
		ParticleSystem() = default;
		~ParticleSystem() = default;

		//Aquí habrá que ver el constructor de copia de cada emiter pq sinos va a ser locura reutilizar emmiters
		Emitter&
		addEmitter() noexcept;

		void
		updateSystem( uint32_t* p_buffer ) noexcept;

	};

}