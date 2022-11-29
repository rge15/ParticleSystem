#pragma once
#include <utilities/chronoTypeAlias.hpp>
#include <Engine/DataTypes/Position.hpp>

namespace ParticleSystem
{

	class Particle
	{
	public:
		Particle(/* args */) = default;
		~Particle() = default;

		const timePoint _initLife = demoClock::now();
		float _totalLifeTime{ 0.f };
		float _normalizedLifeTime{ 0.f };
		float _lifeTime{ 0.f };

		Position _pos {};
		float _velX{ 0.f }, _velY{ 0.f };

		//TODO : Debería hacer un setColor, q reciba 4 floats y los pase de 0 a 255 en un uint8_t para cada canal 
		uint32_t _ARGBMask { 0xFFFFFFFF };

	};

}