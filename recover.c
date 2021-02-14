#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Number of bytes in JPEG
const int BUFFER_SIZE = 512;

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command line argument for .raw file to restore
    if (argc != 2)
    {
        printf("Please input one argument, the .raw file\n");
        return 1;
    }
    
    // Opens file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    int file_count = 0;
    
    BYTE buffer[BUFFER_SIZE];
    FILE *output;
    while (fread(&buffer, BUFFER_SIZE, 1, input) == 1)
    {
        // Check the first 4 bytes to determine whether it denotes the start of a JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (file_count > 0)
            {
                fclose(output);
            }
            
            char output_name[8];
            sprintf(output_name, "%03d.jpg", file_count);
            output = fopen(output_name, "w");
            file_count ++;
            
            fwrite(buffer, BUFFER_SIZE, 1, output);
        }
        else if (file_count > 0)
        {
            fwrite(buffer, BUFFER_SIZE, 1, output);
        }
    }

    
}
