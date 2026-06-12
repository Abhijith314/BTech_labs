#include <stdio.h>
#include <stdlib.h>

// --- Data Structures ---

// A linked list node to represent transitions in the NFA.
struct node {
    int st;           // The destination state.
    struct node *link; // Pointer to the next transition from the same state on the same symbol.
};

// A structure to represent a DFA state.
// A DFA state is conceptually a SET of NFA states.
// We represent this set using an array where the index is the NFA state number.
struct node1 {
    int nst[20]; // If nst[q] is non-zero, it means NFA state 'q' is in this DFA state set.
};

// --- Function Prototypes ---
void insert(int, char, int);      // Adds a transition to the NFA.
int findalpha(char);              // Finds the index for a given alphabet symbol.
void findfinalstate(void);        // Prints the final states of the generated DFA.
int insertdfastate(struct node1); // Adds a new state to the DFA if it's unique.
int compare(struct node1, struct node1); // Compares two DFA states to see if they are the same.
void printnewstate(struct node1); // Prints a DFA state set in a readable format.

// --- Global Variables ---
static int set[20], nostate, noalpha, s, notransition, nofinal, start, finalstate[20], r, buffer[20];
int complete = -1;                // Index of the last DFA state added to our table.
char alphabet[20], c;
struct node1 hash[20];            // Our DFA state table. 'hash' is a bit of a misnomer, it's just an array.
struct node *transition[20][20] = {NULL}; // NFA transition table.

// --- Main Function ---
int main() {
    int i, j, k, l;
    struct node *temp;
    struct node1 newstate = {0}, tmpstate = {0}; // Structures to hold DFA states.

    // --- Input Section ---
    // (User input for alphabets, states, start state, final states, and transitions)
    printf("Enter the number of alphabets?\n");
    scanf("%d", &noalpha); getchar();
    printf("\nEnter alphabets?\n");
    for (i = 0; i < noalpha; i++) { alphabet[i] = getchar(); getchar(); }
    printf("Enter the number of states?\n"); scanf("%d", &nostate);
    printf("Enter the start state?\n"); scanf("%d", &start);
    start = start + 1; // Adjusting for 1-based indexing used in the logic.
    printf("Enter the number of final states?\n"); scanf("%d", &nofinal);
    printf("Enter the final states?\n");
    for (i = 0; i < nofinal; i++) { scanf("%d", &finalstate[i]); finalstate[i] = finalstate[i] + 1; }
    printf("Enter no of transitions?\n"); scanf("%d", &notransition);
    printf("\nEnter transitions?\n");
    for (i = 0; i < notransition; i++) { scanf("%d %c %d", &r, &c, &s); insert(r + 1, c, s + 1); }

    // --- DFA Conversion Logic (Subset Construction) ---
    complete = -1; // No DFA states yet.
    i = -1;
    printf("\nEquivalent DFA.....\n");
    printf(".......................\n");
    printf("Transitions of DFA\n");

    // The start state of the DFA is the set containing just the NFA's start state.
    // (Note: This code does not handle epsilon closures. It's a simplified conversion.)
    newstate.nst[start] = start;
    insertdfastate(newstate); // Add this first DFA state to our table.

    // Process each new DFA state added to the table until no new states are generated.
    while (i != complete) {
        i++;
        newstate = hash[i]; // Get the current DFA state (a set of NFA states) to process.

        // For each alphabet symbol...
        for (k = 0; k < noalpha; k++) {
            int c_count = 0;
            for (j = 1; j <= nostate; j++) set[j] = 0; // Clear the temporary set for the next state.

            // For each NFA state 'l' within the current DFA state 'newstate'...
            for (j = 1; j <= nostate; j++) {
                l = newstate.nst[j];
                if (l != 0) { // If NFA state 'l' is in our current DFA state set...
                    // Find all possible transitions from NFA state 'l' on the current alphabet symbol.
                    temp = transition[l][k];
                    while (temp != NULL) {
                        // Add the resulting NFA state to our new set 'set'.
                        if (set[temp->st] == 0) {
                            c_count++;
                            set[temp->st] = temp->st;
                        }
                        temp = temp->link;
                    }
                }
            }
            printf("\n");
            if (c_count != 0) { // If there were any transitions...
                for (int m = 1; m <= nostate; m++) tmpstate.nst[m] = set[m]; // Copy 'set' to 'tmpstate'.
                insertdfastate(tmpstate); // Add this new set as a DFA state (if it's new).
                // Print the transition: current_DFA_state -> symbol -> new_DFA_state
                printnewstate(newstate);
                printf("%c\t", alphabet[k]);
                printnewstate(tmpstate);
                printf("\n");
            } else { // If no transitions, it goes to a dead state (represented as NULL here).
                printnewstate(newstate);
                printf("%c\t", alphabet[k]);
                printf("NULL\n");
            }
        }
    }

    // --- Output Section ---
    printf("\nStates of DFA:\n"); for (i = 0; i <= complete; i++) printnewstate(hash[i]);
    printf("\nAlphabets:\n"); for (i = 0; i < noalpha; i++) printf("%c\t", alphabet[i]);
    printf("\nStart State:\n"); printnewstate(hash[0]); // The first state we added is the start state.
    printf("\nFinal states:\n"); findfinalstate();
    return 0;
}

// Adds a new DFA state to the 'hash' table if it doesn't already exist.
int insertdfastate(struct node1 newstate) {
    for (int i = 0; i <= complete; i++) {
        if (compare(hash[i], newstate)) return 0; // State already exists.
    }
    complete++;
    hash[complete] = newstate; // Add the new state.
    return 1;
}

// Compares two DFA states (sets of NFA states) to see if they are identical.
int compare(struct node1 a, struct node1 b) {
    for (int i = 1; i <= nostate; i++) {
        if (a.nst[i] != b.nst[i]) return 0; // Not equal.
    }
    return 1; // Equal.
}

// Inserts a transition into the NFA's adjacency list transition table.
void insert(int r, char c, int s) {
    int j = findalpha(c);
    if (j == 999) { printf("error\n"); exit(0); }
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

int findalpha(char c) {
    for (int i = 0; i < noalpha; i++) if (alphabet[i] == c) return i;
    return 999;
}

// Determines and prints the final states of the DFA.
// A DFA state is final if its set of NFA states contains at least one of the original NFA's final states.
void findfinalstate() {
    for (int i = 0; i <= complete; i++) { // For each DFA state...
        for (int j = 1; j <= nostate; j++) { // For each NFA state 'j' in its set...
            for (int k = 0; k < nofinal; k++) { // For each original final state 'k'...
                if (hash[i].nst[j] == finalstate[k]) { // If 'j' is a final state...
                    printnewstate(hash[i]); // ...then this DFA state is final.
                    printf("\t");
                    goto next_dfa_state; // Use goto to avoid printing the same state multiple times.
                }
            }
        }
        next_dfa_state:; // Label for the goto jump.
    }
}

// Prints a DFA state set in a readable format, e.g., {q0, q1}.
void printnewstate(struct node1 state) {
    printf("{");
    for (int j = 1; j <= nostate; j++) {
        if (state.nst[j] != 0) printf("q%d,", state.nst[j] - 1);
    }
    printf("}\t");
}

/*
---------------------------------
ALGORITHM (Subset Construction)
---------------------------------
1.  Start. Get all NFA details (states, alphabet, transitions, start, final states).
2.  Create a list/table for the new DFA states, let's call it `Dstates`. Initially, it's empty.
3.  Create the first DFA state:
    a. This state is the set containing only the NFA's start state. (If handling epsilons, this would be the Epsilon-Closure of the start state).
    b. Add this new state to `Dstates`. Mark it as unprocessed.
4.  Loop while there are unprocessed states in `Dstates`:
    a. Pick an unprocessed DFA state `S` from `Dstates`.
    b. Mark `S` as processed.
    c. For each alphabet symbol `c`:
       i.  Create an empty set `move(S, c)`.
       ii. For each NFA state `q` in the set `S`:
           - Find all states that the NFA can transition to from `q` on symbol `c`.
           - Add all these resulting states to the set `move(S, c)`.
       iii. (If handling epsilons, you would now compute the Epsilon-Closure of the `move(S, c)` set).
       iv. If this new set is not empty and is not already in `Dstates`:
           - Add it to `Dstates` as a new, unprocessed state.
       v.  Record the transition: The DFA has a transition from state `S` to state `move(S, c)` on symbol `c`.
5.  After the loop finishes, determine the final states of the DFA: Any state in `Dstates` that contains at least one of the original NFA's final states is a final state in the DFA.
6.  End.
*/