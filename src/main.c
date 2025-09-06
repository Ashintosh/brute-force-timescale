#include "config.h"
#include "counter.h"
#include "display.h"
#include "utils.h"

#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define BITS_PER_PART 64

struct timespec compute_delay(double gps);
void display_counter(const Config *cfg, unsigned long long *counter,
    unsigned long long attempts, double elapsed);
void run_counter(const Config *cfg);

int main(int argc, char **argv) {
    Config cfg;
    parse_args(argc, argv, &cfg);

    run_counter(&cfg);
    return 0;
}

struct timespec compute_delay(double gps) {
    struct timespec ts = {0};
    if (gps > 0) {
        double delay_sec = 1.0 / gps;
        ts.tv_sec = (time_t)delay_sec;
        ts.tv_nsec = (long)((delay_sec - ts.tv_sec) * 1e9);
    }
    return ts;
}

void display_counter(const Config *cfg, unsigned long long *counter,
    unsigned long long attempts, double elapsed) {
    char buf[cfg->parts * 64 + 1];
    if (cfg->hex_mode) print_hex(counter, cfg->parts, buf, sizeof(buf));
    else print_binary(counter, cfg->parts, buf, sizeof(buf));

    if (cfg->high_speed_mode) {
        printf("\033[2F");                  // Move cursor up 2 lines
        printf("\033[K%s\n", buf);          // Clear line and print counter
        printf("\033[KElapsed: %.2fs | Attempts: %llu | Actual rate: %.2f guesses/s\n",
            elapsed, attempts, attempts / elapsed);
    } else {
        printf("\r%s\n", buf);
        printf("Elapsed: %.2fs | Attempts: %llu | Actual rate: %.2f guesses/s",
            elapsed, attempts, attempts / elapsed);
    }

    fflush(stdout);
}

void run_counter(const Config *cfg) {
    unsigned long long counter[cfg->parts];
    for (int i = 0; i < cfg->parts; i++) counter[i] = 0;

    unsigned long long attempts = 0;
    double start = get_time_seconds();
    struct timespec ts = compute_delay(cfg->guesses_per_sec);

    while (!is_max(counter, cfg->parts)) {
        attempts++;
        increment(counter, cfg->parts);

        double elapsed = get_time_seconds() - start;

        if (cfg->high_speed_mode) {
            if (attempts % cfg->hsm_display_interval == 0) {
                display_counter(cfg, counter, attempts, elapsed);
            }
        } else {
            display_counter(cfg, counter, attempts, elapsed);
            if (cfg->guesses_per_sec > 0) nanosleep(&ts, NULL);
            printf("\033[F");
        }
    }

    display_counter(cfg, counter, attempts, get_time_seconds() - start);
    printf("\nDONE after %.2f s, attempts=%llu\n",
        get_time_seconds() - start, attempts);
}
