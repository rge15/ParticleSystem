#include <Engine/DemoEngine.hpp>
#include <utilities/Benchmark/Benchmarker.hpp>
#include <algorithm>

int main()
{
	DemoEngine engine{};
	Drawer& draw = engine.getDrawer();

	Benchmark::Benchmarker bench {};

	return 0;
}