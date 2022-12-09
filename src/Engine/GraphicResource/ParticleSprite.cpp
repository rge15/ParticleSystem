#include "ParticleSprite.hpp"

namespace Graphics
{
	ParticleSprite::ParticleSprite( std::string p_fileSrc )
	: Sprite { p_fileSrc }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ParticleSprite::drawParticle(
		uint32_t* p_buffer, const Position& p_emitterPos ,const Position& p_particlePos, const Color& p_particleColor
	) const noexcept
	{
		int iStart, jStart, iEnd{ _height }, jEnd{ _width };
		int i, j;
		int finalX, finalY;

		int _posX = p_emitterPos.x + p_particlePos.x;
		int _posY = p_emitterPos.y + p_particlePos.y;

		finalX = DemoMath::max<int>( _posX, 0 );
		finalY = DemoMath::max<int>( _posY, 0 );

		jStart = abs(DemoMath::min<int>( _posX, 0 ));
		iStart = abs(DemoMath::min<int>( _posY, 0 ));

		if( finalX + _width > Demoengine::Config::_widthScr )
			jEnd = Demoengine::Config::_widthScr - finalX;

		if( finalY + _height > Demoengine::Config::_heightScr )
			iEnd = Demoengine::Config::_heightScr - finalY;

		for( i = iStart ; i < iEnd ; i++)
			for( j = jStart ; j< jEnd ; j++)
			{
				Color pColor = p_particleColor;
				//TODO : Aquí pillar el {_data[i * _width + j]} y procesarlo con el color de la particula

				uint32_t particleSprite = _data[i * _width + j];
				uint8_t srcA, srcR, srcG, srcB;
				srcB = particleSprite;
				particleSprite >>= 8;
				srcG = particleSprite;
				particleSprite >>= 8;
				srcR = particleSprite;
				particleSprite >>= 8;
				srcA = particleSprite;

				uint32_t particleColor = pColor._color;
				uint8_t A, R, G, B;
				B = particleColor;
				particleColor >>= 8;
				G = particleColor;
				particleColor >>= 8;
				R = particleColor;
				particleColor >>= 8;
				A = particleColor;

				
				//NEW ALPHA
				srcA = uint16_t(srcA * A) >> 8;
				//NEW COLOR
				srcR = uint16_t(srcR * R) >> 8;
				srcG = uint16_t(srcG * G) >> 8;
				srcB = uint16_t(srcB * B) >> 8;

				srcR = uint16_t(srcR * srcA) >> 8;
				srcG = uint16_t(srcG * srcA) >> 8;
				srcB = uint16_t(srcB * srcA) >> 8;

				//TODO : Tambien pillar le valor de p_buffer y hacer el alphaBlend con el valor calculado arriba
				uint32_t* pScreen = &p_buffer[ (finalY + i - iStart) * Demoengine::Config::_widthScr + (finalX + j - jStart) ];
				uint32_t valScreen = *pScreen;
				uint8_t dstA, dstR, dstG, dstB;

				dstB = valScreen;
				valScreen >>= 8;
				dstG = valScreen;
				valScreen >>= 8;
				dstR = valScreen;

				dstA = uint8_t(srcA^0XFF);
				
				dstR = uint16_t(dstR * dstA) >> 8;
				dstG = uint16_t(dstG * dstA) >> 8;
				dstB = uint16_t(dstB * dstA) >> 8;

				srcR += dstR;
				if(srcR < dstR)
					srcR = 255;

				srcG += dstG;
				if(srcG < dstG)
					srcG = 255;
				
				srcB += dstB;
				if(srcB < dstB)
					srcB = 255;
				
				uint32_t finalCol = srcA;
				finalCol <<= 8;
				finalCol |= srcR;
				finalCol <<= 8;
				finalCol |= srcG;
				finalCol <<= 8;
				finalCol |= srcB;

				*pScreen = finalCol; 
			}
		//Lógica de dibujado con el blendeo de sprites
	}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	//TODO : En la primera iteración del dibujado vamos a supones que se dibuja siempre de forma alineada
	void
	ParticleSprite::drawParticleSSE(
		uint32_t* p_buffer, const Position& p_emitterPos ,const Position& p_particlePos, const Color& p_particleColor
	) const noexcept
	{
		int iStart, jStart, iEnd{ _height }, jEnd{ _width };
		int i, j;
		int finalX, finalY;

		int _posX = p_emitterPos.x + p_particlePos.x;
		int _posY = p_emitterPos.y + p_particlePos.y;

		finalX = DemoMath::max<int>( _posX, 0 );
		finalY = DemoMath::max<int>( _posY, 0 );

		jStart = abs(DemoMath::min<int>( _posX, 0 ));
		iStart = abs(DemoMath::min<int>( _posY, 0 ));

		if( finalX + _width > Demoengine::Config::_widthScr )
			jEnd = Demoengine::Config::_widthScr - finalX;

		if( finalY + _height > Demoengine::Config::_heightScr )
			iEnd = Demoengine::Config::_heightScr - finalY;

		// for( i = iStart ; i < iEnd ; i++)
		// 	for( j = jStart ; j< jEnd ; j++)
		// 	{
		// 		Color pColor = p_particleColor;
		// 		//TODO : Aquí pillar el {_data[i * _width + j]} y procesarlo con el color de la particula

		// 		uint32_t particleSprite = _data[i * _width + j];
		// 		uint8_t srcA, srcR, srcG, srcB;
		// 		srcB = particleSprite;
		// 		particleSprite >>= 8;
		// 		srcG = particleSprite;
		// 		particleSprite >>= 8;
		// 		srcR = particleSprite;
		// 		particleSprite >>= 8;
		// 		srcA = particleSprite;
				
		// 		//NEW ALPHA
		// 		srcA = uint16_t(srcA * pColor.A) >> 8;
		// 		//NEW COLOR
		// 		srcR = uint16_t(srcR * pColor.R) >> 8;
		// 		srcG = uint16_t(srcG * pColor.G) >> 8;
		// 		srcB = uint16_t(srcB * pColor.B) >> 8;

		// 		srcR = uint16_t(srcR * srcA) >> 8;
		// 		srcG = uint16_t(srcG * srcA) >> 8;
		// 		srcB = uint16_t(srcB * srcA) >> 8;

		// 		//TODO : Tambien pillar le valor de p_buffer y hacer el alphaBlend con el valor calculado arriba
		// 		uint32_t* pScreen = &p_buffer[ (finalY + i - iStart) * Demoengine::Config::_widthScr + (finalX + j - jStart) ];
		// 		uint32_t valScreen = *pScreen;
		// 		uint8_t dstA, dstR, dstG, dstB;

		// 		dstB = valScreen;
		// 		valScreen >>= 8;
		// 		dstG = valScreen;
		// 		valScreen >>= 8;
		// 		dstR = valScreen;

		// 		dstA = uint8_t(srcA^0XFF);
				
		// 		dstR = uint16_t(dstR * dstA) >> 8;
		// 		dstG = uint16_t(dstG * dstA) >> 8;
		// 		dstB = uint16_t(dstB * dstA) >> 8;

		// 		srcR += dstR;
		// 		if(srcR < dstR)
		// 			srcR = 255;

		// 		srcG += dstG;
		// 		if(srcG < dstG)
		// 			srcG = 255;
				
		// 		srcB += dstB;
		// 		if(srcB < dstB)
		// 			srcB = 255;
				
		// 		uint32_t finalCol = srcA;
		// 		finalCol <<= 8;
		// 		finalCol |= srcR;
		// 		finalCol <<= 8;
		// 		finalCol |= srcG;
		// 		finalCol <<= 8;
		// 		finalCol |= srcB;

		// 		*pScreen = finalCol; 
		// 	}
		//Lógica de dibujado con el blendeo de sprites

		__m128i zero = _mm_setzero_si128();
		__m128i srcColor = _mm_set1_epi32( p_particleColor._color );
		srcColor = _mm_unpacklo_epi8( srcColor, zero );

		__m128i alphaMask = _mm_set_epi32( 0x00FF0000, 0x00000000, 0x00FF0000, 0x00000000 );

		__m128i* buffStart { nullptr };

		for( i = 0 ; i < _height ; i++)
		{
			buffStart = reinterpret_cast<__m128i*>( &p_buffer[i*Demoengine::Config::_widthScr]);

			for(const __m128i* jStart = reinterpret_cast<const __m128i*>( &_data.data()[i * _width] ),
				*jEnd = reinterpret_cast<const __m128i*>( &_data.data()[i * _width + _width - 1] ); 
				jStart < jEnd; jStart++, buffStart++ )
			{
				//Particle Color
				__m128i sprColorHi = _mm_unpackhi_epi8( *jStart, zero );
				__m128i sprColorLo = _mm_unpacklo_epi8( *jStart, zero );
			
				// 		srcA = uint16_t(srcA * pColor.A) >> 8;
				// 		srcR = uint16_t(srcR * pColor.R) >> 8;
				// 		srcG = uint16_t(srcG * pColor.G) >> 8;
				// 		srcB = uint16_t(srcB * pColor.B) >> 8;
				__m128i particleColorHi = _mm_mullo_epi16( sprColorHi, srcColor );
				__m128i particleColorLo = _mm_mullo_epi16( sprColorLo, srcColor );

				//TODO CHECK : Esto alomejor me está haciendo shift en partes que no quiero
				//? Si es el caso se soluciona con una mascara AND y quedarme las partes que me interesa
				particleColorHi = _mm_srli_epi16( particleColorHi, 8 );
				particleColorLo = _mm_srli_epi16( particleColorLo, 8 );

				const __m128i particleAlphaHiValue = _mm_and_si128( alphaMask, particleColorHi ); //(A1)(0)(0)(0)(A2)(0)(0)(0)
				const __m128i particleAlphaLoValue = _mm_and_si128( alphaMask, particleColorLo ); //(A3)(0)(0)(0)(A4)(0)(0)(0)

				__m128i particleAlphaHi = _mm_setzero_si128();
				__m128i particleAlphaLo = _mm_setzero_si128();

				for(int j = 0; j < 4; j++)
				{
					__m128i shiftedHiAlpha = _mm_srli_epi64( particleAlphaHiValue, j*16 );
					__m128i shiftedLoAlpha = _mm_srli_epi64( particleAlphaLoValue, j*16 );
				
					particleAlphaHi = _mm_or_si128( particleAlphaHi, shiftedHiAlpha );
					particleAlphaLo = _mm_or_si128( particleAlphaLo, shiftedLoAlpha );
				}

				// 		srcR = uint16_t(srcR * srcA) >> 8;
				// 		srcG = uint16_t(srcG * srcA) >> 8;
				// 		srcB = uint16_t(srcB * srcA) >> 8;
				particleColorHi = _mm_mullo_epi16( particleColorHi, particleAlphaHi );
				particleColorLo = _mm_mullo_epi16( particleColorLo, particleAlphaLo );

				particleColorHi = _mm_srli_epi16( particleColorHi, 8 );
				particleColorLo = _mm_srli_epi16( particleColorLo, 8 );

				__m128i finalParticleColor = _mm_packus_epi16( particleColorLo, particleColorHi );
				//End Calculus final Color

				//Alpha Blending
				__m128i dstAlphaHi = _mm_xor_si128( particleAlphaHi, alphaMask );
				__m128i dstAlphaLo = _mm_xor_si128( particleAlphaLo, alphaMask );

				const __m128i dstOriginalVal = _mm_loadu_si128( buffStart );

				__m128i dstColorHi = _mm_unpackhi_epi8( dstOriginalVal, zero );
				__m128i dstColorLo = _mm_unpacklo_epi8( dstOriginalVal, zero );

				dstColorHi = _mm_mullo_epi16( dstColorHi, dstAlphaHi );
				dstColorLo = _mm_mullo_epi16( dstColorLo, dstAlphaLo );

				dstColorHi = _mm_srli_epi16( dstColorHi, 8 );
				dstColorLo = _mm_srli_epi16( dstColorLo, 8 );

				__m128i dstColor = _mm_packus_epi16( dstColorLo, dstColorHi );

				finalParticleColor = _mm_adds_epu8( finalParticleColor, dstColor );
				//End Alpha blending

				_mm_storeu_si128( buffStart, finalParticleColor );
			}
		}



	}



}