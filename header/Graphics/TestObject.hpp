#pragma once

#include "Graphics/Buffer.hpp"
#include "Graphics/Transformable.hpp"

namespace my
{
	using namespace hlvl::buffer;
	using namespace hlvl::vector;

	class TestObject : public hlvl::transform::Transformable
	{
	public:
		VertexBuffer v_buffer{0};
		ColorBuffer3f c_buffer{1};

		void setVertexBuffer(const std::vector<Point2D>& v)
		{
			v_buffer.add(v);
		}
		void setColorBuffer(const std::vector<Color3f>& v)
		{
			c_buffer.add(v);
		}
	};
}