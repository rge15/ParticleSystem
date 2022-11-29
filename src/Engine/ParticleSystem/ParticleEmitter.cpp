#include "ParticleEmitter.hpp"

namespace ParticleSystem
{

	void
	Emitter::setResource( Graphics::ParticleSprite& p_resource ) noexcept
	{
		_resource = &p_resource;
	}

	void
	Emitter::update( uint32_t* const p_buffer ) noexcept
	{
		//Llamar a spawner de partículas
		for(auto& spawner : _spawner._spawners)
		{
			spawner.get()->spawn( _particles, _initiator._inits );
		}

		//Llamar a updaters de partículas
		_updater.updateParticles( _particles );

		//Dibujar particulas
		for(auto& particle : _particles)
		{
			_resource->drawParticle( p_buffer,  _pos, particle );
		}

		//Llamar a borrador de partículas y a reordenación
		
	}	

}