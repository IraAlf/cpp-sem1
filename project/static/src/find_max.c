//
// Created by irinina on 25.10.2020.
//

#include "../headers/find_max.h"
#include "../headers/utils.h"

char* max_word_in_file(char *filename) {
    struct stat statbuf;
    if (filename)
    {
        char *str = mmaping_file(filename, &statbuf);
        if (!str) {
            return NULL;
        }
        return find_max_word(str, statbuf.st_size);
    }
    else return NULL;
}
