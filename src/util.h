#pragma once

#define New(x) (x*)malloc(sizeof(x))
#define NewArray(x, s) (x*)malloc(sizeof(x) * s)
#define Delete(x)  \
    if (x != NULL) \
        free(x);   \
    x = NULL
