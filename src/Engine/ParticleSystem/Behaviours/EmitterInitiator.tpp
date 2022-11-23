
namespace ParticleSystem
{

	//Base Template Overloading with Tag Dispatching Definition
	template<initerBehaviour T, typename... args>
	T&
	EmitterInitiator::addInit( args&&... p_params ) noexcept
	{
		std::cout << "Añado un initiator of type : ";
		auto& initer = addInit( MP::Class<T>{}, std::forward<args>(p_params)... );
	
		return initer;
	}

	//Template Overloadings
	ConstPosInit&
	EmitterInitiator::addInit( MP::Class<ConstPosInit> , float p_x, float p_y, float p_z )
	{
		std::cout << " Position \n";

		_inits.push_back(std::make_unique<ConstPosInit>( p_x, p_y, p_z ));		

		auto& initer = static_cast<ConstPosInit&>(*_inits.back().get());

		return initer;
	}

	ConstColorInit&
	EmitterInitiator::addInit( MP::Class<ConstColorInit> , float p_r, float p_g, float p_b, float p_a )
	{
		std::cout << " Color \n";

		_inits.push_back(std::make_unique<ConstColorInit>( p_r, p_g, p_b, p_a ));

		auto& initer = static_cast<ConstColorInit&>(*_inits.back().get());

		return initer;
	}

	ConstSpeedInit&
	EmitterInitiator::addInit( MP::Class<ConstSpeedInit> , float p_speedX, float p_speedY, float p_speedZ )
	{
		std::cout << " Speed \n";

		_inits.push_back(std::make_unique<ConstSpeedInit>( p_speedX, p_speedY, p_speedZ ));
	
		auto& initer = static_cast<ConstSpeedInit&>(*_inits.back().get());
	
		return initer;
	}

	ConstLifeInit&
	EmitterInitiator::addInit( MP::Class<ConstLifeInit> , float p_life )
	{
		std::cout << " Life \n";

		_inits.push_back(std::make_unique<ConstLifeInit>( p_life ));
	
		auto& initer = static_cast<ConstLifeInit&>(*_inits.back().get());

		return initer;
	}

}