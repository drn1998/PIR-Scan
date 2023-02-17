#include <stdio.h>
#include "dir-iterator.h"

int main(int argc, char* argv[]) {
    char * next_file = NULL;
    
    if(load_directory_by_path("test/") == -1) {
        abort();
    }

    next_file = next_filename();
    puts(next_file);

    next_file = next_filename();
    puts(next_file);

    next_file = next_filename();
    puts(next_file);

    next_file = next_filename();

    if(!next_file)
        close_directory();

    return 0;
}