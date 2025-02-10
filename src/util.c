#include "indef.h"
#include "util.h"

int str_copy(char* target, const char* source) 
{
    if (!source || !target) { return 0; }
    // stop if end of target/source string or after doing UINT16_MAX iterations
    uint32_t count = 0;
    while (*target && (*target = *source) && (count++ < UINT16_MAX)) {
        target++;
        source++;
    }
    return 1;
}


int str_copy_nonull(char* target, const char* source)
{
    if (!source || !target) { return 0; }
    // stop if end of target/source string or after doing UINT16_MAX iterations
    uint32_t count = 0;
    while (*source && *target && (*target = *source) && (count++ < UINT16_MAX)) {
        target++;
        source++;
    }
    return 1;
}
