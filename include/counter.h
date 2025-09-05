#ifndef COUNTER_H
#define COUNTER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void increment(unsigned long long *counter, int parts);
bool is_max(const unsigned long long *counter, int parts);

#endif // COUNTER_H