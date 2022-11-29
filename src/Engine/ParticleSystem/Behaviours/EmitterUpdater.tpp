
//TODO : En el particleEmitter meter código para poder incluir particle updateBehaviour
namespace ParticleSystem
{

	template<updateBehaviour T, typename... args>
	T&
	EmitterUpdater::addUpdater( args&&... p_params ) noexcept
	{
		return addUpdater( MP::Class<T>{}, std::forward<args>(p_params)... );
	}

	//No params Update Class
	template<updateBehaviour T>
	T&
	EmitterUpdater::addUpdater( MP::Class<T> ) noexcept
	{
		_updates.push_back(std::make_unique<T>());

		auto& updater = static_cast<T&>( *_updates.back().get() );

		return updater;
	}

}