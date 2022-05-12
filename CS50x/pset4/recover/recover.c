#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Checking command line argument is passed or not
    if (argc != 2)
    {
        printf("Usage: %s image\n", argv[0]);
        return 1;
    }

    // Opening the memory card file
    FILE *file = fopen(argv[1], "r");

    // Null check
    if (file == NULL)
    {
        return 1;
    }

    // Open image file
    FILE *img = NULL;
    unsigned char buffer[512];
    int flag = 0, file_count = 0;

    // While size returned is 1
    while (fread(buffer, 512, 1, file) == 1)
    {
        // Checking header of JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            // If image already open, then close it
            if (flag == 1)
            {
                fclose(img);
            }
            // For the first time
            else
            {
                flag = 1;
            }

            // Creating new image file
            char filename[8];
            sprintf(filename, "%03i.jpg", file_count);
            img = fopen(filename, "w");
            file_count++;
        }

        // If image file is open, continue writing in it
        if (flag == 1)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    // Closing the memory card file
    fclose(file);

    return 0;

}
