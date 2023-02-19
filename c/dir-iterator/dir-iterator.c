#include "dir-iterator.h"

char ** filename_v;
size_t filename_n;

int load_directory_by_path(char * path) {
    DIR * dp = NULL;
    struct dirent * ep = NULL;

    filename_v = NULL;
    filename_n = 0;
    size_t filename_a = 8;
    char ** new_adress;

    dp = opendir(path);

    if(dp != NULL) {
        filename_v = calloc(filename_a, sizeof(char*));

        while((ep = readdir(dp)) != NULL) {
            if(ep->d_type == DT_REG) {
                filename_v[filename_n] = malloc(strlen(ep->d_name) + strlen(path) + 1);
                if(filename_v[filename_n] == NULL) {
                    filename_n++;
                    closedir(dp);
                    close_directory();
                    return -1;
                }
                strcpy(filename_v[filename_n], path);
                strcat(filename_v[filename_n], ep->d_name);
                filename_n++;
                if(filename_n == filename_a) {
                    filename_a *= 2;
                    new_adress = realloc(filename_v, filename_a * sizeof(char*));
                    if(new_adress != NULL) {
                        filename_v = new_adress;
                    } else {
                        closedir(dp);
                        close_directory();
                        return -1;
                    }
                }
            }
        }
        closedir(dp);
    } else {
        return -1;
    }

    filename_a = filename_n + 1;

    new_adress = realloc(filename_v, filename_a * sizeof(char*));

    if(new_adress != NULL) {
        filename_v = new_adress;
        filename_v[filename_n] = NULL;
    } else {
        close_directory();
        return -1;
    }

    if(filename_n == 0) {
        filename_n++;
        close_directory();
        return -1;
    }

    return filename_n + 1;
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
    if(filename_n == 0)
        return;

    for(register unsigned int i = 0; i < filename_n; i++) {
        if(filename_v[i] != NULL)
            free(filename_v[i]);
    }

    if(filename_v != NULL)
        free(filename_v);

    return;
}