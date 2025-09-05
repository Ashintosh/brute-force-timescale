#include "counter.h"
#include <stdint.h>

#define MAX_PART_VALUE 0xFFFFFFFFFFFFFFFFULL

void increment(unsigned long long *counter, int parts) {
    for (int i = parts - 1; i >= 0; i--) {
        if (++counter[i] != 0ULL) break;
    }
}

bool is_max(const unsigned long long *counter, int parts) {
    for (int i = 0; i < parts; i++) {
        if (counter[i] != MAX_PART_VALUE) return false;
    }
    return true;
}
