#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCKSIZE 512

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open memory card//
    FILE *card = fopen(argv[1], "r");
    if (!card)
    {
        printf("Invalid file\n");
        return 1;
    }

    //jpeg number counter//
    int jpegno = 0;

    //buffer array//
    typedef uint8_t BYTE;
    BYTE buffer[BLOCKSIZE];

    //jpeg name array//
    char outfile[8];

    //output file pointer//
    FILE *img;

    //read 512 bytes into a buffer//
    while (fread(buffer, sizeof(buffer), 1, card) == 1)
    {
        //if start of a new jpeg//
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if first JPEG//
            if (jpegno == 0)
            {
                sprintf(outfile, "%03i.jpg", jpegno);
                img = fopen(outfile, "w");
                fwrite(buffer, sizeof(buffer), 1, img);

                jpegno++;

            }
            //if not first jpeg//
            else
            {
                //close the file that you have just been writting to//
                fclose(img);

                //open up new file//
                sprintf(outfile, "%03i.jpg", jpegno);
                img = fopen(outfile, "w");
                fwrite(buffer, sizeof(buffer), 1, img);

                jpegno++;
            }
        }
        //if already found jpeg//
        else if (jpegno != 0)
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }
    }
    //close any remaining files//
    fclose(img);
    fclose(card);
    return 0;
}