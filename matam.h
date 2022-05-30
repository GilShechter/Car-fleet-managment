

#ifndef HW_5_MATAM_H
#define HW_5_MATAM_H
#define ALLOC(typ,no) ((typ *) checked_malloc(sizeof(typ)*(no)))
#define FREE(ptr) checked_free(ptr)
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

void *checked_malloc(unsigned int);
void checked_free(void *);
void check_for_exit();



#endif
