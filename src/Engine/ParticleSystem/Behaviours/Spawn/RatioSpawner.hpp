#pragma once
#include "BaseSpawner.hpp"
#include <Engine/utils/Timer.hpp>

namespace ParticleSystem
{
	class RatioSpawner : public BaseSpawner
	{
	private:

		float _secondsSpawnRate {1.f};

		Timer _ratioSpawnerTimer {};

		int _spawnParticlesNum { 5 };

	public:
		RatioSpawner( int p_spawnParticles = 5, float p_spawnRateSeconds = 1.f ) noexcept;
		~RatioSpawner() = default;

		void
		spawn( ParticleSlotmap& p_particles, Vector<uniqPtr<BaseInit>>& p_initBehaviour ) noexcept override;
	};	
}