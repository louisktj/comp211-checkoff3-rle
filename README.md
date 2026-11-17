# Run-Length Encoding (RLE)

A small COMP 211 exploration of lossless data compression using C arrays, loops, and bytes.

RLE replaces consecutive copies of the same value with a count and that value. For example, `AAAAABBBCC` becomes `(5,A) (3,B) (2,C)`. Decoding repeats each value the specified number of times, recovering the original data exactly.

## Run the example

You need a C11 compiler such as Clang or GCC. No extra libraries are needed.

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -O0 rle_demo.c -o rle_demo
./rle_demo
./rle_demo "AAAABBBB"
./rle_demo --test
```

The default command prints four examples and verifies each round trip. The test command also checks empty input, one byte, binary values, runs of 255/256/1024 bytes, invalid counts, incomplete pairs, and insufficient output capacity.

## What is stored?

This example stores each run as **two actual bytes**, in this order:

1. A count from 1 to 255.
2. The repeated byte value.

The printed `(5,A)` notation is only a human-readable display. It is not the encoded representation used for the size calculation. For `AAAAABBBCC`, the six payload bytes are `05 41 03 42 02 43` in hexadecimal (ASCII input).

The program measures payload bytes. It excludes file headers, string terminators, and the temporary buffers allocated by the program. The demonstration keeps both original and compressed arrays in memory, so a smaller encoded payload does not mean this program itself uses less total memory. It is a teaching format, not a BMP-compatible encoder.

## Results and discoveries

| Input | Original bytes | Encoded bytes | Space saved |
| --- | ---: | ---: | ---: |
| `AAAAABBBCC` | 10 | 6 | 40.0% |
| `AAAAAA` | 6 | 2 | 66.7% |
| `ABABAB` | 6 | 12 | -100.0% |
| `111122` | 6 | 4 | 33.3% |

`Space saved = 100 × (1 − encoded bytes / original bytes)`.

Repeated values must be **adjacent**. `ABABAB` repeats a pattern, but each run has length one, so this format doubles its payload. With one count byte and one value byte per stored run, the encoded size is `2 × number of stored runs`. It shrinks data when the average stored run length is greater than two. Runs longer than 255 split into multiple pairs. For example, 256 copies of `A` become `(255,A) (1,A)`.

Fixed-width pairs also avoid confusing literal digits with counts: `111122` becomes `(4,'1') (2,'2')`. The decoder knows the count position and value position in every pair.

The encoder scans the input once: O(n) time. Decoding takes O(n) time in the size of the restored output. The worst-case encoded payload is 2n bytes in this simple format. The program caps command-line input at 1024 bytes and checks decoder output capacity.

## A real use

Windows bitmap formats include RLE modes for 8-bit and 4-bit indexed images. Microsoft describes an RLE8 encoded run as a count byte followed by a color-index byte. Real BMP streams also define escape codes and literal modes. The example here demonstrates only the basic count/value idea.

## Materials

- `rle_demo.c`: complete example and built-in checks.
- `docs/results.txt`: captured output from the program.
- `docs/resources.md`: references and what they support.
- `presentation/`: Google Slides draft, PDF snapshot, rehearsal script, and editable Markdown outline.

## Preparation status

These are AI-assisted preparation materials. Review the code, run the examples yourself, and use your own explanation and slide organization. The assignment requires student-created slides. This repository does not claim that the student has completed the personal reflection, recorded the presentation, or submitted the checkoff.
