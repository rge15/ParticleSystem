#include "DemoEngine.hpp"


DemoEngine::DemoEngine() noexcept
{
	ptc_open("Particle System - BitBoy", _widthScr, _heightScr);
	memset( _buffer1, 0, sizeof(_buffer1) );
	memset( _buffer2, 0, sizeof(_buffer2) );
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
	if(_timer.update())
	{
		//bench.get()->setTimer("BasicDraw");
		updateBuffer();
		_drawer.get()->Draw( *_drawBuffer );
		swapDoubleBuffer();
		//bench.get()->stopTimer();
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DemoEngine::updateBuffer() noexcept
{
	ptc_update( _readBuffer );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DemoEngine::swapDoubleBuffer() noexcept
{
	auto* aux = _readBuffer;
	_readBuffer = _drawBuffer;
	_drawBuffer = aux;
	
	memset( _drawBuffer, 0, sizeof(_buffer1) );
}
