#pragma once

namespace hlvl
{
	/*just write in start of main function:
	GLFW just_glfw;
	if (!just_glfw.init())
		//error code
	*/
	class GLFW sealed
	{
	public:
		GLFW();
		bool init();
		~GLFW();
	};
}