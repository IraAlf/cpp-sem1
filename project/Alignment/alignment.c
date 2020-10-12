//
// Created by irinina on 11.10.2020.
//

#include <stdlib.h>
#include "alignment.h"


struct element **alignment(struct element **array, int len, int max_len)
{
    int count = 0;
    for(int i = 0; i < len; i++)
    {
        count = 0;
        for (struct element *pcur = *(array + i); pcur->ptr != NULL; pcur++) {
            count++;
        }
        count++;
        if (count < max_len)
        {
            *(array + i) = realloc(*(array + i), max_len*sizeof(struct element));
            for (int j = count; j < max_len; j++)
                array[i][j].value = 0;
        }
        else if (count > max_len)
        {
            return NULL;
        }
    }
    return array;
}
