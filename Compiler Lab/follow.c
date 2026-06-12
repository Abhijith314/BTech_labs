#include<stdio.h>
#include<ctype.h>
#include<string.h>

// Global variables
int n, m = 0, i = 0, j = 0;  // `n` is number of productions, `m` is index in FOLLOW set array
char a[10][10], f[10];        // `a` stores productions, `f` stores FOLLOW set

// Function declarations
void follow(char c);
void first(char c);

int main() {
    int i, z;
    char c, ch;

    // Input: Number of productions
    printf("Enter the number of productions: ");
    scanf("%d", &n);

    // Input: Productions, use `$` to represent epsilon
    printf("Enter the productions (epsilon=$):\n");
    for(i = 0; i < n; i++) {
        scanf("%s%c", a[i], &ch); // Read each production rule
    }

    // Loop to find FOLLOW set for specified non-terminals
    do {
        m = 0; // Reset FOLLOW set index for each new symbol
        printf("Enter the element whose FOLLOW is to be found: ");
        scanf(" %c", &c); // Read symbol to find FOLLOW of

        follow(c); // Call FOLLOW function for the given symbol

        // Display the FOLLOW set for the symbol
        printf("FOLLOW(%c) = {", c);
        for(i = 0; i < m; i++) {
            printf("%c", f[i]);
        }
        printf("}\n");

        // Option to continue or stop
        printf("Do you want to continue (0/1)? ");
        scanf("%d%c", &z, &ch);
    } while(z == 1); // Repeat if user chooses to continue
}

// Function to calculate FOLLOW set of a given symbol
void follow(char c) {
    // If the symbol is the start symbol, add `$` to FOLLOW set
    if(a[0][0] == c) {
        f[m++] = '$';
    }

    // Loop through each production
    for(i = 0; i < n; i++) {
        // Check each character in production after the start symbol
        for(j = 2; j < strlen(a[i]); j++) {
            // If we find `c` in production
            if(a[i][j] == c) {
                // If `c` is followed by another symbol, find its FIRST set
                if(a[i][j + 1] != '\0') {
                    first(a[i][j + 1]);
                }

                // If `c` is at the end, find FOLLOW of the left-hand symbol
                if(a[i][j + 1] == '\0' && c != a[i][0]) {
                    follow(a[i][0]);
                }
            }
        }
    }
}

// Function to calculate FIRST set of a symbol and add it to FOLLOW set
void first(char c) {
    int k;

    // If `c` is a terminal, add it directly to FOLLOW set
    if(!isupper(c)) {
        f[m++] = c;
    }
    else {
        // Loop through productions to find FIRST set
        for(k = 0; k < n; k++) {
            if(a[k][0] == c) {
                // If production leads to epsilon, follow left-hand symbol
                if(a[k][2] == '$') {
                    follow(a[i][0]);
                }
                // If next symbol is a terminal, add it to FOLLOW set
                else if(islower(a[k][2])) {
                    f[m++] = a[k][2];
                }
                // If next symbol is a non-terminal, recursively find its FIRST set
                else {
                    first(a[k][2]);
                }
            }
        }
    }
}



// Main
// Step 1: Enter the no of productions
// Step 2: Enter the productions
// Step 3: Enter element for whom the follow is to be found
// Step 4: Call Follow(c) on the character
// Step 5: Loop through the follow array and print one by one

// Follow()
// Step 1: If the symbol is start symbol then add $ to follow
// Step 2: Loop through each production
    // Step 2.1: Loop and Check the First letter of RHS (Start with 2nd index element since 1st and 2nd goes to the start and the equal symbols respectively)
        // Step 2.1.1 Loop until the character is matched
        // Step 2.1.2 If C is followed by another symbol then find its First()
        // Step 2.1.3 If C is at the end, then Find follow of the LHS


// First()
// Step 1: If the character is a terminal, then directly add to the follow set
// Step 2: Loop through each production to find the FIRST Set
    // Step 2.1:  if the start symbol of the production is the character then
        // Step 2.1.1: If the production leads to epsilon, do follow() on LHS
        // Step 2.1.2: If the symbol is a terminal, add it to Follow set
        // Step 2.1.3: If its a non terminal, do first() on it


/*

Output:
Enter the no of productions:3
Enter the productions(epsilon=$):
S=Aa
S=Ac
A=b
Enter the element whose FOLLLoW is to be found:S
FOLLOW(S)={$}
Do you want to continue(0/1)?1
Enter the element whose FOLLLoW is to be found:A
FOLLOW(A)={ac}
Do you want to continue(0/1)?0


*/