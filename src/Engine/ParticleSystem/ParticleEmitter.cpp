#include "ParticleEmitter.hpp"

namespace ParticleSystem
{

	void
	Emitter::setResource( Graphics::BaseResource& p_resource ) noexcept
	{
		_resource = &p_resource;
	}

	void
	Emitter::update() noexcept
	{
		//Llamar a spawner de partículas
		
		//Llamar a modifiers de partículas
	
		//Llamar a borrador de partículas
	}


}