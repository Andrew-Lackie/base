#include <defines.h>
#include <stdio.h>
#include <string.h>
#include <logger.h>
#include <stdarg.h>

void log_output(log_level level, const char* message, ...)
{
	const char* level_string[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};

	char out_message_1[32000];
	memset(out_message_1, 0, sizeof(out_message_1));

	va_list arg_ptr;
	va_start(arg_ptr, message);
	vsnprintf(out_message_1, 32000, message, arg_ptr);
	va_end(arg_ptr);

	char out_message_2[32000];
	sprintf(out_message_2, "\n%s%s\n", level_string[level], out_message_1);
	printf("%s", out_message_2);
}

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line)
{
	log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}
