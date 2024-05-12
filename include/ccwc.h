#ifndef CCWC_H
#define CCWC_H

#include <stdio.h>

FILE *open_file(const char *filename, const char *mode);
int byte_count(const char *filename);
int line_count(const char *filename);
int word_count(const char *filename);
int char_count(const char *filename);

#endif