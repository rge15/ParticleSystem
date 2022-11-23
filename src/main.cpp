#include <Engine/DemoEngine.hpp>
#include <utilities/Benchmark/Benchmarker.hpp>
#include <Engine/ParticleSystem/ParticleSystem.hpp>
#include <algorithm>

int main()
{
	DemoEngine engine{};
	Drawer& draw = engine.getDrawer();
	Benchmark::Benchmarker bench {};

	ParticleSystem::Emitter _emitter1 {};
	//? Se añaden bien, ahora falta comprobar que funcionen bien
	_emitter1.addEmmiterInit<ParticleSystem::ConstPosInit>( 1.f,2.f,3.f );
	_emitter1.addEmmiterInit<ParticleSystem::ConstSpeedInit>( 1.f,2.f,3.f );
	_emitter1.addEmmiterInit<ParticleSystem::ConstColorInit>( 1.f,2.f,3.f,1.f );
	_emitter1.addEmmiterInit<ParticleSystem::ConstLifeInit>( 1.f );

	return 0;
}