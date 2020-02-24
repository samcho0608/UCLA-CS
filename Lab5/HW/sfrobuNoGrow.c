#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool f_option = false;

int frobcmp(char const * a, char const * b)
{
  char a_val, b_val;
  while(*a != ' ' && *b != ' ')
    {
      if(f_option)
      {
        a_val = toupper((*a) ^ 42);
        b_val = toupper((*b) ^ 42);
      }
      else
      {
        a_val = (*a) ^ 42;
        b_val = (*b) ^ 42;
      }
      //compare the characters
      if(a_val < b_val)
	return -1;
      else if(a_val != b_val)
	return 1;

      // move to the next character
      a++;
      b++;
    }

  if(*a == ' ' && *b == ' ')
    return 0;
  else if(*a != ' ')
    return 1;
  else
    return -1;
}

int cmp(const void * a, const void * b)
{
  return frobcmp(*(char**) a, *(char**) b);
}

void error_msg(char* msg)
{
  write(2, msg, strlen(msg));
  exit(1);
}

void allocError(void * ptr)
{
  if(ptr == NULL)
      error_msg("Error allocating memory");
}


int main(int argc, char** argv)
{
  if(argc > 2) error_msg("Too Many Arguments.\n");

  if(argc == 2)
  {
    if(argv[1][0] == '-' && argv[1][1] == 'f')
      f_option = true;
    else
      error_msg("Invalid Arguments.\n");
  }
    

  struct stat buf;
  if(fstat(0, &buf) < 0) error_msg("Error with system call.\n");

  char* fcontent;
  size_t file_size = 0;

  file_size = buf.st_size;
  fcontent = (char*) malloc(sizeof(char) * (file_size + 1));
  allocError(fcontent);

  // read in data but if error detected, exit with a msg
  if(read(0, fcontent, file_size) < 0)
    error_msg("Error reading standard input.");
  fcontent[file_size] = ' ';
  
  char* word = NULL;
  int wordsize = 0;
  char** wordlist = NULL;
  int wordlistsize = 0;
  char prev = ' ';


  int findex;
  for(findex = 0; findex < file_size + 1; findex++)
  {
    // if prev char was a space
    if(prev == ' ')
    {
      // if repeated space, skip
      if(fcontent[findex] == ' ')
        continue;
      // if non-space char met,
      // begin a word
      else
      {
        word = &(fcontent[findex]);
        wordsize++; 
      }
    }
    // if prev char was not a space
    else
    {
      // if space met, end word and add to list
      if(fcontent[findex] == ' ')
      {
        wordlist = (char**) realloc(wordlist, (wordlistsize + 1) *sizeof(char*));
        wordlist[wordlistsize++] = word;
        word = NULL;
        wordsize = 0;
      }
      else
        wordsize++;
      
    }
    
    prev = fcontent[findex];
  }

  // sort wordlist
  qsort(wordlist, wordlistsize, sizeof(char*), cmp);
  int i, j;
  for(i = 0; i < wordlistsize; i++)
  {
    for(j = 0; wordlist[i][j] != ' ';j++){}
    write(1, wordlist[i], j + 1);
  }
  
  free(fcontent);
  free(wordlist);
  
  return 0;
}
