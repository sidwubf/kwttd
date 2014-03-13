#include "kwttd_util.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int
kwttd_strcmp(char *a, char *b) {
	if (a == b)
		return 1;

    size_t a_len = strlen(a);
    size_t b_len = strlen(b);
    if (a_len != b_len) {
        return -1;
    }

    return strncmp(a, b, a_len);
}

char
*kwttd_strsub(char *s, int offset, int limit) {
    size_t s_len = strlen(s);
    if (s_len < (offset + limit)) {
        offset = 0;
        limit = s_len;
    }
    char *r;
    r = (char *) malloc(limit + 1);
    strncpy(r, &s[offset], limit);
    return r;
}

int
kwttd_strstartwith(const char *pre, const char *str) {
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? -1 : strncmp(pre, str, lenpre);
}

