%{
// C code to be copied directly.
#include <stdio.h>
#include <stdlib.h>
%}

%%
// Rules section for Lex. The order of rules is important.
// Lex matches the longest possible string and, in case of a tie, the first rule listed.

// This rule uses the '|' (OR) operator to match any of the C keywords.
// It is placed before the identifier rule to ensure keywords are not mistaken for identifiers.
"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"     { printf("KEYWORD: %s\n", yytext); }

// This rule matches common preprocessor directives. '.*' matches any character until the end of the line.
"#define".*|"#include".*|"#undef".*	{ printf("Preprocessor Directive: %s\n", yytext); }

// This rule matches single-line comments.
"//".*						{ printf("Single-Line Comment: %s\n", yytext); }

// This complex rule matches multi-line comments:
// "/*"      : Matches the opening /*
// ([^*]|\*+[^*/])* : Matches any sequence of characters that are not a */
// \*+"/"    : Matches the closing */
"/*"([^*]|\*+[^*/])*\*+"/"			{ printf("Multi-Line Comment: %s\n", yytext); }

// This rule matches identifiers: starts with a letter or underscore,
// followed by zero or more letters, numbers, or underscores.
[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %s\n", yytext); }

// This rule matches integer numbers (one or more digits).
[0-9]+ 					{ printf("Number: %s\n", yytext); }

// This rule matches arithmetic operators. The '\' escapes the special meaning of operators like '+'.
\+|\-|\*|\/    				{ printf("Arithmetic Operator: %s\n", yytext); }

// This rule matches relational operators.
"<="|">="|"=="|"<"|">"    			{ printf("Relational Operator: %s\n", yytext); }

// This rule matches one or more whitespace characters (space, tab, newline).
// The action is empty, so it effectively ignores/skips them.
[ \t\n]+					/* ignore whitespace */

// This rule uses '.' (dot) to match any single character that wasn't matched by any of the rules above.
// It acts as a catch-all for special symbols.
. 						{ printf("Special Symbol: %s\n", yytext); }

%%

int main()
{
    FILE *file;
    // Open the input C file.
    file = fopen("input.c", "r");
    if (!file)
    {
        printf("Could not open the file\n");
        exit(1);
    }
    // 'yyin' is a global file pointer in Lex; setting it to our file redirects input from stdin to this file.
    yyin = file;
    // Start the lexical analysis.
    yylex();
    printf("\n");
    return 0;
}

int yywrap()
{
    return 1;
}

/*
---------------------------------
ALGORITHM
---------------------------------
1.  Start the program.
2.  In the `main` function, open the source file "input.c".
3.  Assign the file pointer to the special Lex variable `yyin` to redirect input.
4.  Call `yylex()`.
5.  `yylex()` begins reading from "input.c" and matches patterns in the following order of precedence:
    a. Tries to match the longest possible string.
    b. If two patterns match the same length string, the one listed first in the rules section wins.
6.  For each matched token:
    a. Check for keywords (e.g., "if", "while").
    b. Check for comments, preprocessor directives.
    c. Check for identifiers.
    d. Check for numbers and operators.
    e. Ignore all whitespace.
    f. Any single character that is left over is a special symbol.
7.  The corresponding `printf` action is executed for each token found.
8.  When the end of the file is reached, `yylex()` calls `yywrap()`, which returns 1, signaling completion.
9.  The `main` function continues and the program exits.
*/