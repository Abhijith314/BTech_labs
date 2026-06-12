#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

// --- Global Variables ---
char productions[MAX][MAX];  // Stores the grammar productions (e.g., "E->E+T" is stored as "EE+T").
char firstResult[26][MAX];   // Stores the computed FIRST sets. Index corresponds to non-terminal ('A'=0, 'B'=1, etc.).
char followResult[26][MAX];  // Stores the computed FOLLOW sets.
int prodCount = 0;           // Number of productions.

// --- Helper Functions ---
// Checks if a character is a non-terminal (uppercase).
int isNonTerminal(char c) {
    return isupper(c);
}

// Adds a character 'val' to a set 'set' if it's not already present.
void addToSet(char set[], char val) {
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == val) return; // Already in the set.
    }
    int len = strlen(set);
    set[len] = val;
    set[len + 1] = '\0'; // Add the character and null-terminate.
}

// --- Core Logic: findFirst ---
// Computes the FIRST set for a given 'symbol' and stores it in 'result'.
void findFirst(char *result, char symbol) {
    // Rule 1: If symbol is a terminal, FIRST(symbol) is {symbol}.
    if (!isNonTerminal(symbol)) {
        addToSet(result, symbol);
        return;
    }

    // Optimization/Memoization: If FIRST set is already computed, just copy it.
    int idx = symbol - 'A';
    if (strlen(firstResult[idx]) != 0) {
        strcpy(result, firstResult[idx]);
        return;
    }

    // Iterate through all productions to find ones for the given 'symbol'.
    for (int i = 0; i < prodCount; i++) {
        if (productions[i][0] == symbol) { // Found a production for our symbol.
            // Rule 2: If production is X -> # (epsilon), add # to FIRST(X).
            if (productions[i][1] == '#') {
                addToSet(result, '#');
            } else {
                // Rule 3: If X -> Y1Y2...Yk, then FIRST(X) includes FIRST(Y1) (excluding epsilon).
                int j = 1;
                while (productions[i][j] != '\0') {
                    char tempFirst[MAX] = "";
                    findFirst(tempFirst, productions[i][j]); // Recursively find FIRST of the symbol on the RHS.

                    int hasEpsilon = 0;
                    // Add everything from FIRST(Yj) to our result.
                    for (int k = 0; tempFirst[k] != '\0'; k++) {
                        if (tempFirst[k] == '#') hasEpsilon = 1;
                        else addToSet(result, tempFirst[k]);
                    }

                    // If FIRST(Yj) does NOT contain epsilon, then we stop.
                    // FIRST(X) cannot contain anything from Yj+1.
                    if (!hasEpsilon) break;
                    j++;
                    // Rule 4: If FIRST(Y1)...FIRST(Yj-1) all contain epsilon, then FIRST(X) also includes FIRST(Yj).
                    // If we reach the end and all had epsilon, we add epsilon to FIRST(X).
                    if (productions[i][j] == '\0') addToSet(result, '#');
                }
            }
        }
    }
    // Store the computed set for future use (memoization).
    strcpy(firstResult[idx], result);
}

// --- Core Logic: computeAllFollow ---
void computeAllFollow() {
    // Rule 1: For the start symbol S, add $ (end of input marker) to FOLLOW(S).
    addToSet(followResult[productions[0][0] - 'A'], '$');

    int changed;
    do { // Repeat the process until no more changes are made to any FOLLOW set in a full pass.
        changed = 0;
        // Iterate through all productions A -> αBβ
        for (int i = 0; i < prodCount; i++) {
            char *prod = productions[i]; // Current production, e.g., "EE+T"
            int len = strlen(prod);
            // Iterate through the RHS of the production to find non-terminals.
            for (int j = 1; j < len; j++) {
                if (isNonTerminal(prod[j])) { // Found a non-terminal B at prod[j]
                    char *followSetB = followResult[prod[j] - 'A'];
                    int oldLen = strlen(followSetB);

                    // --- Apply Rule 2 ---
                    // For A -> αBβ, everything in FIRST(β) except '#' is in FOLLOW(B).
                    char *beta = &prod[j + 1];
                    if (*beta != '\0') { // Check if β exists.
                        char tempFirst[MAX] = "";
                        findFirst(tempFirst, *beta);
                        int hasEpsilon = 0;
                        for (int k = 0; tempFirst[k] != '\0'; k++) {
                            if (tempFirst[k] == '#') hasEpsilon = 1;
                            else addToSet(followSetB, tempFirst[k]);
                        }
                        // --- Apply Rule 3 ---
                        // If FIRST(β) contains '#', then everything in FOLLOW(A) is in FOLLOW(B).
                        if (hasEpsilon) {
                            char *followSetA = followResult[prod[0] - 'A'];
                            for (int k = 0; followSetA[k] != '\0'; k++) addToSet(followSetB, followSetA[k]);
                        }
                    } else {
                        // --- Apply Rule 3 (case A -> αB) ---
                        // Everything in FOLLOW(A) is in FOLLOW(B).
                        char *followSetA = followResult[prod[0] - 'A'];
                        for (int k = 0; followSetA[k] != '\0'; k++) addToSet(followSetB, followSetA[k]);
                    }
                    if (strlen(followSetB) > oldLen) changed = 1;
                }
            }
        }
    } while (changed);
}

// --- Main Driver Function ---
int main() {
    // ... (Input handling code) ...
    printf("Enter number of productions: "); scanf("%d", &prodCount); getchar();
    printf("Enter productions:\n");
    for (int i = 0; i < prodCount; i++) {
        printf("Production %d: ", i + 1);
        fgets(productions[i], MAX, stdin); productions[i][strcspn(productions[i], "\n")] = '\0';
        int len = strlen(productions[i]), j = 3, k = 1;
        while (j < len) { productions[i][k++] = productions[i][j++]; }
        productions[i][k] = '\0';
    }

    // --- Compute and Print FIRST sets ---
    printf("\nFIRST sets:\n");
    for (int i = 0; i < 26; i++) {
        if (isNonTerminal('A' + i)) {
            char temp[MAX] = "";
            findFirst(temp, 'A' + i);
            if (strlen(temp) > 0) {
                 printf("FIRST(%c) = { ", 'A' + i);
                 for(int j=0; temp[j]!='\0'; j++) printf("%c ", temp[j]);
                 printf("}\n");
            }
        }
    }

    // --- Compute and Print FOLLOW sets ---
    computeAllFollow();
    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < 26; i++) {
        if (strlen(followResult[i]) > 0) {
            printf("FOLLOW(%c) = { ", i + 'A');
            for (int j = 0; followResult[i][j] != '\0'; j++) printf("%c ", followResult[i][j]);
            printf("}\n");
        }
    }
    return 0;
}
/*
---------------------------------
ALGORITHM
---------------------------------
**To Calculate FIRST sets:**
1.  Initialize FIRST(X) for all symbols X to an empty set.
2.  For each terminal symbol `t`, FIRST(t) = {t}.
3.  Repeat until no more changes occur to any FIRST set:
    a. For each production `X -> Y1 Y2 ... Yk`:
       i.  Add FIRST(Y1) (excluding epsilon '#') to FIRST(X).
       ii. If FIRST(Y1) contains '#', add FIRST(Y2) (excluding '#') to FIRST(X).
       iii. Continue this for Y3, Y4... until a FIRST(Yi) does not contain '#'.
       iv. If all FIRST(Y1)...FIRST(Yk) contain '#', then add '#' to FIRST(X).
    b. For a production `X -> #`, add '#' to FIRST(X).

**To Calculate FOLLOW sets:**
1.  Initialize FOLLOW(X) for all non-terminals X to an empty set.
2.  Place '$' (end of input marker) in FOLLOW(S), where S is the start symbol.
3.  Repeat until no more changes occur to any FOLLOW set:
    a. For each production `A -> αBβ`:
       - Add everything in FIRST(β), except for '#', to FOLLOW(B).
    b. For each production `A -> αB` or `A -> αBβ` where FIRST(β) contains '#':
       - Add everything in FOLLOW(A) to FOLLOW(B).
*/