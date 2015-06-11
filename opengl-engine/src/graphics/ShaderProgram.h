#pragma once

#include <vector>
#include <memory>
#include <GL/glew.h>
#include "math/Math.h"

namespace ogle {

class Shader;
class LocationCache;

class ShaderProgram {

	private:
		using ShaderPtr = std::unique_ptr<Shader>;
		using ShaderVector = std::vector<ShaderPtr>;

	public:
		explicit ShaderProgram(const std::string& file_name);
		~ShaderProgram();

		void Enable();
		void Disable();
		void SetUniform1f(const std::string& attrib_name, const float f);
		void SetUniform2f(const std::string& attrib_name, const vec2& v);
		void SetUniformMat4(const std::string& attrib_name, const mat4& matrix);

	private:
		void Create();
		void AttachShader(const std::string& file_name);
		void Link();
		bool SuccessfulLinkage() const;
		void LogLinkageError() const;

		GLuint m_object;
		ShaderVector m_shaders;
		std::unique_ptr<LocationCache> m_location_cache;
		bool m_linked;
		bool m_enabled;
};

} // namespace ogle
