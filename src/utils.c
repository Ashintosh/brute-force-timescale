#include "utils.h"
#include <time.h>

#define NANOSECONDS_PER_SECOND 1000000000L

double get_time_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / (double)NANOSECONDS_PER_SECOND;
}
