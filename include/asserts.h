#ifndef _ASSERTS_H
#define _ASSERTS_H

#include <signal.h>
#include "defines.h"

extern void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

#define M_ASSERT(expr)																						\
	{																																\
		if (expr) {																										\
			} else {																										\
				report_assertion_failure(#expr, "", __FILE__, __LINE__);	\
				raise(SIGTRAP);																						\
		}																															\
	}																																\

#define M_ASSERT_MSG(expr, message)																		\
	{																																		\
		if (expr) {																												\
			} else {																												\
				report_assertion_failure(#expr, message, __FILE__, __LINE__);	\
				raise(SIGTRAP);																						\
		}																																	\
	}																																		\



#endif
