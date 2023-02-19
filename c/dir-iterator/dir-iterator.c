#include "dir-iterator.h"

char ** filename_v;
size_t filename_n;

int load_directory_by_path(char * path) {
    DIR * dp = NULL;
    struct dirent * ep = NULL;

    filename_v = NULL;
    filename_n = 1;

    dp = opendir(path);

    if(dp != NULL) {
        filename_v = calloc(filename_n, sizeof(char*));

        while((ep = readdir(dp)) != NULL) {
            if(ep->d_type == DT_REG) {
                char ** new_adress;
                filename_v[filename_n - 1] = malloc(strlen(ep->d_name) + strlen(path) + 1);
                strcpy(filename_v[filename_n - 1], path);
                strcat(filename_v[filename_n - 1], ep->d_name);
                filename_n++;
                new_adress = realloc(filename_v, filename_n * sizeof(char*));
                if(new_adress != NULL) {
                    filename_v = new_adress;
                    filename_v[filename_n - 1] = NULL;
                } else {
                    // TODO Free memory already allocated at this point
                    return -1;
                }
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

    if(filename_n == 1) {
        return NULL;
    }

    if(n < filename_n && filename_v != NULL) {
        n++;
        return filename_v[n - 1];
    }

    return NULL;
}

void close_directory() {
    if(filename_n == 1)
        return;

    for(register unsigned int i = 0; i < filename_n; i++) {
        if(filename_v[i] != NULL)
            free(filename_v[i]);
    }

    if(filename_v != NULL)
        free(filename_v);

    return;
}