#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- Global Variables ---
char input[10]; // Stores the input string from the user.
int i;          // A global index that acts as a pointer to the current character in the input string.
int error;      // A flag to indicate if a syntax error has been found. 0 = no error, 1 = error.

// --- Function Prototypes ---
// Each function corresponds to a non-terminal in the grammar.
// The grammar used here is:
// E -> T E'
// E' -> + T E' | ε (epsilon/empty)
// T -> F T'
// T' -> * F T' | ε
// F -> (E) | id
void E();
void T();
void Eprime();
void Tprime();
void F();

// --- Main Function ---
int main() {
    i = 0;      // Initialize index to the start of the string.
    error = 0;  // Initialize error flag to 0.

    printf("Enter an arithmetic expression : "); // E.g., a+a*a
    // Note: gets() is unsafe. For a real application, fgets(input, 10, stdin) would be better.
    gets(input);

    E(); // Start the parsing process from the grammar's start symbol 'E'.

    // After parsing, check if we have consumed the entire string (strlen(input) == i)
    // AND if no error was flagged.
    if (strlen(input) == i && error == 0) {
        printf("\nAccepted..!!!\n");
    } else {
        printf("\nRejected..!!!\n");
    }
    return 0;
}

// --- Grammar Rule Functions ---

// Function for E -> T E'
// This function implements the rule for an Expression.
void E() {
    T();      // An expression must start with a Term.
    Eprime(); // Followed by whatever E' (E-prime) expands to.
}

// Function for E' -> + T E' | ε
// This handles the part of the expression after the first term (e.g., "+ a*a").
void Eprime() {
    // If the current character is '+', it matches the '+ T E'' rule.
    if (input[i] == '+') {
        i++;      // Consume the '+' character.
        T();      // Look for the following Term.
        Eprime(); // Recursively call E' to handle more additions (like a+b+c).
    }
    // Otherwise, if the character is not '+', we assume the epsilon (ε) production.
    // In this case, we do nothing and simply return.
}

// Function for T -> F T'
// This function implements the rule for a Term.
void T() {
    F();      // A term must start with a Factor.
    Tprime(); // Followed by whatever T' (T-prime) expands to.
}

// Function for T' -> * F T' | ε
// This handles the part of a term after the first factor (e.g., "*a").
void Tprime() {
    // If the current character is '*', it matches the '* F T'' rule.
    if (input[i] == '*') {
        i++;      // Consume the '*' character.
        F();      // Look for the following Factor.
        Tprime(); // Recursively call T' to handle more multiplications (like a*b*c).
    }
    // Otherwise, assume the epsilon (ε) production and do nothing.
}

// Function for F -> (E) | id
// This function implements the rule for a Factor.
void F() {
    // Check if the current character is a letter or a digit.
    if (isalnum(input[i])) {
        i++; // Consume the 'id' character.
    }
    // Check if the current character is an opening parenthesis.
    else if (input[i] == '(') {
        i++; // Consume the '('.
        E(); // An entire new expression must be found inside the parentheses.
        // After the inner expression is parsed, we must find a closing parenthesis.
        if (input[i] == ')') {
            i++; // Consume the ')'.
        } else {
            error = 1; // If ')' is not found, it's a syntax error.
        }
    }
    // If the character is neither an id nor '(', it's an invalid start for a Factor.
    else {
        error = 1; // Set the error flag.
    }
}

/*
---------------------------------
ALGORITHM
---------------------------------
1.  Start the program. Initialize a global index `i` to 0 and an error flag to 0.
2.  Get the input expression string from the user.
3.  Call the function for the start symbol, `E()`.
4.  Function `E()`:
    a. Calls `T()`.
    b. Calls `Eprime()`.
5.  Function `T()`:
    a. Calls `F()`.
    b. Calls `Tprime()`.
6.  Function `F()`:
    a. Checks the current character `input[i]`.
    b. If it is an alphabet or number (an 'id'), increment `i`.
    c. If it is `(`, increment `i`, call `E()`, and then check if the new `input[i]` is `)`. If not, set the error flag.
    d. If neither, set the error flag.
7.  Function `Eprime()`:
    a. Checks the current character `input[i]`.
    b. If it is `+`, increment `i`, call `T()`, and then call `Eprime()` again (recursion).
    c. If it is not `+`, do nothing (this is the epsilon case).
8.  Function `Tprime()`:
    a. Checks the current character `input[i]`.
    b. If it is `*`, increment `i`, call `F()`, and then call `Tprime()` again (recursion).
    c. If it is not `*`, do nothing (epsilon case).
9.  After the initial call to `E()` finishes, check two conditions in `main`:
    a. Has the entire string been processed? (Is `i` equal to the length of the string?)
    b. Is the error flag still 0?
10. If both are true, print "Accepted". Otherwise, print "Rejected".
11. End the program.
*/