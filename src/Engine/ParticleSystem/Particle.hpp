#pragma once
#include <utilities/chronoTypeAlias.hpp>

namespace ParticleSystem
{

	class Particle
	{
	public:
		Particle(/* args */) = default;
		~Particle() = default;

		timePoint _initLife = demoClock::now();
		float _lifeTime{ 0.f };
		float _posX{ 0.f }, _posY{ 0.f }, _posZ{ 0.f };
		float _velX{ 0.f }, _velY{ 0.f }, _velZ{ 0.f };

		//TODO : Debería hacer un setColor, q reciba 4 floats y los pase de 0 a 255 en un uint8_t para cada canal 
		float _A, _R, _G, _B;
	};

}