
namespace ParticleSystem
{
	//Base Template Overloading with Tag Dispatching Definition
	template<spawnBehaviour T, typename... args>
	T&
	EmitterSpawner::addSpawn( args&&... p_params ) noexcept
	{
		std::cout << "Añado un spwaner of type : ";
		return addSpawn( MP::Class<T>{}, std::forward<args>(p_params)... );
	}

	//Template Overloadings
	RatioSpawner&
	EmitterSpawner::addSpawn( MP::Class<RatioSpawner> , int p_spawnParticles, float p_spawnRateSeconds )
	{
		std::cout << " Ratio \n";
		
		_spawners.push_back( std::make_unique<RatioSpawner>(p_spawnParticles, p_spawnRateSeconds) );
	
		auto& spawner = static_cast<RatioSpawner&>( *_spawners.back().get() );

		return spawner;
	}

}