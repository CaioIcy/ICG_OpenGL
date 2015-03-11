#pragma once

#include <GL/glew.h>
#include <string>

namespace ogle {

static const std::string k_shader_path_prefix{"assets/shaders/"};
static const std::string k_fragment_file_type{".frag"};
static const std::string k_vertex_file_type{".vert"};
static const std::string k_geometry_file_type{".geom"};

class Shader {

	public:
		Shader(const std::string& file_name, GLenum shader_type);
		~Shader();

		std::string FileName() const;
		GLuint Object() const;
		GLenum ShaderType() const;

	private:
		void Create();
		void SetSource() const;
		void Compile() const;
		void CheckCompilationStatus() const;

		const std::string m_file_name;
		GLuint m_object;
		GLenum m_shader_type;
};

} // namespace ogle
