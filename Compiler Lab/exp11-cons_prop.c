#include<stdio.h>
#include<string.h>
#include<ctype.h>

// --- Function Prototypes ---
void input();
void output();
void change(int p, char *res); // Propagates a constant value forward.
void constant();              // Performs constant folding and propagation.

// --- Data Structures ---
// A structure to hold a single three-address code expression.
struct expr {
    char op[2], op1[5], op2[5], res[5];
    int flag; // A flag to mark if this expression has been optimized away (1=optimized, 0=not optimized).
} arr[10];

int n; // Global variable to store the number of expressions.

// --- Main Function ---
void main() {
    input();    // Read the input expressions.
    constant(); // Perform the optimization.
    output();   // Print the optimized code.
}

// --- Input Function ---
void input() {
    int i;
    printf("\n\nEnter the maximum number of expressions : ");
    scanf("%d", &n);
    printf("\nEnter the input : \n");
    for (i = 0; i < n; i++) {
        // Read the four parts of the expression: op op1 op2 res
        scanf("%s", arr[i].op);
        scanf("%s", arr[i].op1);
        scanf("%s", arr[i].op2);
        scanf("%s", arr[i].res);
        arr[i].flag = 0; // Initialize flag to 0.
    }
}

// --- Constant Folding and Propagation Function ---
void constant() {
    int i;
    int op1, op2, res;
    char op, res1[5];
    for (i = 0; i < n; i++) {
        // Check if the expression can be evaluated at compile time.
        // This happens if both operands are digits (constant folding)...
        // ...or if it's a simple assignment of a constant (constant propagation).
        if ((isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0])) || (strcmp(arr[i].op, "=") == 0 && isdigit(arr[i].op1[0]))) {

            // Convert the string operands to integers.
            op1 = atoi(arr[i].op1);
            op2 = atoi(arr[i].op2);
            op = arr[i].op[0];

            // --- CONSTANT FOLDING ---
            // Perform the calculation based on the operator.
            switch (op) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
                case '=': res = op1;       break;
            }

            // Convert the integer result back to a string.
            sprintf(res1, "%d", res);

            // Mark this expression as optimized. It will not be printed in the output.
            arr[i].flag = 1;

            // --- CONSTANT PROPAGATION ---
            // Now, substitute this result in all subsequent expressions.
            change(i, res1);
        }
    }
}

// --- Output Function ---
void output() {
    int i = 0;
    printf("\nOptimized code is : ");
    for (i = 0; i < n; i++) {
        // Only print the expressions that were NOT optimized away.
        if (!arr[i].flag)
            printf("\n%s %s %s %s", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
    }
}

// This function propagates the constant.
// It takes the position 'p' of the optimized expression and the constant result 'res'.
void change(int p, char *res) {
    int i;
    // Iterate through all expressions that come AFTER the current one.
    for (i = p + 1; i < n; i++) {
        // If the result of our optimized expression (arr[p].res) is used as an operand
        // in a subsequent expression, replace it with the constant value.
        if (strcmp(arr[p].res, arr[i].op1) == 0)
            strcpy(arr[i].op1, res);
        else if (strcmp(arr[p].res, arr[i].op2) == 0)
            strcpy(arr[i].op2, res);
    }
}


/*
---------------------------------
ALGORITHM
---------------------------------
1.  Start. Define a structure to hold three-address code statements.
2.  **Input Phase:**
    a. Ask the user for the number of expressions, `n`.
    b. Read `n` expressions, each consisting of an operator, two operands, and a result variable. Store them in an array of structures.
    c. Initialize a `flag` for each expression to 0 (not optimized).
3.  **Optimization Phase (`constant()` function):**
    a. Loop through each expression `i` from 0 to `n-1`.
    b. Inside the loop, check if an expression can be optimized. The condition is:
       i.  Are both operands `op1` and `op2` numbers? (This is for **Constant Folding**).
       ii. OR is the operator `=` and the first operand `op1` a number? (This is for **Constant Propagation**).
    c. If the condition is true:
       i.  Convert the string operands to integers.
       ii. Perform the arithmetic operation (`+`, `-`, `*`, `/`, `=`).
       iii. Convert the integer result back into a string.
       iv. Set `arr[i].flag = 1` to mark this statement for deletion.
       v.  Call the `change(i, result_string)` function to propagate this new constant.
4.  **Propagation Phase (`change()` function):**
    a. Loop through all subsequent expressions `j` from `i+1` to `n-1`.
    b. Check if the result variable of the original expression (`arr[i].res`) is used as either `op1` or `op2` in expression `j`.
    c. If it is, replace that operand in expression `j` with the new constant `result_string`.
5.  **Output Phase:**
    a. Loop through all expressions `i` from 0 to `n-1`.
    b. If `arr[i].flag` is 0 (meaning it wasn't optimized away), print the expression.
6.  End.
*/
