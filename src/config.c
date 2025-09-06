#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 2

void parse_args(int argc, char **argv, Config *cfg) {
    // Defaults
    cfg->parts = 2;
    cfg->guesses_per_sec = 10000.0;
    cfg->high_speed_mode = 0;
    cfg->hex_mode = 0;
    cfg->hsm_display_interval = 10000000ULL;

    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];

        // Flags without values
        if (strcmp(arg, "--help") == 0) {
            print_help(argv[0]);
        } else if (strcmp(arg, "--version") == 0) {
            print_version(argv[0]);
        } else if (strcmp(arg, "--highspeed") == 0) {
            cfg->high_speed_mode = 1;
            continue;
        } else if (strcmp(arg, "--binary") == 0) {
            cfg->hex_mode = 0;
            continue;
        } else if (strcmp(arg, "--hex") == 0) {
            cfg->hex_mode = 1;
            continue;
        } 

        // Flags with values
        if ((strcmp(arg, "--parts") == 0 || strcmp(arg, "--gps") == 0 ||
            strcmp(arg, "--hs-interval") == 0) && i + 1 < argc) {
            char *value = argv[++i];

            if (strcmp(arg, "--parts") == 0)
                cfg->parts = atoi(value);
            else if (strcmp(arg, "--gps") == 0)
                cfg->guesses_per_sec = atof(value);
            else if (strcmp(arg, "--hs-interval") == 0)
                cfg->hsm_display_interval = strtoull(value, NULL, 10);

            continue;
        }

        // Unknown argument
        fprintf(stderr, "Unknown argument: %s\n\n", arg);
        print_help(argv[0]);
    }
}

void print_help(const char *prog_name) {
    printf("Usage: %s [OPTIONS]\n", prog_name);
    printf("Options:\n");
    printf("  --help               Show this help message and exit\n");
    printf("  --version            Show the version of this executable\n");
    printf("  --parts <number>     Number of 64-bit parts in the counter (default: 2)\n");
    printf("  --gps <number>       Target guesses per second (ignored in high-speed mode, default: 10000)\n");
    printf("  --highspeed          Enable high-speed mode\n");
    printf("  --binary             Display counter in binary (default)\n");
    printf("  --hex                Display counter in hexadecimal\n");
    printf("  --hs-interval <num>  Display interval in high-speed mode (default: 10000000)\n");
    printf("\nExample:\n");
    printf("  %s --parts 4 --gps 50000 --hex --highspeed --hs-interval 5000000\n", prog_name);
    exit(0);
}

void print_version(const char *prog_name) {
    printf("%s v%i.%i.%i", prog_name,
        VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    exit(0);
}
