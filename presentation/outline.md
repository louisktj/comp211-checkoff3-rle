# 1. Run-Length Encoding

0:00–0:35. Introduce yourself: Louis Kuo Tsing Jen. The topic is a simple form of lossless compression. Start with this question: if the same letter appears many times in a row, do we need to store each copy separately? RLE stores the repetition as a count and a value. This connects to COMP 211 because it is about how we represent information as bytes. The goal is to explain the basic idea, show a small C example, and show a case where compression actually makes the data larger. Add your real reason for choosing the topic when rehearsing.

Sources: https://www.cs.cmu.edu/afs/cs.cmu.edu/project/pscico-guyb/realworld/www/compression.pdf

# 2. A run is a group of equal neighbors

0:35–1:30. A run means consecutive copies of the same value. In this example, the first run has five A values, the second has three B values, and the last has two C values. Store the count and value for each run. To decode the first pair, write A five times, then B three times, then C twice. We get the exact original sequence back. That is what lossless means. Nothing about the original values or their order is lost. Two A values separated by a B belong to different runs. RLE groups equal neighbors, rather than finding every copy of a letter anywhere in the data.

Sources: https://www.cs.cmu.edu/afs/cs.cmu.edu/project/pscico-guyb/realworld/www/compression.pdf

# 3. The byte format matters

1:30–2:25. The parentheses on the previous slide are just a display. For the experiment, each run really uses two bytes: one count byte and one value byte. A count can hold values from one to 255. These three runs therefore use six payload bytes instead of ten original ASCII bytes. Four out of ten bytes are saved, or 40 percent. In hexadecimal, the pairs are 05 41, 03 42, and 02 43. Here 41 is the ASCII value for A. The calculation excludes file headers and string terminators. Also, the demo allocates temporary arrays, so this payload comparison is not a measurement of total program memory. A different format could have different costs.

Sources: Project rle_demo.c and docs/results.txt

# 4. The C encoder

2:25–3:30. This is the main loop from the program. The index i points at the first byte in a run. Start the count at one. Compare the next byte with the current value and extend the run while they match. The loop stops at a different value, the end of the input, or the maximum count of 255. Then write the count and the value into the output array. Move i forward by the count to begin the next run. This uses arrays, indexes, a loop, and comparisons. The full program includes decoding and a round-trip check. A run of 256 A bytes splits into a run of 255 and a run of one, so the count never overflows.

Sources: Project rle_demo.c and docs/results.txt

# 5. Which input gets smaller?

3:30–4:15. Ask this question out loud and allow about 10–15 seconds for an answer: with two bytes for each stored run, which input gets smaller, AAAAAA or ABABAB? Let classmates explain their reasoning before moving to the next slide. A helpful follow-up is: how many runs does each input contain? Both inputs contain six bytes, so the difference comes entirely from the runs. Do not give the answer immediately. If nobody responds, ask everyone to count where a value changes. The point is that repeated patterns and long runs are different things.

Sources: Project rle_demo.c and docs/results.txt

# 6. RLE can make data larger

4:15–5:20. These are results from the C demo. AAAAAA is one run, so it uses two bytes and saves about 67 percent. ABABAB is six runs of length one. It uses twelve bytes, twice the original size. A pattern can repeat without producing useful RLE runs. The ten-byte example from earlier uses six encoded bytes. The rule for this format is that the average stored run must be longer than two bytes to save space. At exactly two, the size stays the same. A real application is an indexed bitmap with long stretches of one color. Microsoft documents RLE modes for 4-bit and 8-bit bitmaps. Real BMP formats also include literal and escape modes, so this toy encoder is not a complete BMP implementation.

Sources: https://learn.microsoft.com/en-us/windows/win32/gdi/bitmap-compression; project rle_demo.c and docs/results.txt

# 7. The main takeaway

5:20–6:00. RLE is simple: store a count and a value, then repeat the value when decoding. It is lossless because the original sequence can be reconstructed exactly. The limitation is the cost of storing counts. The example shows why choosing a data representation depends on what the data looks like. Long runs work well, while alternating values can double the payload. Before presenting, add your own genuine reflection about what surprised you, and one question you would explore next. One possible technical next question is how a literal mode handles data with few runs. Close by asking if anyone has questions. Be ready to explain the two-byte assumption and the difference between payload size and total memory.

Sources: https://www.cs.cmu.edu/afs/cs.cmu.edu/project/pscico-guyb/realworld/www/compression.pdf; project rle_demo.c

# 8. References

Backup reference slide. The explanation of runs follows Blelloch section 4.1. The application example follows Microsoft's official Bitmap Compression documentation. Numerical examples were calculated by the accompanying C program. This deck is an AI-assisted working draft for preparation. The course explicitly requires student-created slides, so Louis should recreate or independently reorganize the slides and explain the material in his own words before submission. Personal motivation and learning reflections must be based on his actual experience.

Sources: https://www.cs.cmu.edu/afs/cs.cmu.edu/project/pscico-guyb/realworld/www/compression.pdf; https://learn.microsoft.com/en-us/windows/win32/gdi/bitmap-compression
