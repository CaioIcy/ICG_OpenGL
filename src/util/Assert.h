#pragma once

#ifdef NDEBUG
#	define ASSERT(expression, message)
#else
#	define ASSERT(expression, message) (void)((expression) || (FailedAssertion(#expression, message, __FILE__, __LINE__, __func__), 0))
#endif

void FailedAssertion(const char* expression, const char* message, const char* file,
	const int line, const char* function);
