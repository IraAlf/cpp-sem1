//
// Created by irinina on 25.10.2020.
//

#define MAX_BUF 160
#include "../headers/utils.h"
#include "../headers/find_max.h"

enum mode {read, write};

char* max_word_in_file(char *filename) {
    struct stat statbuf;
    char *str = mmaping_file(filename, &statbuf);
    if (!str) {
        return NULL;
    }


    int num_of_proc = get_nprocs();
    if (statbuf.st_size / num_of_proc < MIN_CHANK_SIZE) {
        return find_max_word(str, statbuf.st_size);
    }
    pid_t *pid = (pid_t *) malloc(num_of_proc * sizeof(pid_t));
    if (!pid) {
        munmap((void *) str, statbuf.st_size);
        return NULL;
    }
    job_conf **job_array = split_memory(str, statbuf.st_size, num_of_proc);
    if (!job_array) {
        munmap((void *) str, statbuf.st_size);
        free (pid);
        return NULL;
    }
    int status = 0;
    int fd[2];
    pipe(fd);
    for (int i = 0; i < num_of_proc; ++i) {
        pid[i] = fork();
        if (pid[i] == -1) {
            return NULL;
        }

        if (pid[i] == 0) {
            close(fd[read]);
            char *res;
            res = find_max_word(job_array[i]->start, job_array[i]->size);
            if (res) {
                char *temp = realloc(res, strlen(res) + 1);
                if (temp)
                {
                    res = temp;
                    strcat(res, " ");
                    int len = strlen(res);
                    write(fd[write], res, len * sizeof(char) );
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    return NULL;
                }           
            }
            else
            {
                return NULL;
            }
        }
    }
    for (int i = 0; i < num_of_proc; ++i) {
        waitpid(pid[i], &status, 0);
    }
    close(fd[write]);
    char *buf = (char*)malloc(sizeof(char) * MAX_BUF);
    if (!buf) {
        free(pid);
        free_job_conf(job_array, num_of_proc);
        munmap((void *) str, statbuf.st_size);
        return NULL;
    }
    char *res_word;
    read(fd[read], buf, MAX_BUF);
    strip(buf, strlen(buf));
    res_word = find_max_word(buf, strlen(buf));
    free(buf);
    free(pid);
    free_job_conf(job_array, num_of_proc);
    munmap((void *) str, statbuf.st_size);
    return res_word;
}


