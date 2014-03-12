#ifndef __KWTTD_UTIL_H
#define __KWTTD_UTIL_H

int kwttd_strcmp(char *a, char *b);
char *kwttd_strsub(char *s, int offset, int limit);
char *kwttd_strjoin(char *buf, char *delim, ...);

#endif
