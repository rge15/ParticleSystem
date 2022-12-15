#include <Engine/DemoEngine.hpp>
#include <Engine/ParticleSystem/ParticleSystem.hpp>
#include <Engine/GraphicResource/ParticleSprite.hpp>
#include <Engine/DataStructures/Slotmap.hpp>
#include <Engine/ParticleSystem/ParticleAttributeIncludes.hpp>

// int main()
// {
// 	//TODO : Check q funciona
// 	Slotmap<Position,Color,Speed,Life> slot{};
// 	auto par1 = slot.addSlot();
// 	auto par2 = slot.addSlot();
// 	auto par3 = slot.addSlot();
// 	auto par4 = slot.addSlot();
// 	auto par5 = slot.addSlot();

// 	auto& vecPosition = slot.getDataVector<Position>();
// 	std::cout << "Vec Position Parts " << vecPosition.size() << '\n';

// 	for(auto& pos : vecPosition)
// 	{
// 		std::cout << "Vec x : " << pos.x << " y : " << pos.y << '\n';
// 	}

// 	int i = 0;
// 	for(auto& pos : vecPosition)
// 	{
// 		pos.y = -i;
// 		pos.x = i++;
// 	}
// 	std::cout << "&&&&&&&&&&&&&&&" << '\n';

// 	for(auto& pos : vecPosition)
// 	{
// 		std::cout << "Vec x : " << pos.x << " y : " << pos.y << '\n';
// 	}
	
// 	auto& vecLife = slot.getDataVector<Life>();
// 	std::cout << "Vec Life Parts " << vecLife.size() << '\n';
	
// 	i = 0;
// 	for(auto& life : vecLife)
// 	{
// 		life._totalLifeTime = i++;
// 		std::cout << "Pos in memory " << &life << '\n';
// 		std::cout << "Life setted to " << life._totalLifeTime << '\n';
// 		//std::cout << "Life current time : " << life._initLife.time_since_epoch().count() << '\n';
// 	}

// 	i = 0;

// 	for(i = 0;i < vecLife.size();i++)
// 	{
// 		if( (i%2) == 0)
// 		{
// 			std::cout << "Borro el slot : " << i << '\n';
// 			slot.autoDeleteSlot(i);
// 		}
// 	}

// 	std::cout << "Vec Position Parts " << vecPosition.size() << '\n';

// 	for(auto& pos : vecPosition)
// 	{
// 		std::cout << "Vec x : " << pos.x << " y : " << pos.y << '\n';
// 	}

// 	i= 0;
// 	std::cout << "Size of life obj : " << sizeof(Life) << '\n';
// 	for(auto& life : vecLife)
// 	{
// 		std::cout << "Vec life in : " << i << " Vida del elementos : " << life._totalLifeTime << '\n';
// 		std::cout << "Pos in memori of reference : " << &life << " and in data vector pos : " << &vecLife.data()[i++] << '\n';
// 	}

// 	auto& life = slot.getItem<Life>(par2);

// 	std::cout << "Pos in memory of get Item Life en pos 1 : " << &life << " and data in : " << life._totalLifeTime << '\n';
	


// }

int main()
{
	DemoEngine engine{};
	Drawer& draw = engine.getDrawer();

	auto& pSystem = draw.addParticleSystem();

	auto& pEmitter = pSystem.addEmitter();

	auto pSprite = Graphics::ParticleSprite("rsc/particle2.png");
	pEmitter.setResource( pSprite );
	pEmitter.addEmitterSpawn<ParticleSystem::RatioSpawner>( 3, .5f );
	pEmitter.addEmitterInit<ParticleSystem::SquarePosInit>( 0., 0. , 10., 100.);
	//pEmitter.addEmitterInit<ParticleSystem::ConstPosInit>( 10 , 0  );
	pEmitter.addEmitterInit<ParticleSystem::ConstSpeedInit>( 1.f,0.f );
	pEmitter.addEmitterInit<ParticleSystem::ConstColorInit>( 1.f,0.f,1.f,1.f );
	pEmitter.addEmitterInit<ParticleSystem::ConstLifeInit>( 2.f );

	pEmitter.addEmitterUpdate<ParticleSystem::TimeUpdater>();
	pEmitter.addEmitterUpdate<ParticleSystem::ApplySpeedUpdater>();


	// auto& pEmitter2 = pSystem.addEmitter();

	// auto pSprite2 = Graphics::ParticleSprite("rsc/particle.png");
	// pEmitter2.setResource( pSprite2 );
	// pEmitter2.addEmitterSpawn<ParticleSystem::RatioSpawner>( 30, .1f );
	// pEmitter2.addEmitterInit<ParticleSystem::SquarePosInit>( 0, 10 , 0, 400);
// //	pEmitter2.addEmitterInit<ParticleSystem::ConstPosInit>( 10 , 20  );
	// pEmitter2.addEmitterInit<ParticleSystem::ConstSpeedInit>( 4.f,0.f );
	// pEmitter2.addEmitterInit<ParticleSystem::ConstColorInit>( .1f,.9f,1.f,1.f );
	// pEmitter2.addEmitterInit<ParticleSystem::ConstLifeInit>( 2.5f );

	// pEmitter2.addEmitterUpdate<ParticleSystem::TimeUpdater>();
	// pEmitter2.addEmitterUpdate<ParticleSystem::ApplySpeedUpdater>();


	while (!ptc_process_events())
	{
		engine.Draw();
	}


	return 0;
}