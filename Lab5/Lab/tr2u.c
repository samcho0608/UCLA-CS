#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error_msg(char* msg)
{
    write(2, msg, strlen(msg));
    exit(1);
}

int main(int argc, const char** argv)
{
    const char* from = argv[1];
    const char* to = argv[2];
    char* c = (char*)malloc(sizeof(char));
    int i;

    if(argc != 3)
        error_msg("Illegal Number of Arguments\n");
    

    if(strlen(from) != strlen(to))
        error_msg("From and To Are of Different Length.\n");

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
            error_msg("Duplicate Detected.\n");
    }

    while(read(0, c, 1) > 0)
    {
        for(i = 0; from[i] != '\0'; i++)
        {
            if(*c == from[i])
                *c = to[i];
        }
        write(1, c, 1);
    }
    free(c);
    return 0;
}