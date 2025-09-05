#ifndef DISPLAY_H
#define DISPLAY_H

#include <stddef.h>
#include <stdint.h>

void print_binary(const unsigned long long *counter, int parts, char *buf, size_t size);
void print_hex(const unsigned long long *counter, int parts, char *buf, size_t size);

#endif // DISPLAY_H
