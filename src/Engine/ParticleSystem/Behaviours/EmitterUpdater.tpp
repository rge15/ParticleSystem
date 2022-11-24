
//TODO : En el particleEmitter meter código para poder incluir particle updateBehaviour
namespace ParticleSystem
{

	template<updateBehaviour T, typename... args>
	T&
	EmitterUpdater::addUpdater( args&&... p_params ) noexcept
	{
		return addUpdater( MP::Class<T>{}, std::forward<args>(p_params)... );
	}

	inline ApplySpeedUpdater&
	EmitterUpdater::addUpdater( MP::Class<ApplySpeedUpdater> ) noexcept
	{
		_updates.push_back(std::make_unique<ApplySpeedUpdater>());

		auto& updater = static_cast<ApplySpeedUpdater&>( *_updates.back().get() );

		return updater;
	}

}