#pragma once

#include <utilities/alias.hpp>
#include <Engine/utils/Timer.hpp>
#include <Engine/DrawerSrc.hpp>

class Drawer
{
	private:
		DemoTimer	_timer { 60 };
		uint32_t&	_buffer;

		void
		updateDraw() noexcept;

	public:
		uniqPtr<DrawerSrc> _src = std::make_unique<DrawerSrc>();

		/**	@brief Constructor of Drawer class
		 * 
		 * 	@param p_buffer Pointer to the start of the buffer to draw in
		 */
		Drawer( uint32_t* p_buffer );

		/**	@brief Default destructor for Drawe class */
		~Drawer() = default;

		/**
		 * 	@brief It draws all the FXs on _FXs
		*/
		void
		Draw() noexcept;
};