#include "util/Assert.h"
#include <cstdlib>
#include <cstdarg>
#include "util/Logger.h"

void FailedAssertion(const char* expression, const char* file, const int line,
		const char* function, const char* message) {
	{
		ogle::LogBuffer log_assertion{ogle::log_error()};

		log_assertion << "ASSERTION FAILED!";
		log_assertion << "\n---------------------------\n";
		log_assertion << "  File: " << file << "\n";
		log_assertion << "  Function: " << function << "\n";
		log_assertion << "  Line: " << line << "\n";
		log_assertion << "  Expression: " << expression << "\n";
		log_assertion << "Message: " << message;
		log_assertion << "\n---------------------------\n";
	}

	std::quick_exit(EXIT_FAILURE);
}

void FailedAssertionFormatted(const char* expression, const char* file, const int line,
		const char* function, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);

	va_list for_size;
	va_copy(for_size, args);
	size_t size = static_cast<size_t>(vsnprintf(nullptr, 0, fmt, for_size) + 1);
	va_end(for_size);
	
	char* buffer = new char[size];
	vsnprintf(buffer, size, fmt, args);

	{
		ogle::LogBuffer log_assertion{ogle::log_error()};

		log_assertion << "ASSERTION FAILED!";
		log_assertion << "\n---------------------------\n";
		log_assertion << "  File: " << file << "\n";
		log_assertion << "  Function: " << function << "\n";
		log_assertion << "  Line: " << line << "\n";
		log_assertion << "  Expression: " << expression << "\n";
		log_assertion << "Message: " << buffer;
		log_assertion << "\n---------------------------\n";
	}

	delete[] buffer;
	va_end(args);
	std::quick_exit(EXIT_FAILURE);
}
