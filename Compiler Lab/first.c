#include<stdio.h>
#include<ctype.h>

// Function to find the FIRST set of a given non-terminal
void FIRST(char symbol);

// Global variables
int count, n = 0; // `count` for number of productions, `n` for index in first array
char prodn[10][10], first[10]; // Arrays to store productions and FIRST set

void main() {
    int i, choice;
    char c, ch;

    // Input: Number of productions
    printf("How many productions?: ");
    scanf("%d", &count);

    // Input: Productions, using $ to denote epsilon
    printf("Enter %d productions, use epsilon as $:\n", count);
    for(i = 0; i < count; i++) {
        scanf("%s%c", prodn[i], &ch); // Read each production
    }

    do {
        n = 0; // Reset `n` to store new FIRST set elements
        printf("Element: ");
        scanf(" %c", &c); // Input symbol to find FIRST set of

        FIRST(c); // Call FIRST function for the symbol `c`

        // Display the FIRST set for the symbol
        printf("\nFIRST(%c) = {", c);
        for(i = 0; i < n; i++) {
            printf("%c", first[i]);
        }
        printf("}\n");

        // Prompt to continue or stop
        printf("Press 1 to continue: ");
        scanf("%d%c", &choice, &ch);
    } while(choice == 1); // Repeat if user chooses to continue
}

// Function to find the FIRST set of a given symbol
void FIRST(char symbol) {
    int j;

    // If the symbol is a terminal, add it to FIRST set
    if(!isupper(symbol)) { 
        first[n++] = symbol; // Add terminal to `first` array
        return;
    }

    // Loop through each production rule
    for(j = 0; j < count; j++) {
        // If the production rule starts with the symbol
        if(prodn[j][0] == symbol) {
            
            // If the rule has epsilon (`$`), add `$` to FIRST set
            if(prodn[j][2] == '$') {
                first[n++] = '$';
            }
            // If the rule's next character is a terminal, add it to FIRST set
            else if(islower(prodn[j][2])) {
                first[n++] = prodn[j][2];
            }
            // If the rule's next character is a non-terminal, find its FIRST set
            else {
                FIRST(prodn[j][2]);
            }
        }
    }
}


// Main
// Step 1: Enter the no of productions
// Step 2: Enter each production one by one
// Step 3: Enter the character for which FIRST() is to be found
// Step 4: loop through the first array and print the values
// Step 5: Loop

// First()
// Step 1: Check if symbol is terminal or non terminal using isupper(symbol)
    // Step 1.1: If terminal then add to first array
    // Step 1.2 if not terminal then Do remaining steps
// Step 2: Loop through each production
    // Step 2.1: If the production starts with the symbol then
        // Step 2.1.1: If the RHS starts with epsilon, add epsilon to first
        // Step 2.1.2: If RHS starts with lowercase, add it to first
        // Step 2.1.3: If RHS starts with non terminal, find first of that 