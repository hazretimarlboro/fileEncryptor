#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 4096

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("No input file specified!\n");
        return 1;
    }

    printf("Enter encoder string: ");
    char* encoder = malloc(4096);
    if(!encoder)
    {
        perror("allocation error\n");
        return 1;
    }
    fgets(encoder,128,stdin);
    encoder[strcspn(encoder, "\n")] = '\0';
    
    size_t lengencoder = strlen(encoder);
    if(lengencoder == 0)
    {
        printf("Encoder cannot be empty!\n");
        free(encoder);
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if(!file)
    {
        perror("couldn't open file\n");
        free(encoder);
        return 1;
    }

    FILE* f = fopen("decrypted", "wb");
    if(!f)
    {
        perror("file creation error!\n");
        fclose(file);
        free(encoder);
        return 1; 
    }

    unsigned char buffer[CHUNK];
    long pos = 0;
    size_t bytesRead;

    while((bytesRead = fread(buffer,1,CHUNK,file)) > 0)
    {
        for(size_t i = 0; i < bytesRead; i++)
        {
            buffer[i] ^= encoder[(pos + i) % lengencoder];
        }
        size_t bytesWritten = fwrite(buffer,1,bytesRead,f);
        if(bytesWritten != bytesRead)
        {
            perror("failed writing bytes!\n");
            fclose(file);
            fclose(f);
            free(encoder);
            return 1;
        }
        pos += bytesRead;
    }

    fclose(file);
    fclose(f);
    free(encoder);
    return 0;
}
