#pragma once
#include <utilities/chronoTypeAlias.hpp>
#include <Engine/DataTypes/Position.hpp>
#include <Engine/DataTypes/Color.hpp>

namespace ParticleSystem
{

	class Particle
	{
		public:
			Particle(/* args */) = default;
			~Particle() = default;
	
			timePoint _initLife = demoClock::now();
			float _totalLifeTime{ 0.f };
			
			float _currNormalizedLifeTime{ 0.f };
			float _currLifeTime{ 0.f };
	
			Position _pos {};
			float _velX{ 0.f }, _velY{ 0.f };
	
			Color _color { 0xFF, 0xFF, 0xFF, 0xFF };
			//TODO : Debería hacer un setColor, q reciba 4 floats y los pase de 0 a 255 en un uint8_t para cada canal 

	};

}