#include "graphics/LocationCache.h"
#include "util/Assert.h"

namespace ogle {

LocationCache::LocationCache(const GLuint program) :
	m_program{program},
	m_cache{}
{
}

GLint LocationCache::Get(const std::string& key) {
	GLint location = 0;
	const auto it = m_cache.find(key);

	// Location is already registered.
	if (it != m_cache.end()) {
		location = it->second;
	}
	// Location was not loaded yet.
	else {
		location = Load(key);
	}

	return location;
}

GLint LocationCache::Load(const std::string& key) {
	const auto location = glGetUniformLocation(m_program, key.c_str());
	ASSERT(location != -1, "Invalid uniform attribute.");
	RegisterLocation(key, location);
	return location;
}

void LocationCache::RegisterLocation(const std::string& key, GLint location) {
	m_cache.emplace(key, location);
}

void LocationCache::UnregisterLocation(const std::string& key) {
	const auto it = m_cache.find(key);
	if (it != m_cache.end()) {
		m_cache.erase(it);
	}
}

} // namespace ogle
