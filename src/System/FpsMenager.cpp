#include "System/FpsMenager.hpp"
#include <windows.h>

namespace hlvl
{
namespace fps_menager
{

	void FpsMenager::setFps(unsigned fps)
	{
		this->fps = fps;
	}
	unsigned FpsMenager::getFps()
	{
		return fps;
	}

	float FpsMenager::getDelta()
	{
		return (float)delta_counter.update() / 1000.f;
	}

	void FpsMenager::beginOfRendering()
	{
		drawing_time_counter.update();
	}
	void FpsMenager::endOfRendering()
	{
		float frame_time = 1.f / (float)fps;
		// maybe 0.01 sec
		float drawing_time = (float)drawing_time_counter.update() / 1000.f;

		if (drawing_time <= frame_time)
		{
			Sleep(int((frame_time - drawing_time) * 1000.f));

			// 16.666 - 16 = 0.666
			/*
			remainder += (frame_time * 1000.f) - (int)(frame_time * 1000.f);
			if (frame_time > 1.f)
			{
				frame_time -= 1.f;
				Sleep(1);
			}/**/
		}
	}

}
}