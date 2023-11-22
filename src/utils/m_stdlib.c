#include <m_stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *m_strdup(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if(p) { strcpy(p, s); }
    return p;
}
