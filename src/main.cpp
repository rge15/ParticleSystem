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

	pEmitter.addEmitterSpawn<ParticleSystem::RatioSpawner>( 1, 2.f );

	//? Se añaden bien, ahora falta comprobar que funcionen bien
	pEmitter.addEmitterInit<ParticleSystem::ConstPosInit>( 10 , 20  );
	pEmitter.addEmitterInit<ParticleSystem::ConstSpeedInit>( 4.f,0.f );
	pEmitter.addEmitterInit<ParticleSystem::ConstColorInit>( .5f,1.f,0.f,1.f );
	pEmitter.addEmitterInit<ParticleSystem::ConstLifeInit>( 1.f );

	pEmitter.addEmitterUpdate<ParticleSystem::ApplySpeedUpdater>();

	while (true)
	{
		draw.Draw();
	}

	return 0;
}