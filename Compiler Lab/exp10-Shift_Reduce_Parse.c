#include <stdio.h>
#include <string.h>

// --- Global Variables ---
int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];

// --- Function Prototype ---
void check(); // This function attempts to perform a reduction.

// --- Main Function ---
int main()
{
    // Display the grammar being used by this parser.
    puts("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id");
    puts("Enter input string:");
    scanf("%s", a);
    c = strlen(a);
    strcpy(act, "SHIFT->"); // Default action is SHIFT.

    puts("stack \t input \t action");

    // Main parsing loop: iterates through the input string, character by character.
    // 'j' is the input pointer, 'i' is the stack pointer.
    for (k = 0, i = 0, j = 0; j < c; k++, i++, j++)
    {
        // --- SHIFT Operation ---
        // Always shift the next input symbol onto the stack.
        // Special handling for "id" as it's two characters.
        if (a[j] == 'i' && a[j + 1] == 'd')
        {
            stk[i] = a[j]; stk[i + 1] = a[j + 1]; stk[i + 2] = '\0';
            a[j] = ' '; a[j + 1] = ' '; // "Consume" input by replacing it with spaces.
            printf("\n$%s\t%s$\t%sid", stk, a, act);
            j++; // Manually advance input pointer an extra step for 'd'.
            check(); // After every shift, check if a reduction is possible.
        }
        else // Handling for single character terminals like '+', '*', '(', ')'.
        {
            stk[i] = a[j]; stk[i + 1] = '\0';
            a[j] = ' ';
            printf("\n$%s\t%s$\t%ssymbol", stk, a, act);
            check(); // After every shift, check if a reduction is possible.
        }
    }

    // --- Final Check ---
    // After the loop, if the stack contains only the start symbol 'E' and input is empty,
    // the parsing is successful.
    if (strcmp(stk, "E") == 0)
    {
        printf("\n\nString Accepted.\n");
    }
    else
    {
        printf("\n\nString Rejected.\n");
    }

    return 0;
}


// --- REDUCE Operation ---
// This function greedily checks the top of the stack for a handle (a sequence matching a rule's RHS)
// and performs a reduction if one is found.
// Note: This is a very simplified and potentially buggy implementation. A real parser uses a table.
void check()
{
    strcpy(ac, "REDUCE TO E");
    // Loop to keep reducing as long as possible (e.g., id+id*id -> E+id*id -> E+E*id -> E*id -> E*E -> E)
    for(int l=0; l < c; l++) {
        // Rule: E -> id
        // strstr finds a substring. We check if "id" is at the top of the stack.
        if (strstr(stk, "id")) {
            // Replace "id" with "E"
            char* pos = strstr(stk, "id");
            *pos = 'E';
            *(pos+1) = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i--; // Stack size decreases by 1 ('i','d' -> 'E').
        }
        // Rule: E -> E + E
        if (strstr(stk, "E+E")) {
            char* pos = strstr(stk, "E+E");
            *pos = 'E';
            *(pos+1) = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i -= 2; // Stack size decreases by 2.
        }
        // Rule: E -> E * E
        if (strstr(stk, "E*E")) {
            char* pos = strstr(stk, "E*E");
            *pos = 'E';
            *(pos+1) = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i -= 2;
        }
        // Rule: E -> (E)
        if (strstr(stk, "(E)")) {
            char* pos = strstr(stk, "(E)");
            *pos = 'E';
            *(pos+1) = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i -= 2;
        }
    }
}

/*
---------------------------------
ALGORITHM
---------------------------------
1.  Start with an empty stack and the input string in a buffer, with a pointer at the beginning.
2.  Loop until the input buffer is empty and the stack contains only the start symbol.
3.  At each step, decide on an action: SHIFT or REDUCE.
    a. **SHIFT:** Move the next input symbol from the buffer to the top of the stack. Advance the input pointer.
    b. **REDUCE:**
       i.  Look at the top of the stack for a sequence of symbols that matches the right-hand side (RHS) of a grammar rule. This matching sequence is called a "handle".
       ii. If a handle is found, "pop" all the symbols of the handle from the stack.
       iii. "Push" the non-terminal from the left-hand side (LHS) of that rule onto the stack.
4.  This specific C code simplifies the decision: it ALWAYS shifts one symbol, then checks if ANY possible reduction can be made on the new stack top.
5.  **ACCEPT:** If the input is empty and the stack contains only the start symbol (e.g., "E"), the string is accepted.
6.  **ERROR:** If no valid action (shift or reduce) can be made, or if the input is empty but the stack is not in the accept state, the string is rejected.
*/