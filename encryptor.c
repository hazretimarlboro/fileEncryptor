#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHUNK 4096

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("No input file specified!\n");
        return 1;
    }

    char* encoder = (char*) malloc(4096);
    if(!encoder)
    {
        perror("allocation error\n");
        return 1;
    }

    printf("Please enter the encoder string:\n");
    fgets(encoder,128,stdin);
    encoder[strcspn(encoder, "\n")] = '\0';

    if(!strlen(encoder))
    {
        printf("Encoder can not be empty!\n");
        free(encoder);
        return 1;
    }

    FILE* f = fopen(argv[1], "rb");
    if(!f)
    {
        free(encoder);
        perror("failed to open file\n");
        return 1;
    }

    FILE* newfile = fopen("encrypted", "wb");
    if(!newfile)
    {
        free(encoder);
        fclose(f);
        perror("failed to create output file\n");
        return 1;
    }

    unsigned char buffer[CHUNK];
    size_t bytesRead;
    long pos = 0;
    int size = strlen(encoder);

    while((bytesRead = fread(buffer,1,CHUNK,f)) > 0)
    {
        for(size_t i = 0; i < bytesRead; i++)
        {
            buffer[i] = buffer[i] ^ encoder[(pos + i) % size];
        }

        size_t bytesWritten = fwrite(buffer,1,bytesRead,newfile);
        if(bytesWritten != bytesRead)
        {
            perror("failed writing bytes!\n");
            free(encoder);
            fclose(f);
            fclose(newfile);
            return 1;
        }

        pos += bytesRead;
    }

    free(encoder);
    fclose(f);
    fclose(newfile);
    return 0;
}
