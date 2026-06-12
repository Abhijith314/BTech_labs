%{
// This section contains C code that will be copied verbatim to the generated C file.
#include<stdio.h>
// Global variables to count spaces, words, lines, and characters.
int sc=0,wc=0,lc=0,cc=0;
%}

%%
// Rules section for Lex. Each line is a pattern-action pair.

// Pattern: [\n] matches a newline character.
// Action: { lc++;} increments the line counter.
[\n] { lc++;}

// Pattern: [ \t] matches a space or a tab character.
// Action: { sc++;} increments the space counter.
[ \t] { sc++;}

// Pattern: ([a-zA-Z0-9])* matches any sequence of letters and numbers. This represents a word.
// Action: { wc++; cc+=yyleng;} increments the word counter, and adds the length
// of the matched word (stored in the 'yyleng' variable) to the character counter.
([a-zA-Z0-9])* { wc++; cc+=yyleng;}
%%

// This is the C code section that is copied to the generated C file.
int main(int argc ,char* argv[ ])
{
 printf("Enter the input:\n");
 // yylex() is the main function in Lex that runs the lexical analyzer.
 // It reads input and executes the actions based on the rules above.
 yylex();
 // Print the final counts after yylex() has processed all input.
 printf("The number of lines=%d\n",lc);
 printf("The number of spaces=%d\n",sc);
 printf("The number of words=%d\n",wc);
 printf("The number of characters are=%d\n",cc);
}

// The yywrap() function is called by Lex when it reaches the end of the input file.
// Returning 1 tells Lex that we are done and the program can exit.
// If you were processing multiple files, you could open the next file here and return 0.
int yywrap( )
{
 return 1;
}

/*
---------------------------------
ALGORITHM
---------------------------------
1.  Start the Lex program.
2.  Initialize global integer counters for lines, words, spaces, and characters to zero.
3.  Lex starts its internal function `yylex()`.
4.  `yylex()` reads the input stream character by character and tries to match the longest possible sequence against the defined patterns.
    a. If the input sequence matches `\n`, it increments the `lc` counter.
    b. If the input sequence matches a space or a tab, it increments the `sc` counter.
    c. If the input sequence matches a word `([a-zA-Z0-9])*`, it increments the `wc` counter and adds the length of the word (`yyleng`) to the `cc` counter.
5.  This process repeats until the end of the input is reached.
6.  When the input ends, `yylex()` finishes.
7.  The `main` function then prints the final values of all the counters.
8.  End the program.
*/