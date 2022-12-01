#include "BenchTimer.hpp"


namespace Benchmark
{
	BenchTimer::BenchTimer( std::string& p_name , std::size_t p_valuesToAvg) noexcept
	: _name { p_name }, _valuesToAvg { p_valuesToAvg }
	{
		_values.reserve(_valuesToAvg);
	}
	
	BenchTimer::~BenchTimer() noexcept
	{
		writeToFile();
	}

	void
	BenchTimer::startRecord() noexcept
	{
		_start = BenchClock::now();
	}
	
	void
	BenchTimer::stopRecord( time_point<BenchClock> p_timeStoped ) noexcept
	{
		auto init = std::chrono::time_point_cast<TimeMeasure>(_start).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<TimeMeasure>(p_timeStoped).time_since_epoch().count();
		
		auto ellapsedTime = end - init;

		_values.push_back( ellapsedTime );

		if( _values.size() == _values.capacity() )
			avgTheValues();
	}

	//TODO : Deberiamos mover esto de otra forma para cuando se destruya y lo escriba, pq si no va a afectar al rendimiento
	void
	BenchTimer::avgTheValues() noexcept
	{
		TimeMeasure::rep avgTime { TimeMeasure::zero().count() };
		TimeMeasure::rep max { TimeMeasure::min().count() };
		TimeMeasure::rep min { TimeMeasure::max().count() };
		TimeMeasure::rep valueCount;
		
		for(auto& value : _values)
		{
			valueCount = value;

			avgTime += valueCount;
			
			if( valueCount > max )
				max = valueCount;
		
			if(valueCount < min)
				min = valueCount;
		}

		avgTime /= _values.size();

		addFramerData( max, min, avgTime );
		cleanValues();
	}

	void
	BenchTimer::addFramerData( TimeMeasure::rep max, TimeMeasure::rep min, TimeMeasure::rep avgTime ) noexcept
	{
		_timerData[ _framesWritting++ ] = FrameTime(max, min, avgTime);
		if(_framesWritting >= _timerData.size())
			_framesWritting -= _timerData.size();
	}

	void
	BenchTimer::cleanValues() noexcept
	{
		_values.erase(_values.begin(), _values.end());
	}

	void
	BenchTimer::writeToFile() noexcept
	{
		std::ofstream file;
		file.open(_name+"Timer.txt");
		file << "--------------- Timer of {" << _name << "} results ---------------" << '\n';
		for(auto& val : _timerData)
		{
			auto [max, min, avg] = val;
			file << "Max Time : [" << double(max)*0.001 << "] , Min Time : [" << double(min)*0.001 << "] , Avg Time [" << double(avg)*0.001 << "]\n";
		}
		file.close();
	}

}
