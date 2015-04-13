#include "graphics/ShaderProgram.h"
#include "graphics/Shader.h"
#include "graphics/LocationCache.h"
#include "util/Assert.h"
#include "util/Logger.h"
#include "util/GlLog.h"

namespace ogle {

ShaderProgram::ShaderProgram(const std::string& file_name) :
	m_object{0},
	m_shaders{},
	m_location_cache{nullptr},
	m_linked{false},
	m_enabled{false}
{
	Create();
	AttachShader(file_name);
	Link();
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(m_object);
	CHECK_GL_ERRORS("Destroying a program.");
}

void ShaderProgram::Enable() {
	ASSERT(m_linked == true, "The program has not been linked.");
	glUseProgram(m_object);
	m_enabled = true;
}

void ShaderProgram::Disable() {
	glUseProgram(0);
	m_enabled = false;
}

void ShaderProgram::SetUniform2f(const std::string& attrib_name, const float x, const float y, const float z) {
	ASSERT(m_enabled == true, "The program has not been enabled.");
	const GLint location = m_location_cache->Get(attrib_name);
	glUniform3f(location, x, y, z);
}

void ShaderProgram::Create() {
	m_object = glCreateProgram();
	ASSERT(m_object != 0, "Could not create the OpenGL ShaderProgram.");
	m_location_cache = std::make_unique<LocationCache>(m_object);
}

void ShaderProgram::AttachShader(const std::string& file_name) {
	ASSERT(m_linked == false, "The program has already been linked.");
	
	// Construct both vertex and fragment shaders from the file name.
	m_shaders.emplace_back(std::make_unique<Shader>(file_name + k_vertex_file_type,
		GL_VERTEX_SHADER));
	glAttachShader(m_object, m_shaders.back()->Object());

	m_shaders.emplace_back(std::make_unique<Shader>(file_name + k_fragment_file_type,
		GL_FRAGMENT_SHADER));
	glAttachShader(m_object, m_shaders.back()->Object());

	CHECK_GL_ERRORS("Attaching shaders to a program.");
}

void ShaderProgram::Link() {
	ASSERT(m_linked == false, "The program has already been linked.");

	glLinkProgram(m_object);
	CHECK_GL_ERRORS("Linking a program.");

	for(const auto& shader : m_shaders) {
		glDetachShader(m_object, shader->Object());
	}

	if(SuccessfulLinkage()) {
		m_linked = true;
	}
	else {
		LogLinkageError();
	}

}

bool ShaderProgram::SuccessfulLinkage() const {
	GLint link_status = 0;
	glGetProgramiv(m_object, GL_LINK_STATUS, &link_status);
	CHECK_GL_ERRORS("Getting program link status.");

	return (link_status == GL_TRUE);
}

void ShaderProgram::LogLinkageError() const {
	ASSERT(m_linked == false, "The program has not been linked.");

	GLint info_log_length;
	glGetProgramiv(m_object, GL_INFO_LOG_LENGTH, &info_log_length);
	CHECK_GL_ERRORS("Getting program compile log length.");

	GLchar* str_info_log = new GLchar[info_log_length + 1];
	glGetProgramInfoLog(m_object, info_log_length, nullptr, str_info_log);
	CHECK_GL_ERRORS("Getting program compile log.");

	log_error() << "ShaderProgram linker failure: " << str_info_log;
	delete[] str_info_log;
}

} // namespace ogle
