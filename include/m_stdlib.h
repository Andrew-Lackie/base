#ifndef _M_STDLIB_H
#define _M_STDLIB_H

char *m_strdup(const char *s);

#define strdup(x) m_strdup(x)

#endif
