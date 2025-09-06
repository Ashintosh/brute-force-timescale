#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int parts;
    double guesses_per_sec;
    bool high_speed_mode;
    bool hex_mode;
    unsigned long long hsm_display_interval;
} Config;

void parse_args(int argc, char **argv, Config *cfg);
void print_help(const char *prog_name);
void print_version(const char *prog_name);

#endif // CONFIG_H
