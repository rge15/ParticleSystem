#include "Benchmarker.hpp"

namespace Benchmark
{
	Benchmarker::Benchmarker(/* args */)
	{
	}
	
	Benchmarker::~Benchmarker()
	{
	}

	void
	Benchmarker::setTimer(std::string p_name, std::size_t p_valuesToAvg ) noexcept
	{
		BenchTimer* timer {nullptr};

		if( _timers.contains(p_name) )
			timer = _timers.find(p_name)->second.get();
		else
		{
			_timers.insert( { p_name, std::make_unique<BenchTimer>( p_name,p_valuesToAvg) } );
			timer = _timers.find(p_name)->second.get();
		}

		_listenerTimers.push( timer );
		
		timer->startRecord();
	}
	
	void
	Benchmarker::stopTimer() noexcept
	{
		auto endTime = Clock::now();

		auto timer = _listenerTimers.top();
		_listenerTimers.pop();
		
		timer->stopRecord(endTime);
	}

}