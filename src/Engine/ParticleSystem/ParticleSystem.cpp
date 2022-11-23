#include "ParticleSystem.hpp"


namespace ParticleSystem
{

	ParticleSystem::ParticleSystem( int p_updateRate )
	: _updateRate { p_updateRate }
	{
	}
	
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	Emitter&
	ParticleSystem::addEmitter( ) noexcept
	{
		_emiters.push_back( std::make_unique<Emitter>() );

		return *_emiters.back().get();		
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	ParticleSystem::updateSystem() noexcept
	{
		if( _timer.update() )
		{
			for(auto& emitter : _emiters)
			{
				emitter.get()->update();
			}
		}
	}


}
