#pragma once
#include <Engine/GraphicResource/Sprite.hpp>
#include <Engine/ParticleSystem/Particle.hpp>
#include <Engine/DemoEngineConfig.hpp>
#include <Engine/ParticleSystem/ParticleAttributeIncludes.hpp>
#include <utilities/includeSSE.hpp>

namespace Graphics
{
	class ParticleSprite : public Sprite
	{
	private:
		void
		drawPixel( uint32_t& p_buffer, uint32_t p_particleColor, uint32_t particlePixel ) const noexcept;

		void
		drawAndStoreSSEPixel( const __m128i* p_src, __m128i* p_dst, const uint32_t color ) const noexcept;

		__m128i
		drawSSEPixel( const __m128i& p_src, __m128i& p_dst, const uint32_t color ) const noexcept;

		void
		drawParticleNormally(
			const int p_iStart, const int p_iEnd, const int p_jStart, const int p_jEnd,
			const int p_finalX, const int p_finalY,
			uint32_t* p_buffer, uint32_t p_particleColor
		) const noexcept;

		void
		drawParticleWithSrcDstAlligned( 
			const int p_iStart, const int p_iEnd, const int p_jStart, const int p_jEnd,
			const int p_finalX, const int p_finalY,
			uint32_t* p_buffer, uint32_t p_particleColor
		) const noexcept;

		void
		drawParticlesWithSrcAlligned(
			const int p_iStart, const int p_iEnd, const int p_jStart, const int p_jEnd,
			const int p_finalX, const int p_finalY,
			uint32_t* p_buffer, uint32_t p_particleColor
		) const noexcept;

		template<int N>
		void
		drawWithSrcAlligned(
			const int p_iStart, const int p_iEnd, const int p_jStart, const int p_jEnd,
			const int p_finalX, const int p_finalY,
			uint32_t* p_buffer, uint32_t p_particleColor
		) const noexcept;

	public:
		ParticleSprite(std::string p_fileSrc);

		~ParticleSprite() = default;
	
		void
		drawParticle(
			uint32_t* p_buffer, const Position& p_emitterPos ,const Position& p_particlePos, const Color& p_particleColor
		) const noexcept;
	
		void
		drawParticleSSE(
			uint32_t* p_buffer, const Position& p_emitterPos ,const Position& p_particlePos, const Color& p_particleColor
		) const noexcept;

		void
		drawParticleSSE2(
			uint32_t* p_buffer, const Position& p_emitterPos ,const Position& p_particlePos, const Color& p_particleColor
		) const noexcept;

	};

}
