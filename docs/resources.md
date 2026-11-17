# References

- Guy E. Blelloch, *Introduction to Data Compression*, section 4.1, Run-length Coding, Carnegie Mellon University. Explains replacing adjacent equal values with a value and a count. https://www.cs.cmu.edu/afs/cs.cmu.edu/project/pscico-guyb/realworld/www/compression.pdf
- Microsoft Learn, *Bitmap Compression*. Documents RLE8 and RLE4, count/color-index pairs, escape codes, and absolute modes. https://learn.microsoft.com/en-us/windows/win32/gdi/bitmap-compression
- Microsoft Open Specifications, *Run-Length Encoding (RLE) Compression*. Describes expansion by repeating a value according to its run count. https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/b05fc2f2-ad74-41f0-88ee-55ed5c36aad2

All numeric examples in this project come from `rle_demo.c`. The two-byte teaching format is defined by this project. It does not implement the complete formats in the Microsoft references.
