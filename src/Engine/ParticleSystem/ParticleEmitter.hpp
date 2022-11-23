#pragma once
#include <Engine/GraphicResource/BaseResource.hpp>
#include <Engine/ParticleSystem/Behaviours/EmitterInitiator.hpp>

namespace ParticleSystem
{
	class Emitter
	{
	private:
		Graphics::BaseResource* _resource { nullptr };
	
		//TODO : Estructurar el particle Emmiter en Initer y Updater, y llevarse los tagDispatching y las cosas a los respectivos
		EmitterInitiator _initiator;
		// EmmiterUpdater _updater;
		// Vector<uniqPtr<BaseUpdater>> _inits;

		Vector<Particle> _particles;

	public:
	
		Emitter() = default;
	
		~Emitter() = default;

		void
		setResource( Graphics::BaseResource& p_resource ) noexcept;

		void
		update() noexcept;
	
		template<initerBehaviour T, typename... args>
		T&
		addEmmiterInit(args&&... p_params);

	};

}

#include "ParticleEmitter.tpp"