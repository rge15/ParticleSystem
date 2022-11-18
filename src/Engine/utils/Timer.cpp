#include "Timer.hpp"


DemoTimer::DemoTimer( int p_frameRate ) noexcept
: _frameRate { p_frameRate }
{}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

double
DemoTimer::ellapsedTime() const noexcept
{
	return ( DemoTimer::clock::now() - _initTime ).count();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DemoTimer::reset( int p_frameRate ) noexcept
{
	if( p_frameRate > 0 )
	{
		_frameRate = p_frameRate;
		_refreshTime = 1.f/p_frameRate;
	}
	_initTime = clock::now();
	_lastTime = 0.f ;
	_totalFXTime = 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

double
DemoTimer::ellapsedSeconds() const noexcept
{
	return ( ellapsedTime() / 1000000000.0f );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

double
DemoTimer::deltaTime() noexcept
{
	return ellapsedSeconds() - _lastTime;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool
DemoTimer::updateDraw() noexcept
{
	if( deltaTime() >= _refreshTime )
	{
		_lastTime = ellapsedSeconds();
		return true;
	}
	return false;
}

