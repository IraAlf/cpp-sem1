//
// Created by irinina on 25.10.2020.
//

#ifndef UNTITLED8_UTILS_H
#define UNTITLED8_UTILS_H



#define MIN_CHANK_SIZE 2
#define SERIAL 4
#define PARALLEL 5


#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef struct {
    char *start;
    size_t size;
} job_conf;


char *mmaping_file(char *filename, struct stat *statbuf);
job_conf **split_memory(char *str, size_t str_length, size_t num_of_proc);
void free_job_conf(job_conf **arr, int n);
void strip(char *str, size_t size);
char *find_max_word(const char *str, size_t strsize);


#endif //UNTITLED8_UTILS_H
