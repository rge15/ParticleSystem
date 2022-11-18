#pragma once
#include <chrono>

struct DemoTimer
{
	public:
		using clock = std::chrono::steady_clock;
		using timePoint = std::chrono::time_point<clock>;

		timePoint _initTime = clock::now();

		int _totalFXTime { 0 };

		//TODO : Alomejor el framerate dependeria del buffer y no del engine(Timer)
		int _frameRate { 60 };
		double _refreshTime { 1.f / _frameRate };

		double _lastTime { 0.f };

	public:
		/**	@brief Constructor for class DemoTimer */
		explicit
		DemoTimer( int p_frameRate ) noexcept;

		/**	@brief Default destructor for class DemoTimer	*/
		~DemoTimer() = default;

		/**
		 * 	@brief Gives the total ellapsed time in nanoseconds
		 * 
		 * 	@return Nanoseconds ellapsed from the init/reset of the timer
		*/
		double
		ellapsedTime() const noexcept;

		/**
		 * 	@brief Gives the total ellapsed time in seconds
		 * 
		 * 	@return Seconds ellapsed from the init/reset of the timer
		*/
		double
		ellapsedSeconds() const noexcept;

		/**
		 * 	@brief Gives the ellapsed time in seconds from the last rendered frame
		 * 
		 * 	@return Delta time since the last rendered frame
		*/
		double
		deltaTime() noexcept;
	
		/**
		 * 	@brief Check if it has to render a frame
		 * 
		 * 	@return True if it passed the _refreshTime
		*/
		bool
		updateDraw() noexcept;

		/**
		 * 	@brief Resets the timer ans sets a new framerate if wanted
		 * 
		 * 	@param p_framerate New framerate if wanted to be set. If 0 doesn't update.
		*/
		void
		reset( int p_frameRate = 0 ) noexcept;
};