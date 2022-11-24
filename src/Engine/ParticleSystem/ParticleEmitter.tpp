
namespace ParticleSystem
{
	template<initerBehaviour T, typename... args>
	T&
	Emitter::addEmmiterInit(args&&... p_params)
	{
		auto& init = _initiator.addInit<T>(std::forward<args>(p_params)... );

		return init;
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	template<spawnBehaviour T, typename... args>
	T&
	Emitter::addEmmiterSpawn(args&&... p_params)
	{
		auto& spawn = _spawner.addSpawn<T>(std::forward<args>(p_params)... );

		return spawn;
	}

}