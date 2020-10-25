//
// Created by irinina on 25.10.2020.
//

#include "utils.h"


job_conf **split_memory(char *str, size_t str_length, size_t num_of_proc) {
    job_conf **job_array = (job_conf **) malloc(sizeof(job_conf *) * num_of_proc);
    if (!job_array) {
        return NULL;
    }
    for (size_t i = 0; i < num_of_proc; i++) {
        job_array[i] = (job_conf *) malloc(sizeof(job_conf));
        if (!job_array[i]) {
            free(job_array);
            return NULL;
        }
    }
    char *prev_start = str;
    for (size_t i = 0; i < num_of_proc; i++)     {
        char *start = str + str_length / num_of_proc * i;
        while(*start != ' ' && *start != '\0' && i != 0) {
            start++;
            offset++;
        }
        job_array[i]->start = start;
        if (start != prev_start)
            if (i != 0) {
                job_array[i - 1]->size = start - prev_start;
            }
        prev_start = start;
        if (i == num_of_proc - 1)
            job_array[num_of_proc - 1]->size = start + str_length + 1 - prev_start;
    }
    return job_array;
}


void free_job_conf(job_conf **arr, int n) {
    if (!arr) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

char *mmaping_file(char *filename, struct stat *statbuf) {
    if (!filename) {
        return NULL;
    }

    FILE *stream = fopen(filename, "r");
    if (!stream) {
        printf("Cannot open file.\n");
        return NULL;
    }

    if (fstat(fileno(stream), statbuf) < 0) {
        fclose(stream);
        return NULL;
    }
    char *str = (char *) mmap(0, statbuf->st_size, PROT_READ, MAP_SHARED, fileno(stream), 0);
    if (str == MAP_FAILED) {
        printf("Mapping failed\n");
        fclose(stream);
        return NULL;
    }
    fclose(stream);
    return str;
}


char *find_max_word(const char *str, size_t strsize) {
    if (!str) {
        return (void*)EXIT_FAILURE;
    }
    int max_len = 0, current_len = 0;
    char *max_word = (char*)calloc(1, sizeof(char));
    char *current_word = NULL;
    for (size_t i = 0; i < strsize; i++) {
        if (str[i] != ' ' && str[i] != '\0')
        {
            current_word = realloc(current_word, current_len + 1);
            strncat(current_word, str + i, 1);
            current_len++;
        }
        else
        {
            if (current_len > max_len) {
                max_len = current_len;
                void *tmp = realloc(max_word, max_len );
                if (tmp != NULL)
                    max_word = tmp;
                strcpy(max_word, current_word);
                current_len = 0;
                current_word = realloc(current_word, 1);
                strcpy(current_word, "");
            }
            else {
                current_len = 0;
                current_word = (char *) realloc(current_word, 1);
                strcpy(current_word, "");
            }
        }
    }
    if (current_len > max_len) {
        max_len = current_len;
        void *tmp = realloc(max_word, max_len);
        if (tmp != NULL)
            max_word = tmp;
        strcpy(max_word, current_word);
    }
    char *word = (char *)calloc(max_len, max_len * sizeof(char));
    strcpy(word, max_word);
    free(max_word);
    return word;
}

void strip(char *str, size_t size)
{
    for (size_t i = 0; i < size; i++)
        if (str[i] == ' ' && str[i + 1] == ' ') {
            for (size_t j = i; j < size; j++)
                str[j] = str[j + 1];
            i--;
        }
}

