#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include "glad/glad.h"
#include "Utils/Math.h"
#include "Utils/Log.h"

namespace Cobalt
{
	class Shader
	{
	public:
		Shader(const char* vertPath, const char* fragPath);

		unsigned int ID;

		void Use();

		void SetBool(const char* name, bool value) const;
		void SetInt(const char* name, int value) const;
		void SetFloat(const char* name, float value) const;
		void SetVec2(const char* name, float x, float y) const;
		void SetVec2(const char* name, glm::vec2 value) const;
		void SetVec3(const char* name, float x, float y, float z) const;
		void SetVec3(const char* name, glm::vec3 value) const;
		void SetVec4(const char* name, float x, float y, float z, float w) const;
		void SetVec4(const char* name, glm::vec4 value) const;
		void SetMat2(const char* name, glm::mat2 value) const;
		void SetMat3(const char* name, glm::mat3 value) const;
		void SetMat4(const char* name, glm::mat4 value) const;

	private:
		mutable std::unordered_map<const char*, GLint> m_UniformLocations;
		GLint GetUniformLocation(const char* name) const;
	};
}