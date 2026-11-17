/* A small educational RLE format: [count byte][value byte].
 * Each count is 1..255. This is not a BMP file encoder.
 * AI-assisted example for COMP 211. */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

_Static_assert(CHAR_BIT == 8, "This example uses 8-bit bytes");
#define MAX_INPUT 1024

/* Caller provides room for 2 * n bytes. Empty input produces no pairs. */
static size_t encode(const unsigned char *input, size_t n,
                     unsigned char *output) {
    size_t i = 0, used = 0;
    while (i < n) {
        unsigned int count = 1;
        while (i + count < n && input[i + count] == input[i]
               && count < 255) {
            count++;
        }
        output[used++] = (unsigned char) count;
        output[used++] = input[i];
        i += count;
    }
    return used;
}

/* Return 1 on success, 0 for invalid pairs or insufficient output room. */
static int decode(const unsigned char *input, size_t n,
                  unsigned char *output, size_t capacity, size_t *used) {
    *used = 0;
    if (n % 2 != 0) return 0;
    for (size_t i = 0; i < n; i += 2) {
        unsigned int count = input[i];
        if (count == 0 || count > capacity - *used) return 0;
        for (unsigned int j = 0; j < count; j++) {
            output[(*used)++] = input[i + 1];
        }
    }
    return 1;
}

static void round_trip(const unsigned char *input, size_t n) {
    unsigned char packed[2 * MAX_INPUT], restored[MAX_INPUT];
    size_t restored_size;
    size_t packed_size = encode(input, n, packed);
    assert(decode(packed, packed_size, restored, sizeof restored, &restored_size));
    assert(restored_size == n);
    assert(memcmp(input, restored, n) == 0);
}

static void self_test(void) {
    const char *samples[] = {"", "A", "AAAAABBBCC", "ABABAB", "111122"};
    for (size_t i = 0; i < sizeof samples / sizeof samples[0]; i++) {
        round_trip((const unsigned char *) samples[i], strlen(samples[i]));
    }
    unsigned char long_run[MAX_INPUT], packed[2 * MAX_INPUT], out[MAX_INPUT];
    memset(long_run, 'A', sizeof long_run);
    const size_t lengths[] = {255, 256, 1024};
    for (size_t i = 0; i < sizeof lengths / sizeof lengths[0]; i++) {
        round_trip(long_run, lengths[i]);
    }
    size_t n = encode(long_run, 256, packed);
    assert(n == 4 && packed[0] == 255 && packed[2] == 1);
    const unsigned char binary[] = {0, 0, 255, 255, 255, 0};
    round_trip(binary, sizeof binary);
    size_t used;
    const unsigned char zero_count[] = {0, 'A'};
    const unsigned char odd_length[] = {3};
    const unsigned char too_large[] = {5, 'A'};
    assert(!decode(zero_count, sizeof zero_count, out, sizeof out, &used));
    assert(!decode(odd_length, sizeof odd_length, out, sizeof out, &used));
    assert(!decode(too_large, sizeof too_large, out, 4, &used));
    puts("PASS: 9 round trips, run splitting, and 3 invalid/capacity cases.");
}

static void show(const char *text) {
    unsigned char packed[2 * MAX_INPUT], restored[MAX_INPUT];
    size_t n = strlen(text), restored_size;
    size_t packed_size = encode((const unsigned char *) text, n, packed);
    printf("Input: %s\nPairs: ", n ? text : "(empty)");
    for (size_t i = 0; i < packed_size; i += 2) {
        printf("(%u,%c) ", (unsigned int) packed[i], packed[i + 1]);
    }
    printf("\nOriginal: %zu bytes\nEncoded payload: %zu bytes\n", n, packed_size);
    if (n) printf("Space saved: %.1f%%\n", 100.0 * (1.0 - (double) packed_size / n));
    else puts("Space saved: n/a (empty input)");
    int ok = decode(packed, packed_size, restored, sizeof restored, &restored_size);
    printf("Round trip: %s\n\n", ok && restored_size == n &&
           memcmp(text, restored, n) == 0 ? "PASS" : "FAIL");
}

int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "--test") == 0) {
        self_test();
        return 0;
    }
    if (argc > 2 || (argc == 2 && strlen(argv[1]) > MAX_INPUT)) {
        fprintf(stderr, "Usage: %s [ASCII text up to 1024 bytes | --test]\n", argv[0]);
        return 1;
    }
    if (argc == 2) show(argv[1]);
    else {
        show("AAAAABBBCC");
        show("AAAAAA");
        show("ABABAB");
        show("111122");
    }
    return 0;
}
