
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  lineNumber = 0;
int  lastLineNumber = 0;
  


void interpretError(int lineNumber)
{
  printf("Error parsing line: %i, exiting.\n", lineNumber);
  exit (1);
}


// PRINT opcode
int opcode_PRINT(char *arg)
{
  /*
   * Rules for PRINT opcode.
   * Might have semicolon for newline
   * Might have variables to print out also
   * Must have double quotes around argument
   * Must be in format 10 PRINT "TEST"
   * Doesn't need to have any text to print
   * But could still be printing a variable (check variable is defined)
   */
  
  char *tok;
  char *p;
  int newline = 0;
  int n = 0;
  int isNotNumber = 0;
  
  //printf("arguments are: %s\n", arg);
  // check if theres a ; for newline
  p = strchr(arg, ';');
  if(p != NULL)
    newline = 1;
  else
    newline = 0;
  
  // strip out argument from quotes
  tok = strtok(arg, "\"");
  //printf("tok is: %s\n", tok);
  printf("%s", tok);
  
  // check for variables on end, just print for now
  tok = strtok(NULL, " ");
  // ?
  tok = strtok(NULL, " ");
  printf(" ");
  
  // check if variable $bleh - could be a number though! i.e no $
  if (tok != NULL) 
    {
      p = strchr(tok, '$');
      if(p != NULL)
	{
	  //printf("tok is: %s\n", tok);
	  printf("%s", tok);
	}
      else
	{
	  // if for example PRINT "hello" bleh
	  // but what about numbers?
	  interpretError(lineNumber);
	}
    }

  if (newline == 1)
    printf("\n");

  return 0;
}





int main(int argc, char **argv) 
{
  
  char line[256];
  char *tok;
  char opcode[64];
  int  r;
  
  strcpy(line, "10 PRINT \"HELLO\"; $NAME");
  printf("Parsing line: %s\n", line);
  
  // get line number
  tok = strtok(line, " ");
  //printf("tok is: %s\n", tok);
  
  // could do with checking line number IS actually a number and not just garbage
  lineNumber = atoi(tok);
  //printf("lineNumber is: %i\n", lineNumber);
  
  // get next part of line
  tok = strtok(NULL, " ");
  //printf("tok is: %s\n", tok);
  if (strcmp(tok, "PRINT") == 0) 
    {
      //printf("opcode is PRINT\n");
      // get argument(s), pass rest of line minus line number and opcode in to PRINT function
      tok = strtok(NULL, "");
      //printf("tok is: %s\n", tok);
      r = opcode_PRINT(tok);
      // check it worked ok
      if (r != 0) 
	interpretError(lineNumber);
    }
  else
    interpretError(lineNumber);
  
  return 0;

}


