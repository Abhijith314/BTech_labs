#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

void main()
{
    // File pointer to hold the input file
    FILE *f1;
    // 'c' holds the current character, 'str' stores multi-character lexemes
    char c, str[100];
    // 'num' stores the value of a number, 'i' is an index for 'str', 'lineno' counts lines
    int num = 0, i = 0, lineno = 0;

    // Open the input file "input.txt" in read mode. Make sure this file exists.
    f1 = fopen("input.txt", "r");
    printf("Token\t\t\tLexeme\n");

    // Loop through the file character by character until the end (EOF) is reached.
    while ((c = getc(f1)) != EOF)
    {
        // Check if the character is a digit using the isdigit() function.
        if (isdigit(c))
        {
            // Convert character ('0'-'9') to integer (0-9) by subtracting the ASCII value of '0' (which is 48).
            num = c - 48;
            c = getc(f1); // Read the next character.
            // Continue reading as long as subsequent characters are also digits.
            while (isdigit(c))
            {
                // Build the full number (e.g., if you have '1' then '2', it becomes 1*10 + 2 = 12).
                num = num * 10 + (c - 48);
                c = getc(f1);
            }
            printf("Number \t\t\t %d \n", num);
            // The last character read was not a digit, so push it back to the input stream
            // so it can be processed in the next loop iteration.
            ungetc(c, f1);
        }
        // Check if the character is an alphabet using isalpha().
        else if (isalpha(c))
        {
            // Start building a string for a potential identifier or keyword.
            str[i++] = c;
            c = getc(f1); // Read the next character.
            // Continue reading if the character is a letter, digit, underscore, or dollar sign.
            while (isdigit(c) || isalpha(c) || c == '_' || c == '$')
            {
                str[i++] = c;
                c = getc(f1);
            }
            // Add the null terminator to mark the end of the string.
            str[i++] = '\0';

            // Use strcmp() to check if the identified string is a known keyword.
            if (strcmp("for", str) == 0 || strcmp("while", str) == 0 || strcmp("do", str) == 0 || strcmp("int", str) == 0 || strcmp("float", str) == 0 || strcmp("char", str) == 0 || strcmp("double", str) == 0 || strcmp("static", str) == 0 || strcmp("switch", str) == 0 ||  strcmp("case", str) == 0 ||strcmp("printf", str) == 0)
            {
                printf("Keyword \t\t %s \n", str);
            }
            else // If it's not a keyword, it's an identifier.
            {
                printf("Identifier \t\t %s \n", str);
            }
            // Push the last read character back to the stream.
            ungetc(c, f1);
            // Reset the string index for the next identifier/keyword.
            i = 0;
        }
        // Ignore spaces and tabs.
        else if (c == ' ' || c == '\t')
        {
           // This block is intentionally empty to skip whitespace.
        }
        // Increment line number on newline character.
        else if (c == '\n')
        {
            lineno++;
        }
        // Any other character that doesn't fit the above categories is a special symbol.
        else
        {
            printf("Special symbol \t\t %c \n", c);
        }
    }

    // Print the total number of lines counted.
    printf("\nTotal no. of lines are: %d \n", lineno);
    // Close the file to free up resources.
    fclose(f1);
}

/*
---------------------------------
ALGORITHM
---------------------------------
1.  Start the program.
2.  Initialize variables for line number, string index, etc.
3.  Open the source code file (e.g., "input.txt") in read mode.
4.  Read the file character by character in a loop until the end of the file (EOF) is reached.
5.  Inside the loop, for each character `c`:
    a. If `c` is a digit, read all consecutive digits to form a number. Print it as a "Number" token.
    b. If `c` is a letter, read all consecutive letters, digits, and underscores to form a word.
       i.  Check if this word is in the list of keywords.
       ii. If yes, print it as a "Keyword" token.
       iii. If no, print it as an "Identifier" token.
    c. If `c` is a newline character `\n`, increment the line counter.
    d. If `c` is a space or tab, ignore it.
    e. If `c` is none of the above, print it as a "Special Symbol" token.
6.  After the loop finishes, print the total count of lines.
7.  Close the file.
8.  End the program.
*/