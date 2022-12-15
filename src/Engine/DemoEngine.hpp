#pragma once
#include <utilities/config.hpp>
#include <utilities/alias.hpp>
#include <Engine/DemoEngineConfig.hpp>
#include "Drawer.hpp"
#include <utilities/Benchmark/Benchmarker.hpp>


using namespace Demoengine::Config;

class DemoEngine
{
	public :
		uint32_t _buffer1[ _widthScr * _heightScr ];
		uint32_t _buffer2[ _widthScr * _heightScr ];

		uniqPtr<Benchmark::Benchmarker> bench = std::make_unique<Benchmark::Benchmarker>();

		uint32_t* _drawBuffer { _buffer1 };
		uint32_t* _readBuffer { _buffer2 };

		uniqPtr<Drawer> _drawer { std::make_unique<Drawer>() };

		Timer _timer { 60 };

	public:
		/**	@brief Opens the window to draw in */
		explicit DemoEngine() noexcept;

		/**	@brief Destroys the opened window */
		~DemoEngine() noexcept;

		/** @brief Draws all the FXs set on _drawer */
		void
		Draw() noexcept;

		/**	
		 * 	@brief Gets the reference to the engine _drawer 
		 * 
		 * 	@return Reference to _drawer
		*/
		Drawer&
		getDrawer() const noexcept
		{
			return *_drawer.get();
		}

	private:

		void
		updateBuffer() noexcept;

		void
		swapDoubleBuffer() noexcept;

};

