#pragma once

namespace hlvl
{
namespace clock
{


	class Clock
	{
		long time;
	public:
		Clock();
		~Clock() = default;

		// returns how many msec have passed since the last call
		long update();
	};


}
}