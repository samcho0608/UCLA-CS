#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const * a, char const * b)
{
  char a_val, b_val;
  while(*a != ' ' && *b != ' ')
    {
      a_val = (*a) ^ 42;
      b_val = (*b) ^ 42;
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

void allocError(void * ptr)
{
  if(ptr == NULL)
    {
      fprintf(stderr, "Error allocating memory");
      exit(2);
    }
}

int main()
{
  char * word = NULL;
  int wordsize = 0;
  char ** wordlist = NULL;
  int wordlistsize = 0;
  char prev, current = ' ';

  //putc(' ',stdin);

  while(1)
    {
      // in a loop, previous char is the 
      // current char of previous iteration
      prev = current;
      current = getchar();

      // if error reading char, exit with error
      if(ferror(stdin))
      	{
	        fprintf(stderr, "Error reading standard input.");
	        exit(1);
	      }

      // if it's end of the file, add the word
      if(feof(stdin))
	      {
	        if(word != NULL)
	          {
              word = (char*) realloc(word, (wordsize + 1) * sizeof(char));
              allocError(word);
              word[wordsize] = ' ';
              wordsize++;

	            wordlist = (char**)realloc(wordlist,(wordlistsize + 1)*sizeof(char*));
              allocError(wordlist);

              wordlist[wordlistsize] = word;
              wordlistsize++;
              word = NULL;
              wordsize = 0;
	            }
	         break;
        }
      
      // if repeated spaces, skip it
      if(prev == ' ' && current == ' ')
      	continue;

      // allocate memory
      word = (char*) realloc(word, (wordsize + 1) * sizeof(char));
      allocError(word);

      word[wordsize] = current;
      wordsize++;

      // if space met and word is already allocated
      if(current == ' ' && word != NULL)
      	{
          	  wordlist = (char**)realloc(wordlist,(wordlistsize + 1)*sizeof(char*));
	            allocError(wordlist);

	            wordlist[wordlistsize] = word;
          	  wordlistsize++;
          	  word = NULL;
        	    wordsize = 0;
  	    }

    }

  // sort wordlist
  qsort(wordlist, wordlistsize, sizeof(char*), cmp);

  int i, j;
  for(i = 0; i < wordlistsize; i++)
    {
      for(j = 0; wordlist[i][j] != ' '; j++)
      	printf("%c",wordlist[i][j]);
      printf(" ");
      free(wordlist[i]);
    }
  free(wordlist);
      
  return 0;
}
