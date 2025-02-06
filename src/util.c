#include "util.h"

int str_copy(char* target, const char* source) 
{
    if (!source || !target) { return 0; }
    uint32_t count = 0;
    while ((*target = *source) && (count++ < UINT16_MAX)) {
        target++;
        source++;
    }
    return 1;
}
