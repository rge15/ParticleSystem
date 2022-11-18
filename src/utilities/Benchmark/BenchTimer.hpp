#include <utilities/alias.hpp>
#include <chrono>
#include <fstream>

namespace Benchmark
{
	using namespace std::chrono;	
	using Clock = std::conditional_t< high_resolution_clock::is_steady, high_resolution_clock, steady_clock> ;

	class BenchTimer
	{	
		// maxFrameTime, minFrameTime, avgFrameTime
		using FrameTime = Tuple<milliseconds::rep, milliseconds::rep, milliseconds::rep>;
		
		private:
			std::string _name;

			std::size_t _valuesToAvg;
			Vector<milliseconds> _values;

			std::size_t _framesWritting { 0 };
			Array<FrameTime,10> _timerData;

			time_point<Clock> _start;

			void
			avgTheValues() noexcept;

			void
			addFramerData( milliseconds::rep max, milliseconds::rep min, milliseconds::rep avgTime ) noexcept;
			
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
			stopRecord( time_point<Clock> p_timeStoped ) noexcept;
	};
}