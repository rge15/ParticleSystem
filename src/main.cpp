#include <Engine/DemoEngine.hpp>
#include <utilities/Benchmark/Benchmarker.hpp>
#include <Engine/ParticleSystem/ParticleSystem.hpp>
#include <Engine/GraphicResource/ParticleSprite.hpp>

int main()
{
	DemoEngine engine{};
	Drawer& draw = engine.getDrawer();
	Benchmark::Benchmarker bench {};

	auto& pSystem = draw.addParticleSystem();

	auto& pEmitter = pSystem.addEmitter();

	auto pSprite = Graphics::ParticleSprite("rsc/Particle.png");

	pEmitter.setResource( pSprite );

	pEmitter.addEmmiterSpawn<ParticleSystem::RatioSpawner>( 1, 2.f );

	//? Se añaden bien, ahora falta comprobar que funcionen bien
	pEmitter.addEmmiterInit<ParticleSystem::ConstPosInit>( 10 , 20  );
	pEmitter.addEmmiterInit<ParticleSystem::ConstSpeedInit>( 1.f,2.f );
	pEmitter.addEmmiterInit<ParticleSystem::ConstColorInit>( .5f,1.f,0.f,1.f );
	pEmitter.addEmmiterInit<ParticleSystem::ConstLifeInit>( 1.f );

	while (true)
	{
		draw.Draw();
	}
	

	return 0;
}