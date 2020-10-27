//
// Created by irinina on 25.10.2020.
//

#include "find_max.h"
#include "utils.h"

char* max_word_in_file(char *filename) {
    struct stat statbuf;
    char *str = mmaping_file(filename, &statbuf);
    if (!str) {
        return (void *) 0;
    }
    return find_max_word(str, statbuf.st_size);
}
