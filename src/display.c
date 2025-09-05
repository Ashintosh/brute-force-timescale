#include "display.h"

#define BITS_PER_PART 64
#define HEX_DIGITS_PER_PART (BITS_PER_PART / 4)

void print_binary(const unsigned long long *counter, int parts, char *buf, size_t size) {
    size_t pos = 0;
    for (int i = 0; i < parts; i++) {
        for (int bit = BITS_PER_PART - 1; bit >= 0; bit--) {
            if (pos < size - 1)
                buf[pos++] = ((counter[i] >> bit) & 1ULL) ? '1' : '0';
        }
    }
    buf[pos] = '\0';
}

void print_hex(const unsigned long long *counter, int parts, char *buf, size_t size) {
    size_t pos = 0;
    const char *hex_chars = "0123456789abcdef";

    for (int i = 0; i < parts; i++) {
        for (int shift = BITS_PER_PART - 4; shift >= 0; shift -= 4) {
            if (pos < size - 1) {
                buf[pos++] = hex_chars[(counter[i] >> shift) & 0xFULL];
            }
        }
    }
    buf[pos] = '\0';
}
