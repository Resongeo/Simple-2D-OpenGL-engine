#pragma once

#include "glad/glad.h"
#include "stb_image.h"
#include "Utils/Log.h"

namespace Cobalt
{
	class Sprite
	{
	public:
		Sprite(const char* path);

		unsigned int textureID;
		void Bind();
	};
}