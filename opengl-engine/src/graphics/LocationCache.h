#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include <string>

namespace ogle {

class LocationCache final {

	private:
		using CacheType = std::unordered_map<std::string, GLint>;

	public:
		LocationCache(const GLuint program);
		~LocationCache() = default;

		// Not copyable and not moveable.
		LocationCache(const LocationCache&) = delete;
		LocationCache& operator=(const LocationCache&) = delete;
		LocationCache(LocationCache&&) = delete;
		LocationCache& operator=(LocationCache&&) = delete;

		GLint Get(const std::string& key);

	private:
		GLint Load(const std::string& key);
		void RegisterLocation(const std::string& key, GLint location);
		void UnregisterLocation(const std::string& key);

		GLuint m_program;
		CacheType m_cache; /**< The map that contains all the T locations. */
};

} // namespace ogle
