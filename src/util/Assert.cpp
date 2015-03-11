#include "util/Assert.h"
#include <cstdlib>
#include "util/Logger.h"

void FailedAssertion(const char* expression, const char* message, const char* file,
		const int line, const char* function) {
	{
		ogle::LogBuffer assertion_logger = ogle::log_error();

		assertion_logger << "ASSERTION FAILED!";
		assertion_logger << "\n---------------------------\n";
		assertion_logger << "  File: " << file << "\n";
		assertion_logger << "  Function: " << function << "\n";
		assertion_logger << "  Line: " << line << "\n";
		assertion_logger << "  Expression: " << expression << "\n";	
		assertion_logger << "Message: " << message;
		assertion_logger << "\n---------------------------\n";
	}

	std::quick_exit(EXIT_FAILURE);
}
