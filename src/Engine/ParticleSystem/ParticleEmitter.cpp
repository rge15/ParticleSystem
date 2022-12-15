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
		drawParticles( p_buffer );

		////Llamar a borrador de partículas y a reordenación
		killOldParticles();
	}

	void
	Emitter::drawParticles(uint32_t* const p_buffer) noexcept
	{
		auto& vecPos = _particles.getDataVector<Position>();
		auto& vecColor = _particles.getDataVector<Color>();

		auto color = vecColor.begin(); 
		for(auto& position : vecPos )
		{
			_resource->drawParticleSSE2( p_buffer, _pos, position, *color );
			++color; 
		}
	}

	void
	Emitter::killOldParticles() noexcept
	{
		auto& vecLife = _particles.getDataVector<Life>();

		auto& clearVec = _particles.getClearVector();

		int i = 0;
		for(auto& life : vecLife)
		{
			if( life._currLifeTime >= life._totalLifeTime)
				_particles.autoDeleteSlot(clearVec.data()[i]);
			i++;
		}
	}


}