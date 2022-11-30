#include <utilities/alias.hpp>
#include <chrono>
#include <fstream>

namespace Benchmark
{
	using namespace std::chrono;	
	using BenchClock = std::conditional_t< high_resolution_clock::is_steady, high_resolution_clock, steady_clock> ;
	using TimeMeasure = nanoseconds;

	class BenchTimer
	{	
		// maxFrameTime, minFrameTime, avgFrameTime
		using FrameTime = Tuple<TimeMeasure::rep, TimeMeasure::rep, TimeMeasure::rep>;
		
		private:
			std::string _name;

			std::size_t _valuesToAvg;
			Vector<TimeMeasure> _values;

			std::size_t _framesWritting { 0 };
			Array<FrameTime,20> _timerData;

			time_point<BenchClock> _start;

			void
			avgTheValues() noexcept;

			void
			addFramerData( TimeMeasure::rep max, TimeMeasure::rep min, TimeMeasure::rep avgTime ) noexcept;
			
			void
			cleanValues() noexcept;

			void
			writeToFile() noexcept;

		public:
			BenchTimer(std::string& p_name, std::size_t p_valuesToAvg) noexcept;
			~BenchTimer() noexcept;

			void
			startRecord() noexcept;
			
			void
			stopRecord( time_point<BenchClock> p_timeStoped ) noexcept;
	};
}