#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: exactly one command-line argument\n");
        return 1;
    }

    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    unsigned char buffer[512];
    char file_name[8];
    int file_no = -1;
    FILE *img;

    while (fread(&buffer, sizeof(buffer), 1, inptr) == 1){

        bool jpg = buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && ((buffer[3] & 0xf0) == 0xe0);

        if (jpg == true){
            if (file_no < 0){
                file_no++;
                sprintf(file_name, "%03i.jpg", file_no);

                img = fopen(file_name, "w");
                fwrite(&buffer,sizeof(buffer), 1, img);
            }

            else {
                fclose(img);

                file_no++;
                sprintf(file_name, "%03i.jpg", file_no);

                img = fopen(file_name, "w");
                fwrite(&buffer,sizeof(buffer), 1, img);

            }
        }

        if (jpg != true){
            if (file_no >= 0){
                fwrite(&buffer,sizeof(buffer), 1, img);
            }

        }

    }
    fclose(img);
    fclose(inptr);

}
