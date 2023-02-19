#include <stdio.h>
#include "dir-iterator.h"

int main(int argc, char* argv[]) {
    char * next_file = NULL;

    if(load_directory_by_path("/home/drn/textfiles/") == -1) {
        exit(EXIT_FAILURE);
    }

    next_file = next_filename();

    while(next_file != NULL) {
        puts(next_file);
        next_file = next_filename();
    }

    close_directory();

    return 0;
}
