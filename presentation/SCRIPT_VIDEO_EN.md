# Presentation rehearsal script

Use this as a practice aid. Explain the material in your own words during the actual presentation. The timing is a target, not a measured recording. Allow time for the audience question. The references slide is a backup.

## Slide 1 — Run-Length Encoding

Hi, I'm Louis Kuo Tsing Jen. My topic is run-length encoding, or RLE. It is a simple way to compress data without losing any information.

Suppose a file contains the same value many times in a row. Instead of storing every copy, we can store how many copies there are and what the value is. That is the basic idea of RLE.

This connects to COMP 211 because the way we represent data affects how many bytes we need. I will show the idea, a small C implementation, and an example where compression makes the data bigger.

## Slide 2 — A run is a group of equal neighbors

A run is a group of consecutive copies of the same value. In this example, we have five A values, then three B values, then two C values.

We can represent those groups as five A, three B, and two C. To decode them, repeat each value the number of times given by its count. That brings us back to exactly the same input.

This is why RLE is lossless. The values and their order are preserved. One important detail is that the copies have to be next to each other. Two A values separated by a B belong to different runs.

## Slide 3 — The byte format matters

To say how much space we save, we need to define the format. In this experiment, every run uses two bytes: one count byte and one value byte.

The original example has ten ASCII bytes. It contains three runs, so the encoded payload uses six bytes. That saves four out of ten bytes, or forty percent.

The parentheses are only a readable way of printing the pairs. The program stores actual byte values. For example, hexadecimal 41 is the ASCII value for A.

These numbers compare payload sizes. They exclude headers and string terminators. The program also allocates temporary arrays, so this is not a measurement of its total memory use.

## Slide 4 — The C encoder

Here is the main loop from the C example. The variable i is the position where a run starts. The count starts at one because there is already one value at that position.

The inner loop checks whether the next byte matches. If it does, the count increases. The loop stops when the value changes, the input ends, or the count reaches 255.

The program then writes the count and the value into the output array. Finally, it moves i forward by the run length.

The full program also has a decoder and checks that decoding returns the original input. Runs longer than 255 split into multiple pairs. For example, 256 A values become a run of 255 and a run of one.

## Slide 5 — Which input gets smaller?

Here is a question: using our two-byte format, which of these inputs gets smaller, six A values or ABABAB?

**Pause for about 10–15 seconds. Let a classmate answer before changing slides.**

A useful way to think about it is to count the runs. Both inputs contain six bytes, but they have very different numbers of runs.

## Slide 6 — RLE can make data larger

Six A values form one run, so the encoded version needs only two bytes. ABABAB forms six runs of length one. Each needs two bytes, so the encoded version takes twelve bytes instead of six.

ABABAB repeats a pattern, but RLE only groups equal neighbors. That is the difference.

For this format, the average stored run must be longer than two bytes to save space. Counts have a cost.

A real application is indexed bitmap images. Microsoft documents RLE modes for four-bit and eight-bit bitmaps. Long stretches of one color can form long runs. Real BMP formats also have special codes and literal modes. This C example only demonstrates the count-and-value idea.

## Slide 7 — The main takeaway

RLE stores a count and a value, and the decoder repeats the value. This recovers the original data exactly.

The main limitation is that the counts cost space. Long runs can give a smaller representation. Alternating values can make it larger.

So the main takeaway is that compression depends on the structure of the input. A simple method can work very well for some data and poorly for other data.

One possible next question is how a format handles data with very few runs without doubling its size. That is where something like a literal mode becomes useful.

Thank you. Are there any questions?

## Before recording

- Rehearse aloud and measure the actual duration. Aim for 5–7 minutes.
- Add your own reason for selecting the topic and your own observation about what you learned.
- Use your personally created final slides in both the recording and the in-person presentation.
- Keep the technical claims consistent with the two-byte format in the code.
