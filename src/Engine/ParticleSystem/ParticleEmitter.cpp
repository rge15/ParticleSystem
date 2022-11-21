#include "ParticleEmitter.hpp"

namespace ParticleSystem
{

	void
	Emitter::setResource( Graphics::BaseResource& p_resource ) noexcept
	{
		_resource = &p_resource;
	}


}