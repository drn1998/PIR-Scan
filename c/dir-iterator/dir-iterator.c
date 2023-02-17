#include "dir-iterator.h"

char ** filename_v = NULL;
size_t filename_n = 1;

int load_directory_by_path(char * path) {
    DIR * dp;
    struct dirent * ep;

    dp = opendir(path);

    if(dp != NULL) {
        filename_v = calloc(filename_n, sizeof(char*));

        while((ep = readdir(dp)) != NULL) {
            if(ep->d_type == DT_REG) {
                filename_v[filename_n - 1] = malloc(strlen(ep->d_name) + strlen(path) + 1);
                strcpy(filename_v[filename_n - 1], path);
                strcat(filename_v[filename_n - 1], ep->d_name);
                filename_n++;
                filename_v = realloc(filename_v, filename_n * sizeof(char*));
            }
        }
        closedir(dp);
    } else {
        return -1;
    }

    if(filename_n == 1) {
        return -1;
    }

    return 0;
}

char * next_filename() {
    static size_t n = 0;

    if(n < filename_n) {
        n++;
        return filename_v[n - 1];
    }

    return NULL;
}

void close_directory() {
    for(register unsigned int i = 0; i < filename_n - 1; i++) {
        free(filename_v[i]);
    }

    if(filename_v != NULL)
        free(filename_v);

    return;
}