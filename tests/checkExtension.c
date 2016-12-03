
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) 
{

  char filename[255];
  char *r;
  char lastTok[64];

  strcpy(filename, "file.bas.bleh");
  printf("Processing %s\n", filename);
  
  r = strtok(filename, ".");
  
  // check again because if r is null next time it means its only a single word for a filename
  r = strtok(NULL, ".");
  
  if(r == NULL) 
    {
      printf("No valid file extension found, exiting.\n");
      return 1;
    }
  else 
    {    
      printf("r is: %s\n", r);
      
      while (r != NULL)
	{
	  strcpy(lastTok, r);
	  r = strtok(NULL, ".");
	  printf("r is: %s\n", r);
	}
      
      printf("last token was: %s\n", lastTok);
    }
  
  
  // now check for .bas extension
  if(strcmp(lastTok, "bas") != 0) 
    {
      printf("File extension is not .bas, exiting.\n");
      return 1;
    }
  else
    {
      printf("File extension is .bas, and valid.\n");
      return 0;
    }
  
}


