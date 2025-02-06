#include "util.h"

int str_copy(char* target, const char* source) 
{
    if (!source || !target) { return 0; }
    uint32_t count = 0;
    // stop if end of target/source string or after doing UINT16_MAX iterations
    while (*target && (*target = *source) && (count++ < UINT16_MAX)) {
        target++;
        source++;
    }
    return 1;
}
