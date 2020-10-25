//
// Created by irinina on 25.10.2020.
//

#include "finding_max_paral.h"


char* max_word_in_file_mp(char *filename) {
    struct stat statbuf;
    char *str = mmaping_file(filename, &statbuf);
    if (!str) {
        return (void*)0;
    }
    int num_of_proc = get_nprocs();
    if (statbuf.st_size / num_of_proc < MIN_CHANK_SIZE) {
        return find_max_word(str, statbuf.st_size);
    }
    pid_t *pid = (pid_t *) malloc(num_of_proc * sizeof(pid_t));
    if (!pid) {
        munmap((void *) str, statbuf.st_size);
        return (void*)0;
    }
    job_conf **job_array = split_memory(str, statbuf.st_size, num_of_proc);
    if (!job_array) {
        munmap((void *) str, statbuf.st_size);
        free (pid);
        return (void*)0;
    }
    int status = 0;
    int fd[2];
    pipe(fd);
    for (int i = 0; i < num_of_proc; i++) {
        pid[i] = fork();
        if (pid[i] == -1) {
            return (void*)0;
        }

        if (pid[i] == 0) {
            close(fd[0]);
            char *res;
            void *temp = find_max_word(job_array[i]->start, job_array[i]->size);
            if (temp) {
                res = temp;
                res = realloc(res, strlen(res) + 1);
                strcat(res, " ");
                int len = strlen(res);
                write(fd[1], res, len * sizeof(char) );
                exit(EXIT_SUCCESS);
            }
            else
                return (void *)0;
            free(res);
        }
    }
    for (int i = 0; i < num_of_proc; i++) {
        waitpid(pid[i], &status, 0);
    }
    close(fd[1]);
    char *buf = (char*)malloc(sizeof(char) * 160);
    if (!buf) {
        free(pid);
        free_job_conf(job_array, num_of_proc);
        munmap((void *) str, statbuf.st_size);
        return (void*)0;
    }
    char *res_word;
    read(fd[0], buf, 160);
    strip(buf, strlen(buf));
    res_word = find_max_word(buf, strlen(buf));
    free(buf);
    free(pid);
    free_job_conf(job_array, num_of_proc);
    munmap((void *) str, statbuf.st_size);
    return res_word;
}


