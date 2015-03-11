#include "Logger.h"
#include <iostream>
#include <utility>

namespace {

struct LogInfo {
	const char* tag;
	const char* color;
};

// constexpr implies const, but const is here to stop the compiler from yelling about
// -Wwrite-strings
constexpr const char* colorReset = "\033[0m";

constexpr LogInfo logInfos[] {
//	  Level   ,  Color
	{" ERROR ", "\033[1;4;91;49m"},
	{"WARNING", "\033[1;4;93;49m"},
	{" INFO  ", "\033[1;4;96;49m"},
	{" DEBUG ", "\033[1;4;32;49m"}
};

} // namespace

namespace ogle {

LogBuffer::LogBuffer(const LogLevel level) :
	m_log_level{static_cast<int>(level)},
	m_log_stream{}
{
	// Ignoring 'parameter not used' warning.
	(void)level;
}

LogBuffer::LogBuffer(const LogBuffer& log_buffer) :
	m_log_level{log_buffer.m_log_level},
	m_log_stream{}
{
}

LogBuffer::~LogBuffer() {
	std::clog << "[" << logInfos[m_log_level].color << logInfos[m_log_level].tag << colorReset
		<< "] - " << m_log_stream.str() << "\n";
}

template <LogLevel level>
LogBuffer log() {
	LogBuffer log_buffer{level};
	return log_buffer;
}

template LogBuffer log<LogLevel::Error>();
template LogBuffer log<LogLevel::Warn>();
template LogBuffer log<LogLevel::Info>();
template LogBuffer log<LogLevel::Debug>();

} // namespace ogle
