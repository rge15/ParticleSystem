
namespace ParticleSystem
{
	template<initerBehaviour T, typename... args>
	T&
	Emitter::addEmitterInit(args&&... p_params)
	{
		auto& init = _initiator.addInit<T>(std::forward<args>(p_params)... );

		return init;
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	template<spawnBehaviour T, typename... args>
	T&
	Emitter::addEmitterSpawn(args&&... p_params)
	{
		auto& spawn = _spawner.addSpawn<T>(std::forward<args>(p_params)... );

		return spawn;
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	template<updateBehaviour T, typename... args>
	T&
	Emitter::addEmitterUpdate(args&&... p_params)
	{
		return _updater.addUpdater<T>( std::forward<args>(p_params)... );
	}

}