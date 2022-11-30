#include <Engine/DemoEngine.hpp>
#include <utilities/Benchmark/Benchmarker.hpp>
#include <Engine/ParticleSystem/ParticleSystem.hpp>
#include <Engine/GraphicResource/ParticleSprite.hpp>

int main()
{
	DemoEngine engine{};
	Drawer& draw = engine.getDrawer();
	uniqPtr<Benchmark::Benchmarker> bench = std::make_unique<Benchmark::Benchmarker>();

	auto& pSystem = draw.addParticleSystem();

	auto& pEmitter = pSystem.addEmitter();

	auto pSprite = Graphics::ParticleSprite("rsc/particle1.png");
	pEmitter.setResource( pSprite );
	pEmitter.addEmitterSpawn<ParticleSystem::RatioSpawner>( 3, .2f );
	pEmitter.addEmitterInit<ParticleSystem::SquarePosInit>( 0, 10 , 0, 400);
//	pEmitter.addEmitterInit<ParticleSystem::ConstPosInit>( 10 , 20  );
	pEmitter.addEmitterInit<ParticleSystem::ConstSpeedInit>( 2.5f,0.f );
	pEmitter.addEmitterInit<ParticleSystem::ConstColorInit>( .5f,1.f,0.f,1.f );
	pEmitter.addEmitterInit<ParticleSystem::ConstLifeInit>( 3.5f );

	pEmitter.addEmitterUpdate<ParticleSystem::TimeUpdater>();
	pEmitter.addEmitterUpdate<ParticleSystem::ApplySpeedUpdater>();


	auto& pEmitter2 = pSystem.addEmitter();

	auto pSprite2 = Graphics::ParticleSprite("rsc/particle.png");
	pEmitter2.setResource( pSprite2 );
	pEmitter2.addEmitterSpawn<ParticleSystem::RatioSpawner>( 1, .1f );
	pEmitter2.addEmitterInit<ParticleSystem::SquarePosInit>( 0, 10 , 0, 400);
//	pEmitter2.addEmitterInit<ParticleSystem::ConstPosInit>( 10 , 20  );
	pEmitter2.addEmitterInit<ParticleSystem::ConstSpeedInit>( 4.f,0.f );
	pEmitter2.addEmitterInit<ParticleSystem::ConstColorInit>( .1f,.9f,1.f,1.f );
	pEmitter2.addEmitterInit<ParticleSystem::ConstLifeInit>( 2.5f );

	pEmitter2.addEmitterUpdate<ParticleSystem::TimeUpdater>();
	pEmitter2.addEmitterUpdate<ParticleSystem::ApplySpeedUpdater>();


	while (!ptc_process_events())
	{
		bench.get()->setTimer("BasicDraw");
		engine.Draw();
		bench.get()->stopTimer();
	}


	return 0;
}