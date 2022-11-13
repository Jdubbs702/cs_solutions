Write a program to modify the volume of an audio file.

$ ./volume INPUT.wav OUTPUT.wav 2.0
Where INPUT.wav is the name of an original audio file and OUTPUT.wav is the name of an audio file with a volume that has been scaled by the given factor (e.g., 2.0).

WAV Files
WAV files are a common file format for representing audio. WAV files store audio as a sequence of “samples”: numbers that represent the value of some audio signal at a particular point in time. WAV files begin with a 44-byte “header” that contains information about the file itself, including the size of the file, the number of samples per second, and the size of each sample. After the header, the WAV file contains a sequence of samples, each a single 2-byte (16-bit) integer representing the audio signal at a particular point in time.

Scaling each sample value by a given factor has the effect of changing the volume of the audio. Multiplying each sample value by 2.0, for example, will have the effect of doubling the volume of the origin audio. Multiplying each sample by 0.5, meanwhile, will have the effect of cutting the volume in half.

Types
So far, we’ve seen a number of different types in C, including int, bool, char, double, float, and long. Inside a header file called stdint.h are the declarations of a number of other types that allow us to very precisely define the size (in bits) and sign (signed or unsigned) of an integer. Two types in particular will be useful to us in this lab.

uint8_t is a type that stores an 8-bit unsigned (i.e., not negative) integer. We can treat each byte of a WAV file’s header as a uint8_t value.
int16_t is a type that stores a 16-bit signed (i.e., positive or negative) integer. We can treat each sample of audio in a WAV file as an int16_t value.
Getting Started
Started CS50x in 2021 or prior and need to migrate your work from CS50 IDE to the new VS Code codespace? Be sure to check out our instructions on how to migrate your files!

Open VS Code.

Start by clicking inside your terminal window, then execute cd by itself. You should find that its “prompt” resembles the below.

$
Click inside of that terminal window and then execute

wget https://cdn.cs50.net/2021/fall/labs/4/volume.zip
followed by Enter in order to download a ZIP called volume.zip in your codespace. Take care not to overlook the space between wget and the following URL, or any other character for that matter!

Now execute

unzip volume.zip
to create a folder called volume. You no longer need the ZIP file, so you can execute

rm volume.zip
and respond with “y” followed by Enter at the prompt to remove the ZIP file you downloaded.

Now type

cd volume
followed by Enter to move yourself into (i.e., open) that directory. Your prompt should now resemble the below.

volume/ $
If all was successful, you should execute

ls
and you should see a volume.c file alongside an input.wav file.

If you run into any trouble, follow these same steps again and see if you can determine where you went wrong!

Implementation Details
Complete the implementation of volume.c, such that it changes the volume of a sound file by a given factor.

The program accepts three command-line arguments: input represents the name of the original audio file, output represents the name of the new audio file that should be generated, and factor is the amount by which the volume of the original audio file should be scaled.
For example, if factor is 2.0, then your program should double the volume of the audio file in input and save the newly generated audio file in output.
Your program should first read the header from the input file and write the header to the output file. Recall that this header is always exactly 44 bytes long.
Note that volume.c already defines a variable for you called HEADER_SIZE, equal to the number of bytes in the header.
Your program should then read the rest of the data from the WAV file, one 16-bit (2-byte) sample at a time. Your program should multiply each sample by the factor and write the new sample to the output file.
You may assume that the WAV file will use 16-bit signed values as samples. In practice, WAV files can have varying numbers of bits per sample, but we’ll assume 16-bit samples for this lab.
Your program, if it uses malloc, must not leak any memory.
