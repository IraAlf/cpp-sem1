//
// Created by irinina on 11.10.2020.
//

#ifndef PROJECT_ALIGNMENT_H
#define PROJECT_ALIGNMENT_H

struct element
{
    int value;
    void *ptr;
};
struct element **alignment(struct element **array, int len, int max_len);

#endif //PROJECT_ALIGNMENT_H
