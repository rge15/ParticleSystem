#pragma once
#include <Engine/GraphicResource/ParticleSprite.hpp>
#include <Engine/ParticleSystem/Behaviours/EmitterInitiator.hpp>
#include <Engine/ParticleSystem/Behaviours/EmitterSpawner.hpp>
#include <Engine/ParticleSystem/Behaviours/EmitterUpdater.hpp>

#include <Engine/DataTypes/Position.hpp>
namespace ParticleSystem
{
	class Emitter
	{
	private:
		Graphics::ParticleSprite* _resource { nullptr };

		Position _pos {};

		EmitterSpawner _spawner;
		EmitterInitiator _initiator;
		EmitterUpdater _updater;

		Vector<Particle> _particles;

	public:
	
		Emitter() = default;
	
		~Emitter() = default;

		void
		setResource( Graphics::ParticleSprite& p_resource ) noexcept;

		void
		update( uint32_t* const p_buffer ) noexcept;

		template<initerBehaviour T, typename... args>
		T&
		addEmitterInit(args&&... p_params);

		template<updateBehaviour T, typename... args>
		T&
		addEmitterUpdate(args&&... p_params);

		template<spawnBehaviour T, typename... args>
		T&
		addEmitterSpawn(args&&... p_params);

	};

}

#include "ParticleEmitter.tpp"