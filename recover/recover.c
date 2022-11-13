#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check for 1 argument
    if (argc != 2)
    {
        printf("Usage: ./recover input.raw\n");
        return 1;
    }

    // open memory card > File *f = fopen(filename, "r")
    FILE *card = fopen(argv[1], "r");
    // check card is read
    if (argv[1] == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // create variables
    unsigned char buffer[512];
    const int BLOCK_SIZE = 512;
    int count = 0;
    char filename[8];
    // create pointer for files to be written
    FILE *img;

    // repeat until end of card:
    // read 512 bytes into a buffer
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // if the buffer is the start of a new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // create dynamic string called filename (###.jpg) and increment it with count
            sprintf(filename, "%03i.jpg", count);
            // if the  buffer is the 1st jpeg, open new file and write block to it
            if (count == 0)
            {
                img = fopen(filename, "w");
                fwrite(buffer, BLOCK_SIZE, 1, img);
                count++;
            }
            // if there is already a jpeg, close the open file then create a new file and write block to it
            else
            {
                fclose(img);
                img = fopen(filename, "w");
                fwrite(buffer, BLOCK_SIZE, 1, img);
                count++;
            }
        }
        // if there is already a jpeg, write next block to open file
        else
        {
            if (count > 0)
            {
                fwrite(buffer, BLOCK_SIZE, 1, img);
            }
        }
    }
    // close open files
    fclose(img);
    fclose(card);
}