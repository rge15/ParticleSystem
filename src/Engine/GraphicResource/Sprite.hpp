#pragma once
#include "BaseResource.hpp"
#include <utilities/alias.hpp>
#include <picopng.hpp>
#include <fstream>
#include <cstring>
#include <utilities/DemoMath.hpp>
#include <utilities/asserts.hpp>

namespace Graphics
{
	class Sprite : BaseResource
	{

	public:
		//Data of the sprite
		Vector<uint32_t> _data {};

		// Size of the sprite
		int32_t _width{ 0 }, _height{ 0 };
		int32_t _allignedWidth{ 0 };

	public:

		/**
		 * 	@brief Cosntructor of the class Sprite
		 * 
		 * 	@param p_fileSrc String with the path of the Image
		*/
		Sprite( std::string p_fileSrc ) noexcept;

		/** @brief Destructor of the Sprite class */
		~Sprite() = default;

		/**
		 * 	@brief Method tha fills the sprite data
		 * 
		 * 	@param p_spriteData Ifstream reference with ths sprite file opened
		*/
		void
		fillSpriteData(std::ifstream& p_spriteData) noexcept;

		/**
		 * 	@brief Draws the sprite on the specified buffer
		 * 
		 * 	@param p_buffer Pointer to the start of the buffer
		*/
		void
		Draw( uint32_t* p_buffer, uint32_t p_width, uint32_t p_height ) const noexcept override;

	};
}