%{
// C code section.
#include <stdio.h>
#include <stdlib.h>

int op = 0;          // Stores the current operation (1 for +, 2 for -, etc.). A value of 0 means no operation is pending.
float a = 0, b = 0, n, i; // 'a' is the accumulator/result, 'b' is the second operand.
%}

// Definitions section for Lex.
// 'digit' is a named regular expression for floating point or integer numbers.
digit [0-9]+|[0-9]*"."[0-9]+
// We can give names to simple patterns for clarity.
add "+"
sub "-"
mul "*"
div "/"
pow "^"
end "\n"

%%
// Rules section.

// When a number is matched...
{digit} {
    // If 'op' is 0, it means we are expecting the first number of a pair.
    if(op == 0) {
        a = atof(yytext); // atof() converts the string in yytext to a float and stores it in 'a'.
    } else {
        // If 'op' is not 0, an operator has just been seen, so this is the second number.
        b = atof(yytext); // Convert and store in 'b'.
        // Perform the pending operation based on the value of 'op'.
        switch(op) {
            case 1: a = a + b; break; // Addition
            case 2: a = a - b; break; // Subtraction
            case 3: a = a * b; break; // Multiplication
            case 4: a = a / b; break; // Division
            case 5: // Power calculation
                i = 1;
                n = a;
                while(i < b) {
                    a = a * n;
                    i++;
                }
                break;
        }
        op = 0; // Reset the operation to 0, indicating the calculation is done and we are ready for a new first number.
    }
}

// When an operator is matched, set the 'op' variable to a corresponding number.
// The action here doesn't do any calculation; it just remembers which operation to perform next.
{add} { op = 1; }
{sub} { op = 2; }
{mul} { op = 3; }
{div} { op = 4; }
{pow} { op = 5; }

// When a newline is encountered, it signals the end of the expression.
{end} { printf("Result is %f\n", a); exit(0); }

// Any other character is invalid; print an error and exit.
.     { printf("Invalid character\n"); exit(0); }

%%

int main() {
    printf("Enter the equation:\n");
    yylex(); // Start the lexical analysis (which also performs the calculation).
    return 0;
}

int yywrap() {
    return 1;
}

/*
---------------------------------
ALGORITHM
---------------------------------
1.  Start the program. Initialize a result variable `a` and an operation flag `op` to 0.
2.  Call `yylex()` to start processing the input.
3.  `yylex()` reads the input and matches tokens:
    a. If a **number** is matched:
       i.  Check the `op` flag.
       ii. If `op` is 0, it's the first number. Convert it to a float and store it in `a`.
       iii. If `op` is not 0, it's the second number. Convert it to a float `b`, perform the operation (`a = a op b`), and reset `op` to 0.
    b. If an **operator** (+, -, *, /) is matched:
       i.  Set the `op` flag to a corresponding value (e.g., 1 for '+', 2 for '-', etc.) to remember the operation.
    c. If a **newline** is matched:
       i.  Print the final result stored in `a`.
       ii. Exit the program.
    d. If any other character is matched, it's an error. Exit.
4.  The program continues this cycle of reading number -> operator -> number -> ... until a newline is entered.
*/