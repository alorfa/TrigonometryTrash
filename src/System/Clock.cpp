#include "System/Clock.hpp"
#include <ctime>

namespace hlvl
{
namespace clock
{

	Clock::Clock()
	{
		update();
	}

	long Clock::update()
	{
		long new_time = std::clock();
		auto output = new_time - time;

		time = new_time;

		return output;
	}


}
}