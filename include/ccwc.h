#ifndef CCWC_H
#define CCWC_H

#include <stdio.h>

FILE *open_file(const char *filename);
int byte_count(FILE *file);
int line_count(FILE *file);
int word_count(FILE *file);
int char_count(FILE *file);
int count_all(FILE *file, int *line_count, int *word_count, int *byte_count, int *char_count);

#endif