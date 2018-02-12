# PNMImageIO
Reads binary P5 (PGM) and P6 (PPM) PNM images into simple C++ structs that hold unsigned integers (much more readable than binary man).
Writes binary P5 and P6 PNM images from the same structs mentioned previously.

So far:

  - can read & write binary pgm images (RGB)
  - can read & write binary ppm images (Grayscale)
  - prints out a detailed report when reading or writing a pnm image
  - works well with "ImageJ" program
  
Next:

  - pnmio will be a namespace rather than a class
  - pnmio will have public helper functions to help further read the image data easier
