//
// Created by irinina on 25.10.2020.
//

#ifndef UNTITLED8_UTILS_H
#define UNTITLED8_UTILS_H



#define MIN_CHUNK_SIZE 2

#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
    char *start;
    size_t size;
} job_conf;


char *mmaping_file(char *filename, struct stat *statbuf);
job_conf **split_memory(char *str, size_t str_length, size_t num_of_proc);
void free_job_conf(job_conf **arr, int n);



#endif //UNTITLED8_UTILS_H
