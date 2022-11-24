#pragma once
#include <Engine/GraphicResource/Sprite.hpp>
#include <Engine/ParticleSystem/Particle.hpp>
#include <Engine/DemoEngineConfig.hpp>
namespace Graphics
{
	class ParticleSprite : public Sprite
	{
	private:
	public:
		ParticleSprite(std::string p_fileSrc);

		~ParticleSprite() = default;
	
		void
		drawParticle(
			uint32_t* p_buffer, const Position& p_emitterPos ,const ParticleSystem::Particle& p_particle
		) const noexcept;
	
	};

}
