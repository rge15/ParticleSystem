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
		if(_values.size() != 0)
			avgTheValues();
		
		writeToFile();
	}

	void
	BenchTimer::startRecord() noexcept
	{
		_start = Clock::now();
	}
	
	void
	BenchTimer::stopRecord( time_point<Clock> p_timeStoped ) noexcept
	{
		auto ellapsedTime = duration_cast<milliseconds>(p_timeStoped - _start);
		
		_values.push_back( ellapsedTime );

		if( _values.size() == _values.capacity() )
			avgTheValues();
	}

	//TODO : Deberiamos mover esto de otra forma para cuando se destruya y lo escriba, pq si no va a afectar al rendimiento
	void
	BenchTimer::avgTheValues() noexcept
	{
		milliseconds::rep avgTime { milliseconds::zero().count() };
		milliseconds::rep max { milliseconds::min().count() };
		milliseconds::rep min { milliseconds::max().count() };
		milliseconds::rep valueCount;
		
		for(auto& value : _values)
		{
			valueCount = value.count();

			avgTime += valueCount;
			
			if( valueCount > max )
				max = valueCount;
		
			if(valueCount < min)
				min = valueCount;
		}

		avgTime /= _values.size();

		// std::cout << "--------------- Timer of {" << _name << "} results ---------------" << '\n';
		// std::cout << "Max Time : [" << float(max)/1000 << "] , Min Time : [" << float(min)/1000 << "] , Avg Time [" << float(avgTime)/1000 << "]\n";

		addFramerData( max, min, avgTime );
		cleanValues();
	}

	void
	BenchTimer::addFramerData( milliseconds::rep max, milliseconds::rep min, milliseconds::rep avgTime ) noexcept
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
			file << "Max Time : [" << float(max)/1000 << "] , Min Time : [" << float(min)/1000 << "] , Avg Time [" << float(avg)/1000 << "]\n";
		}
		file.close();
	}

}
