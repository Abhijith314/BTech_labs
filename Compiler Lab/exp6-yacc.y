%{
  // C code section for Yacc. This code is copied to the top of the generated C file.
  #include <stdio.h>
  int yyerror(char* s); // Declare the error function.
%}

// Declare the tokens that will be provided by the Lexer.
// Yacc will generate a header file (y.tab.h) with these token definitions.
%token NUMBER ID

// Define the precedence and associativity of operators. This is how Yacc resolves ambiguities.
// Operators on the same line have the same precedence.
// Lines lower in the list have higher precedence.
%left '+' '-' // Lowest precedence, left-associative. (e.g., 5-3+2 is (5-3)+2)
%left '*' '/' // Higher precedence than +/-, left-associative.

/* Rule Section */
%%
// Grammar rules for the parser.

// The start symbol of the grammar is 'E' (Expression).
// When an expression is fully parsed and reduced to E, print the final result.
E : T    	{
            	printf("Result = %d\n", $$); // $$ refers to the value of the symbol on the left (E).
                return 0; // Successful parsing.
        	}

// 'T' represents a term in the expression.
T :
	T '+' T { $$ = $1 + $3; } // Rule for addition. $$ is the result. $1 is the value of the first T, $3 is the value of the second T.
	|
	T '-' T { $$ = $1 - $3; } // Rule for subtraction.
	| T '*' T { $$ = $1 * $3; } // Rule for multiplication.
	|
	T '/' T { $$ = $1 / $3; } // Rule for division.
	| '-' NUMBER { $$ = -$2; } // Rule for unary minus (e.g., -5).
	|
	'-' ID { $$ = -$2; }
	| '(' T ')' { $$ = $2; }   // Rule for expressions in parentheses. The value is just the value of the inner expression.
	| NUMBER { $$ = $1; }      // A term can be just a number. The value of T is the value of the NUMBER token.
	| ID { $$ = $1; };         // A term can be an ID (variable).
%%

// Main C code section.
int main()
{
	printf("Enter the expression\n");
	// yyparse() is the Yacc function that starts the parsing process. It will call yylex() to get tokens.
	yyparse();
}

// This function is called automatically by Yacc when a syntax error is found.
int yyerror(char* s) {
	printf("\nExpression is invalid\n");
}