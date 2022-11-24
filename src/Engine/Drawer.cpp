#include "Drawer.hpp"


Drawer::Drawer( uint32_t* p_buffer )
: _buffer { *p_buffer }
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
Drawer::Draw() noexcept
{
	_timer.reset();
	
	//Draw Logic
	for(auto& pSystem : _pSystems)
	{
		pSystem.get()->updateSystem( &_buffer );
	}

	updateDraw();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
Drawer::updateDraw() noexcept
{
	ptc_update( &_buffer );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

ParticleSystem::ParticleSystem&
Drawer::addParticleSystem() noexcept
{
	_pSystems.push_back( std::make_unique<ParticleSystem::ParticleSystem>() );

	return *( _pSystems.back().get() );
}

