#ifndef DIR_ITERATOR_H
#define DIR_ITERATOR_H

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

extern char ** filename_v;
extern size_t filename_n;

int load_directory_by_path(char * path);
char * next_filename();
void close_directory();

#endif