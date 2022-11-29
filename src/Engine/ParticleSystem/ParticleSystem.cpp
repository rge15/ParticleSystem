#include "ParticleSystem.hpp"


namespace ParticleSystem
{


	Emitter&
	ParticleSystem::addEmitter( ) noexcept
	{
		_emiters.push_back( std::make_unique<Emitter>() );

		return *_emiters.back().get();		
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	ParticleSystem::updateSystem( uint32_t* p_buffer ) noexcept
	{
		//TODO : Debería actualizarse por un lado y dibujarse siempre que se pida
		for(auto& emitter : _emiters)
		{
			emitter.get()->update( p_buffer );
		}
		
	}


}
