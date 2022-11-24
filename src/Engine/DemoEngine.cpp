#include "DemoEngine.hpp"


DemoEngine::DemoEngine() noexcept
{
	ptc_open("Particle System - BitBoy", _widthScr, _heightScr);
	memset( _buffer, 0, sizeof(_buffer) );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DemoEngine::~DemoEngine()
{
	ptc_close();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DemoEngine::Draw() noexcept
{
	_drawer.get()->Draw();
}