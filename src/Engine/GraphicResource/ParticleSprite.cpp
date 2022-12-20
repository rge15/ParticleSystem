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

	void
	ParticleSprite::drawPixel( uint32_t& p_buffer, uint32_t p_particleColor, uint32_t particlePixel ) const noexcept
	{
		uint8_t srcA, srcR, srcG, srcB;
		srcB = particlePixel;
		particlePixel >>= 8;
		srcG = particlePixel;
		particlePixel >>= 8;
		srcR = particlePixel;
		particlePixel >>= 8;
		srcA = particlePixel;
		
		uint8_t A, R, G, B;
		B = p_particleColor;
		p_particleColor >>= 8;
		G = p_particleColor;
		p_particleColor >>= 8;
		R = p_particleColor;
		p_particleColor >>= 8;
		A = p_particleColor;

		//NEW ALPHA
		srcA = uint16_t(srcA * A) >> 8;
		//NEW COLOR
		srcR = uint16_t(srcR * R) >> 8;
		srcG = uint16_t(srcG * G) >> 8;
		srcB = uint16_t(srcB * B) >> 8;

		srcR = uint16_t(srcR * srcA) >> 8;
		srcG = uint16_t(srcG * srcA) >> 8;
		srcB = uint16_t(srcB * srcA) >> 8;

		uint32_t valScreen = p_buffer;
		
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

		p_buffer = finalCol;
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ParticleSprite::drawParticleSSE(
		uint32_t* p_buffer, const Position& p_emitterPos ,const Position& p_particlePos, const Color& p_particleColor
	) const noexcept
	{
		int iStart, jStart, iEnd{ _height }, jEnd{ _allignedWidth };
		int finalX, finalY;

		int _posX = (int)p_emitterPos.x + (int)p_particlePos.x;
		int _posY = (int)p_emitterPos.y + (int)p_particlePos.y;

		finalX = DemoMath::max<int>( _posX, 0 );
		finalY = DemoMath::max<int>( _posY, 0 );

		jStart = abs(DemoMath::min<int>( _posX, 0 ));
		iStart = abs(DemoMath::min<int>( _posY, 0 ));

		if( finalX + _width > Demoengine::Config::_widthScr )
			jEnd = Demoengine::Config::_widthScr - finalX;

		if( finalY + _height > Demoengine::Config::_heightScr )
			iEnd = Demoengine::Config::_heightScr - finalY;


		if( (jEnd-jStart) < 4 )
		{
			drawParticleNormally( iStart, iEnd, jStart, jEnd, finalX, finalY, p_buffer, p_particleColor._color );
			return;
		}

		auto srcAllignment = jStart & 0x03;
		auto dstAllignment = finalX & 0x03;

		if( srcAllignment == dstAllignment )
		{
			drawParticleWithSrcDstAlligned( iStart, iEnd, jStart, jEnd, finalX, finalY, p_buffer, p_particleColor._color );
			return;	
		}

		drawParticlesWithSrcPeeling( iStart, iEnd, jStart, jEnd, finalX, finalY, p_buffer, p_particleColor._color );

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ParticleSprite::drawParticleNormally(
		const int p_iStart, const int p_iEnd, const int p_jStart, const int p_jEnd,
		const int p_finalX, const int p_finalY,
		uint32_t* p_buffer, uint32_t p_particleColor
	) const noexcept
	{
		for(int i = p_iStart ; i < p_iEnd ; i++)
			drawNormalPixelsInRange( p_jStart, p_jEnd, p_iStart, p_finalX, p_finalY, p_buffer, p_particleColor, i );
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ParticleSprite::drawParticleWithSrcDstAlligned( 
		const int p_iStart, const int p_iEnd, const int p_jStart, const int p_jEnd,
		const int p_finalX, const int p_finalY,
		uint32_t* p_buffer, uint32_t p_particleColor
	) const noexcept
	{
		int initPositionNonAlignedDiff = p_jStart & 0x03; // jStart % 4;
		int prePeelLoopIter = initPositionNonAlignedDiff ? 4 - initPositionNonAlignedDiff : 0 ; //Num of pixels to prePeelDraw
		int prePeelFinalPixel = p_jStart + prePeelLoopIter;
		int srcSSEStartPoint = (p_jStart + 3) & ~0x03;

		int pixelsToDraw = p_jEnd - p_jStart;

		int postPeelLoopIter = (p_finalX + pixelsToDraw) & 0x03; //Num of pixels to postPeelDraw
		int postPeelStartPixel = p_jEnd - postPeelLoopIter;

		int pixelsInnerPeels = ((p_finalX + pixelsToDraw) - postPeelLoopIter) - (p_finalX + prePeelLoopIter);
		int SSELoopIterations = pixelsInnerPeels >> 2;

		for(int i = p_iStart ; i < p_iEnd ; i++)
		{
			//?PrePeel pixels draws
			drawNormalPixelsInRange( p_jStart, prePeelFinalPixel, p_iStart, p_finalX, p_finalY, p_buffer, p_particleColor, i );

			//?Inner SSE pixel draws
			drawInnerSSEPixelsAlligned( p_iStart, p_finalX, p_finalY, p_buffer, p_particleColor, prePeelLoopIter, i, SSELoopIterations, srcSSEStartPoint );

			//?PostPeel pixel draws
			drawNormalPixelsInRange( postPeelStartPixel, p_jEnd, p_iStart, p_finalX, p_finalY, p_buffer, p_particleColor, i );

		}
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ParticleSprite::drawAndStoreSSEPixel( const __m128i* p_src, __m128i* p_dst, const uint32_t color ) const noexcept
	{
		__m128i finalPixelValue = drawSSEPixel( *p_src, *p_dst, color );

		_mm_store_si128( p_dst, finalPixelValue );
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ParticleSprite::drawParticlesWithSrcPeeling(
		const int p_iStart, const int p_iEnd, const int p_jStart, const int p_jEnd,
		const int p_finalX, const int p_finalY,
		uint32_t* p_buffer, uint32_t p_particleColor
	) const noexcept
	{
		auto prePeelDraws = 4 - (p_jStart & 0x03);
		auto dstShiftStep = (p_finalX + prePeelDraws) & 0x03;

		switch (dstShiftStep)
		{
			case 0:
				drawParticleWithSrcDstAlligned(p_iStart, p_iEnd, p_jStart, p_jEnd, p_finalX, p_finalY, p_buffer, p_particleColor);
				break;

			case 1:
				drawWithSrcPeeling<1>(p_iStart, p_iEnd, p_jStart, p_jEnd, p_finalX, p_finalY, p_buffer, p_particleColor);
				break;

			case 2:
				drawWithSrcPeeling<2>(p_iStart, p_iEnd, p_jStart, p_jEnd, p_finalX, p_finalY, p_buffer, p_particleColor);
				break;

			case 3:
				drawWithSrcPeeling<3>(p_iStart, p_iEnd, p_jStart, p_jEnd, p_finalX, p_finalY, p_buffer, p_particleColor);
				break;

			default:
				std::cout << "Some kind of error at DrawPArticlesWithSRCAlligned \n"; 
				break;
		}

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	__m128i
	ParticleSprite::drawSSEPixel( const __m128i& p_src, __m128i& p_dst, const uint32_t color ) const noexcept
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i alphaMask = _mm_set_epi32( 0x00FF0000, 0x00000000, 0x00FF0000, 0x00000000 );
		const __m128i dstAlphaMask = _mm_set_epi32( 0x00FF00FF, 0x00FF00FF, 0x00FF00FF, 0x00FF00FF );

		__m128i srcColor = _mm_set1_epi32( color );
		srcColor = _mm_unpacklo_epi8( srcColor, zero );

		//Particle Color
		__m128i sprColorHi = _mm_unpackhi_epi8( p_src, zero );
		__m128i sprColorLo = _mm_unpacklo_epi8( p_src, zero );

		// 		srcA = uint16_t(srcA * pColor.A) >> 8;
		// 		srcR = uint16_t(srcR * pColor.R) >> 8;
		// 		srcG = uint16_t(srcG * pColor.G) >> 8;
		// 		srcB = uint16_t(srcB * pColor.B) >> 8;
		__m128i particleColorHi = _mm_mullo_epi16( sprColorHi, srcColor );
		__m128i particleColorLo = _mm_mullo_epi16( sprColorLo, srcColor );

		particleColorHi = _mm_srli_epi16( particleColorHi, 8 );
		particleColorLo = _mm_srli_epi16( particleColorLo, 8 );

		const __m128i particleAlphaHiValue = _mm_and_si128( alphaMask, particleColorHi ); //(A1)(0)(0)(0)(A2)(0)(0)(0)
		const __m128i particleAlphaLoValue = _mm_and_si128( alphaMask, particleColorLo ); //(A3)(0)(0)(0)(A4)(0)(0)(0)

		__m128i particleAlphaHi = _mm_setzero_si128();
		__m128i particleAlphaLo = _mm_setzero_si128();

		for(int y = 0; y < 4; y++)
		{
			__m128i shiftedHiAlpha = _mm_srli_epi64( particleAlphaHiValue, y*16 );
			__m128i shiftedLoAlpha = _mm_srli_epi64( particleAlphaLoValue, y*16 );
		
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
		__m128i dstAlphaHi = _mm_xor_si128( particleAlphaHi, dstAlphaMask );
		__m128i dstAlphaLo = _mm_xor_si128( particleAlphaLo, dstAlphaMask );

		const __m128i dstOriginalVal = _mm_load_si128( &p_dst );

		__m128i dstColorHi = _mm_unpackhi_epi8( dstOriginalVal, zero );
		__m128i dstColorLo = _mm_unpacklo_epi8( dstOriginalVal, zero );

		dstColorHi = _mm_mullo_epi16( dstColorHi, dstAlphaHi );
		dstColorLo = _mm_mullo_epi16( dstColorLo, dstAlphaLo );

		dstColorHi = _mm_srli_epi16( dstColorHi, 8 );
		dstColorLo = _mm_srli_epi16( dstColorLo, 8 );

		__m128i dstColor = _mm_packus_epi16( dstColorLo, dstColorHi );

		finalParticleColor = _mm_adds_epu8( finalParticleColor, dstColor );
		//End Alpha blending

		return finalParticleColor;
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	template<int N>
	void
	ParticleSprite::drawWithSrcPeeling(
		const int p_iStart, const int p_iEnd, const int p_jStart, const int p_jEnd,
		const int p_finalX, const int p_finalY,
		uint32_t* p_buffer, uint32_t p_particleColor
	) const noexcept
	{
		auto initPositionNonAlignedDiff = 4 - (p_jStart & 0x03);
		auto prePeelIterations = initPositionNonAlignedDiff ? 4 - initPositionNonAlignedDiff : 0 ;
		auto prePeelFinalPixel = p_jStart + prePeelIterations;
		auto jStartWithPrePeel = (p_jStart + 3) & ~0x03;

		auto pixelsToDraw = p_jEnd - jStartWithPrePeel;
		auto pixelsToSSEDraw = pixelsToDraw & ~0x03;
		auto postPeelLoop = pixelsToDraw - pixelsToSSEDraw;
		auto postPeelFinalPixel = pixelsToSSEDraw + postPeelLoop;

		auto dstAllignedPos = p_finalX & ~0x03;
		auto nextFinalDstAllignedPos = (p_finalX + pixelsToSSEDraw) & ~0x03;

		for( int i = p_iStart; i < p_iEnd; i++ )
		{
			//? PostPeel pixels draw
			drawNormalPixelsInRange( p_jStart, prePeelFinalPixel, p_iStart, p_finalX, p_finalY, p_buffer, p_particleColor, i );

			//? Inner SSE Splited Pixels
			drawInnerSSEPixelsSplited<N>( p_iStart, p_finalY, p_buffer, p_particleColor, i, dstAllignedPos, jStartWithPrePeel, nextFinalDstAllignedPos );

			//? PostPeel pixels draw
			drawNormalPixelsInRange( pixelsToSSEDraw, postPeelFinalPixel, p_iStart, p_finalX, p_finalY, p_buffer, p_particleColor, i );
		}
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ParticleSprite::drawNormalPixelsInRange(
		const int p_start, const int p_end,
		const int p_iStart,
		const int p_finalX, const int p_finalY,
		uint32_t* p_buffer, uint32_t p_particleColor,
		const int p_row
	) const noexcept
	{
		for(int j = p_start; j < p_end; j++)
		{
			uint32_t& bufferPixel = p_buffer[ (p_finalY + p_row - p_iStart) * Demoengine::Config::_widthScr + (p_finalX + j - p_start) ];
			uint32_t particlePixel = _data[p_row * _allignedWidth + j];
			drawPixel( bufferPixel, p_particleColor, particlePixel );
		}
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ParticleSprite::drawInnerSSEPixelsAlligned(
		const int p_iStart,
		const int p_finalX, const int p_finalY,
		uint32_t* p_buffer, uint32_t p_particleColor,
		const int p_peelIter, const int p_row,
		const int p_SEEIterations, const int p_srcSSEStartPoint
	) const noexcept
	{
		__m128i* buffStart = reinterpret_cast<__m128i*>( &p_buffer[ (p_finalY + p_row - p_iStart) * Demoengine::Config::_widthScr + (p_finalX + p_peelIter)]);
		int j = 0;

		for(const __m128i* jStart = reinterpret_cast<const __m128i*>( &_data.data()[p_row * _allignedWidth + p_srcSSEStartPoint] );
			j < p_SEEIterations; jStart++, buffStart++ )
		{
			drawAndStoreSSEPixel( jStart, buffStart, p_particleColor );
			++j;
		}
	
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	template<int N>
	void
	ParticleSprite::drawInnerSSEPixelsSplited(
		const int p_iStart, const int p_finalY,
		uint32_t* p_buffer, uint32_t p_particleColor,
		const int p_row,
		const int p_dstAlligned, const int p_srcStartPixel,
		const int p_dstFinalPos
	) const noexcept
	{
		//? First SSE dstPixels
		__m128i* dstPtr = reinterpret_cast<__m128i*>( &p_buffer[ (p_finalY + p_row - p_iStart) * Demoengine::Config::_widthScr + p_dstAlligned ] );
		const __m128i* srcNewPtr = reinterpret_cast<const __m128i*>( &_data[ p_row * _allignedWidth + p_srcStartPixel ] );

		__m128i dstFirstValue = _mm_load_si128( dstPtr );
		__m128i srcFirstValue = _mm_load_si128( srcNewPtr );

		srcFirstValue = _mm_slli_si128( srcFirstValue, (N << 2) );
		const __m128i firstPixelsColor = drawSSEPixel( srcFirstValue, dstFirstValue, p_particleColor );
		_mm_store_si128( dstPtr, firstPixelsColor );

		// Loop SSE srcPixels with dstPixels
		const __m128i* srcOldPtr = srcNewPtr;
		++dstPtr;
		++srcNewPtr;

		for(const __m128i* const lastDstPtr = reinterpret_cast<const __m128i* const>( &p_buffer[ (p_finalY + p_row - p_iStart) * Demoengine::Config::_widthScr + p_dstFinalPos ] );
			dstPtr != lastDstPtr; ++dstPtr, ++srcNewPtr, ++srcOldPtr)
		{
			__m128i srcShiftedValue = _mm_or_si128( _mm_srli_si128( *srcOldPtr, ((4-N)<<2) ), _mm_slli_si128( *srcNewPtr, (N<<2) ) );
			const __m128i firstPixelsColor = drawSSEPixel( srcShiftedValue, *dstPtr, p_particleColor );
			_mm_store_si128( dstPtr, firstPixelsColor );
		}

		// Last SSE dstPixels
		__m128i dstLastValue = _mm_load_si128( --dstPtr );
		__m128i srcLastValue = _mm_load_si128( srcOldPtr );

		srcLastValue = _mm_srli_si128( srcLastValue, (N<<2) );
		const __m128i lastPixelsColor = drawSSEPixel( srcLastValue, dstLastValue, p_particleColor );
		_mm_store_si128( dstPtr, lastPixelsColor );
	}

}