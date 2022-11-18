#include <utilities/alias.hpp>
#include "BenchTimer.hpp"

namespace Benchmark
{
	class Benchmarker
	{
	private:
		static const std::size_t _avgValuesInTimer { 30 };

		unorderMap<std::string, uniqPtr<BenchTimer>> _timers {};

		Stack<BenchTimer*> _listenerTimers {};

	public:
		Benchmarker();
		~Benchmarker();
		
		void
		setTimer(std::string p_name, std::size_t p_valuesToAvg = _avgValuesInTimer ) noexcept;
		
		void
		stopTimer() noexcept;
	};
}