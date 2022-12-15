#include "Sprite.hpp"

namespace Graphics
{

	Sprite::Sprite( std::string p_fileSrc ) noexcept
	{
		std::ifstream file ( p_fileSrc, std::ios::binary);

		ASSERT(file.is_open(), "Error opening the img for the sprite")

		fillSpriteData( file );

		file.close();
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	Sprite::fillSpriteData( std::ifstream& p_spriteData ) noexcept
	{
		std::vector<unsigned char> pixels {};
		unsigned long width {0}, height {0};

		std::vector<unsigned char> fileData{
			std::istreambuf_iterator<char> {p_spriteData},
			std::istreambuf_iterator<char> {}
		};

		decodePNG( pixels, width, height, fileData.data(), fileData.size());

		ASSERT( (width<=UINT32_MAX) , "Width of png greater than posible")
		ASSERT( (height<=UINT32_MAX) , "Height of png greater than posible")

		_width = width;
		_height = height;
		_allignedWidth = (_width + 3) & ~0x03;

		//TODO : Aquñi tendré que hacer calculos para que cada fila esté alineada a 16 bytes
		//TODO : Y volver a guardar los datos con 2 for's
		//TODO : Tener una variable miembro que sea _allignedWidth que tenga el width real en los datos pero no en el sprite

		auto iterValuesCopy = pixels.size()/_height;

		_data.resize( _height * _allignedWidth );
		for(int i = 0; i < _height; i++)
			memcpy( &_data.data()[i * _allignedWidth], &pixels.data()[i*iterValuesCopy], iterValuesCopy );

		uint8_t r,g,b;
		uint32_t value;

		for( uint32_t i = 0 ; i < _data.size(); i++)
		{
			value = _data[i]; 
			r = value;
			value >>= 8;
			g = value;
			value >>= 8;
			b = value;
			value >>= 8;
			value <<= 8;
			value |= r;
			value <<= 8;
			value |= g;
			value <<= 8;
			value |= b;
			_data[i] = value;
		}
	
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	Sprite::Draw( uint32_t* p_buffer, uint32_t p_width, uint32_t p_height  ) const noexcept
	{
		int iStart, jStart, iEnd{ _height }, jEnd{ _width };
		int i, j;
		int finalX, finalY;

		//Aquí irá la posición de la partícula
		int _posX, _posY;

		finalX = DemoMath::max<int>( _posX, 0 );
		finalY = DemoMath::max<int>( _posY, 0 );

		jStart = abs(DemoMath::min<int>( _posX, 0 ));
		iStart = abs(DemoMath::min<int>( _posY, 0 ));

		if( finalX + _width > p_width )
			jEnd = p_width - finalX;

		if( finalY + _height > p_height )
			iEnd = p_height - finalY;

		for( i = iStart ; i < iEnd ; i++)
			for( j = jStart ; j< jEnd ; j++)
				p_buffer[ (finalY + i - iStart) * p_width + (finalX + j - jStart) ] = _data[ i * _width + j];
	}





}