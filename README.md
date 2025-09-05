# brute-force-timescale

A simple demo to show how long it would take to check every iteration of a possible key of n bits.

## Features

- Configure number of 64-bit parts in the counter (default: 2 -> 128 bit total)
- Display counter in **binary** or **hexadecimal**
- Configurable target guesses per second (`--gps`)
- High-speed mode with configurable display interval (`--highspeed`, `--hs-interval`)
- Real-time display of elapsed time, total attempts, and actual guess rate
- Command-line options with `--help` for usage

---

## Build Instructions

1. Clone or download the repo:
    ```bash
    git clone https://github.com/Ashintosh/brute-force-timescale
    ```
2. Build using Makefile:
    ```bash
    make
    ```
3. Clean build artifacts (optional):
    ```bash
    make clean
    ```

This will create:
- Object files in `bin/obj/`
- Executable at `bin/bft`

---

## Usage

```bash
./bft [OPTIONS]
```
### Options
| Option                | Description                                                            |
| --------------------- | ---------------------------------------------------------------------- |
| `--help`              | Show help message and exit                                             |
| `--parts <number>`    | Number of 64-bit parts in the counter (default: 2)                     |
| `--gps <number>`      | Target guesses per second (ignored in high-speed mode, default: 10000) |
| `--highspeed`         | Enable high-speed mode                                                 |
| `--binary`            | Display counter in binary (default)                                    |
| `--hex`               | Display counter in hexadecimal                                         |
| `--hs-interval <num>` | Display interval in high-speed mode (default: 10000000)                |

### Example
Run a 4-part counter, in hexadecimal, high-speed mode, updating every 5,000,000 guesses:
```bash
./bft --hex --highspeed --hs-interval 5000000 --parts 4
```

---

## Notes
- High-speed mode only updates the output at the specified interval to reduce console clutter and IO calls that slow it down.
- Binary output is very wide for large part counts. Consider using hexadecimal mode for readability.
- The application is single-threaded and uses nanosleep to simulate the target guesses per second.
