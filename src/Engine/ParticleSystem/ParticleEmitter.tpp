
namespace ParticleSystem
{
	template<initerBehaviour T, typename... args>
	T&
	Emitter::addEmmiterInit(args&&... p_params)
	{
		auto& init = _initiator.addInit<T>(std::forward<args>(p_params)... );

		return init;
	}

}