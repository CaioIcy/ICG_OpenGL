#include "graphics/Shader.h"
#include <string>
#include "util/Assert.h"
#include "util/Logger.h"
#include "util/GlLog.h"
#include "util/Util.h"

namespace {

bool SameShaderFileType(const std::string& file_name, GLenum shader_type) {
	bool same_type = false;

	if((shader_type == GL_FRAGMENT_SHADER && file_name.find(ogle::k_fragment_file_type) != std::string::npos)
		|| (shader_type == GL_VERTEX_SHADER && file_name.find(ogle::k_vertex_file_type) != std::string::npos)
		|| (shader_type == GL_GEOMETRY_SHADER && file_name.find(ogle::k_geometry_file_type) != std::string::npos)
		) {
		same_type = true;
	}

	return same_type;
}

std::string ShaderTypeToString(GLenum shader_type) {
	std::string shader_type_str{""};

	switch(shader_type) {
		case GL_VERTEX_SHADER:
			shader_type_str = "vertex";
			break;
		case GL_GEOMETRY_SHADER:
			shader_type_str = "geometry";
			break;
		case GL_FRAGMENT_SHADER:
			shader_type_str = "fragment";
			break;
		default:
			shader_type_str = "UNKNOWN SHADER TYPE";
			ogle::log_warn() << "Unknown shader type in ShaderTypeToString.";
			break;
	}

	return shader_type_str;
}

} // namespace

namespace ogle {

Shader::Shader(const std::string& file_name, GLenum shader_type) :
	m_file_name{file_name},
	m_object{0},
	m_shader_type{shader_type}
{
	const bool correct_file = SameShaderFileType(file_name, shader_type);
	ASSERT(correct_file == true, "Wrong file type for shader type.");

	Create();
	SetSource();
	Compile();
}

Shader::~Shader() {
	glDeleteShader(m_object);
	CHECK_GL_ERRORS("Destroying a shader.");
}

std::string Shader::FileName() const {
	return m_file_name;
}

GLuint Shader::Object() const {
	return m_object;
}

GLenum Shader::ShaderType() const {
	return m_shader_type;
}

void Shader::Create() {
	m_object = glCreateShader(m_shader_type);
	CHECK_GL_ERRORS("Creating a shader.");

	ASSERT(m_object != 0, "Could not create shader.");
}

void Shader::SetSource() const {
	ASSERT(m_object != 0, "Can't set the source to an invalid shader.");

	// Get the shader code from the file.
	std::string shader_code_str{util::FileContentsToString(k_shader_path_prefix + m_file_name)};
	const char* shader_code = shader_code_str.c_str();

	glShaderSource(m_object, 1, &shader_code, nullptr);
	CHECK_GL_ERRORS("Setting a shader's source.");
}

void Shader::Compile() const {
	ASSERT(m_object != 0, "Can't compile an invalid shader.");

	glCompileShader(m_object);
	CHECK_GL_ERRORS("Compiling a shader.");

	CheckCompilationStatus();
}

void Shader::CheckCompilationStatus() const {
	ASSERT(m_object != 0, "Impossible to have compiled an invalid shader.");

	GLint compile_status;
	glGetShaderiv(m_object, GL_COMPILE_STATUS, &compile_status);
	CHECK_GL_ERRORS("Getting the shader compile status .");

	// Compilation failure.
	if(compile_status != GL_TRUE) {
		GLint info_log_length;
		glGetShaderiv(m_object, GL_INFO_LOG_LENGTH, &info_log_length);
		CHECK_GL_ERRORS("Getting the shader compilation info log length.");

		GLchar* str_info_log = new GLchar[info_log_length + 1];
		glGetShaderInfoLog(m_object, info_log_length, nullptr, str_info_log);
		CHECK_GL_ERRORS("Getting the shader compilation info log.");

		log_error() << "Shader compilation failure in " << ShaderTypeToString(m_shader_type)
			<< " shader: " << str_info_log;

		delete[] str_info_log;
	}
}

} // namespace ogle
