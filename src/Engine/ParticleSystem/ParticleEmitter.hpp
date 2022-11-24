#pragma once
#include <Engine/GraphicResource/ParticleSprite.hpp>
#include <Engine/ParticleSystem/Behaviours/EmitterInitiator.hpp>
#include <Engine/ParticleSystem/Behaviours/EmitterSpawner.hpp>
#include <Engine/DataTypes/Position.hpp>
namespace ParticleSystem
{
	class Emitter
	{
	private:
		Graphics::ParticleSprite* _resource { nullptr };

		Position _pos {};

		EmitterSpawner _spawner;
		//TODO : Estructurar el particle Emmiter en Initer y Updater, y llevarse los tagDispatching y las cosas a los respectivos
		EmitterInitiator _initiator;
		// EmmiterUpdater _updater;
		// Vector<uniqPtr<BaseUpdater>> _inits;

		Vector<Particle> _particles;

	public:
	
		Emitter() = default;
	
		~Emitter() = default;

		void
		setResource( Graphics::ParticleSprite& p_resource ) noexcept;

		void
		update( uint32_t* p_buffer ) noexcept;
	
		template<initerBehaviour T, typename... args>
		T&
		addEmmiterInit(args&&... p_params);

		template<spawnBehaviour T, typename... args>
		T&
		addEmmiterSpawn(args&&... p_params);

	};

}

#include "ParticleEmitter.tpp"