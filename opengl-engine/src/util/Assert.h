#pragma once

#ifdef NDEBUG
#	define ASSERT(expression, message)
#	define ASSERTF(expression, fmt, ...)
#else
#	define ASSERT(expression, message) (void)((expression) || (FailedAssertion(#expression, __FILE__, __LINE__, __func__, message), 0))
#	define ASSERTF(expression, fmt, ...) (void)((expression) || (FailedAssertionFormatted(#expression, __FILE__, __LINE__, __func__, fmt, __VA_ARGS__), 0))
#endif

void FailedAssertion(const char* expression, const char* file, const int line,
	const char* function, const char* message);

void FailedAssertionFormatted(const char* expression, const char* file, const int line,
	const char* function, const char* fmt, ...);
