#pragma once

#include "System/Clock.hpp"

namespace hlvl
{
namespace fps_menager
{

	class FpsMenager
	{
		using Clock = clock::Clock;

		Clock delta_counter;
		Clock drawing_time_counter;

		unsigned fps = 0;

		//float remainder = 0.f;
	public:
		void setFps(unsigned fps);
		unsigned getFps();

		// returns how much time has passed since the last mathod call (in seconds)
		float getDelta();

		// call this method to indicate the start of rendering
		void beginOfRendering();
		/*
		Call this method to indicate the end of rendering.
		The method will wait for the rest of the frame if need
		*/
		void endOfRendering();
	};

}
}