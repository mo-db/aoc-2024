#ifndef UTIL_H
#define UTIL_H

#include "indefs.h"

// custom impl of strcpy
int str_copy(char* target, const char* source);

// doesnt copy /0 into target
int str_copy_nonull(char* target, const char* source);

#endif
