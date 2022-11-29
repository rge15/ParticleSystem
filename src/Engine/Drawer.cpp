#include "Drawer.hpp"


void
Drawer::Draw( uint32_t& p_buffer ) noexcept
{
	// _timer.reset();
	
	//Draw Logic
	for(auto& pSystem : _pSystems)
	{
		pSystem.get()->updateSystem( &p_buffer );
	}

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

ParticleSystem::ParticleSystem&
Drawer::addParticleSystem() noexcept
{
	_pSystems.push_back( std::make_unique<ParticleSystem::ParticleSystem>() );

	return *( _pSystems.back().get() );
}

