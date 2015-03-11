#pragma once

#include <sstream>

namespace ogle {

/**
* @brief All the possible log levels.
*/
enum class LogLevel {
	Error,
	Warn,
	Info,
	Debug
};

/**
* @brief Temporary buffer that grabs log messages from stream.
*
* Usage examples:
*	1) log_debug() << "Hello world."
*		
*		Will print the message "[DEBUG] - Hello world.", since the LogBuffer created will
*		immediately be destroyed/go out of scope.
*
*	2) LogBuffer test_log = log_warn();
*	   test_log << "One two ";
*	   test_log << "three.";
*
*	   		After test_log goes out of scope, it will print "[WARNING] One two three.".
*
* @note The available functions to log are 'log_debug()', 'log_info()', 'log_warn()',
*	'log_error()'.
*/
class LogBuffer {

	public:
		/**
		* @brief The constructor;
		*
		* @param level : The log level desired.
		*/
		LogBuffer(const LogLevel level);

		/**
		* @brief The copy constructor.
		*
		* Needed for the main log function.
		*/
		LogBuffer(const LogBuffer& log_buffer);

		/**
		* @brief The destructor.
		*
		* Prints all the data received from the stream into std::clog.
		*/
		~LogBuffer();

		/**
		* @brief Adds arguments to m_log_stream.
		*/
		template <typename T>
		LogBuffer& operator<<(const T& t) {
			m_log_stream << t;
			return *this;
		}

		const int m_log_level; /**< The log level for this buffer. */

	private:
		std::ostringstream m_log_stream; /**< Receives data from overloaded operator<<. */
};

/**
* @brief Main log function.
*
* @note Should never be called directly. Instead, use the 'log_*()' aliases.
*/
template <LogLevel level>
LogBuffer log();

using log_function_ptr = LogBuffer (*) ();

// Aliases that should be used for logging.
constexpr log_function_ptr log_error = log<LogLevel::Error>;
constexpr log_function_ptr log_warn  = log<LogLevel::Warn>;
constexpr log_function_ptr log_info  = log<LogLevel::Info>;
constexpr log_function_ptr log_debug = log<LogLevel::Debug>;

} // namespace ogle
