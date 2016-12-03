
/*
 * kernbasic - a simple basic interpreter
 * kernow 15/2/2011
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kernbasic_version 0.1


// nasty globals
int lineNumber = 0;
int lastLineNumber = 0;


// check file extension for .bas or exit
int checkFilename(char *filename) 
{  
  char *r;
  char lastTok[64];
  
  //printf("Processing %s\n", filename);
  
  r = strtok(filename, ".");
  
  //check again because if r is null next time it means its only a single word for a filename
    r = strtok(NULL, ".");
       
  if(r == NULL) 
    {
      printf("No valid file extension found, exiting.\n");
      return 1;
    }
  else 
    {    
      //printf("r is: %s\n", r);
           
      while (r != NULL)
	{
	  strcpy(lastTok, r);
	  r = strtok(NULL, ".");
	  //printf("r is: %s\n", r);
	}
      
      //printf("last token was: %s\n", lastTok);
    }
    
  // now check for .bas extension
  if(strcmp(lastTok, "bas") != 0) 
    {
      printf("File extension is not .bas, exiting.\n");
      return 1;
    }
  else
    {
      // valid .bas filename
      return 0;
    }
}


void interpretError(int lineNumber)
{
  
    printf("Error parsing line: %i, exiting.\n", lineNumber);
    exit (1);
}




// END opcode
void opcode_END()
{
  printf("hello?\n");
  exit(0);
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
    
  if (newline == 1)
    printf("\n");
  
  return 0;
}


void parseLine(char *currentLine)
{
  
  char *tok;
  char opcode[64];
  int  r;
  
  if(strcmp(currentLine, "\n") != 0)
    {
      //printf("Parsing line: %s\n", currentLine);
      
      // get line number
      tok = strtok(currentLine, " ");
      printf("tok is: %s\n", tok);
      
      // could do with checking line number IS actually a number and not just garbage
      lineNumber = atoi(tok);
      //printf("lineNumber is: %i\n", lineNumber);
      // get next part of line
      tok = strtok(NULL, " ");
      printf("tok is: %s\n", tok);
      if (strcmp(tok, "END") == 0)
	{
	  printf("opcode is END\n");
	  opcode_END();
	}
      
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
    }
  
}





interpret(char *filename) 
{
  FILE *f;
  char basicFile[256];
  int total_lines = 0;
  char line[256]; // our line buffer
  
  // check file actually exists before doing anything
  f = fopen(filename, "r");
  if(!f)
    {
      printf("Error reading \'%s\', exiting.\n", filename);
      exit(1);
    }
  fclose(f);
  
  // preserve filename as it gets mangled in checkFilename while tokenizing
  strcpy(basicFile, filename);
  // check filename is .bas
  if (checkFilename(basicFile) != 0)
    exit(1);
  
  // if we are here, I guess we can keep interpreting, gulp
  //printf("Opening %s\n", filename);
  
  // open file, read mode, text
  f = fopen(filename, "r");
  if (!f) 
    {
      // error opening file
      printf("Error reading \'%s\', exiting.\n", filename);
      exit(1);
    }
  else 
    { 
      // read a line from the file
      while(fgets(line,sizeof(line),f) != NULL)
	{	  
	  if (strcmp(line, "\n") != 0) 
	    total_lines++;
	    // do we return or just let parseLine fail and exit on error?
	    parseLine(line);
	}
          
      fclose(f);
      
      //printf("Number of lines parsed: %i\n", total_lines);
    }
  
  //printf("Interpretation finished, exiting.\n");
  //printf("\n");
    
}



void printUsageInfo() 
{
  printf("kernbasic %1.1f", kernbasic_version);
  printf("\nUsage: kernbasic <file.bas>\n");
  printf("\n");
}


int main(int argc, char **argv) 
{

  // check command line arguments
  if(argc == 1) 
    {
      // no filename specified so just display usage and exit
      printUsageInfo();
    }
  else 
    {
      // interpret filename specifed
      interpret(argv[1]);
    }

}


