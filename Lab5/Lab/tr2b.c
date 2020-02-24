#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char** argv)
{
    const char* from = argv[1];
    const char* to = argv[2];
    char c;
    int i;

    if(argc != 3)
    {
        fprintf(stderr, "Illegal Number of Arguments.\n");
        exit(1);
    }

    if(strlen(from) != strlen(to))
    {
        fprintf(stderr, "From and To are of different length.\n");
        exit(1);
    }

    char unique;
    int count, j;
    for(i = 0; from[i] != '\0'; i++)
    {
        count = 0;
        unique = from[i];
        for(j = 0; from[j] != '\0'; j++)
            if(unique == from[j])
                count++;
        if(count > 1)
        {
            fprintf(stderr, "Duplicate detected.\n");
            exit(1);
        }
    }

    while(!feof(stdin))
    {
       c = getchar();
       for(i = 0; from[i] != '\0'; i++)
       {
           if(c == from[i])
            c = to[i];
       }
       putchar(c);
       if(ferror(stdout))
       {
           fprintf(stderr,"Error with character output.\n");
           exit(1);
       }
    }
}