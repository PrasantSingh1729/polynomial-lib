#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    double coefficient;
    int exponent;
} Term;

Term parseTerm(char* termStr) {
    Term term;
    term.coefficient = 1.0;  // Default coefficient
    term.exponent = 0;       // Default exponent

    char* token = strtok(termStr, "*^ ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            term.coefficient = atof(token);
        } else if (isalpha(token[0])) {
            char* caretPos = strchr(token, '^');
            if (caretPos != NULL) {
                term.exponent = atoi(caretPos + 1);
            }
        }
        token = strtok(NULL, "*^ ");
    }

    return term;
}

int main() {
    char input[] = "+2*x^3 - 0.5x^2 + 3";
    char* termStr = strtok(input, "+-");
    
    while (termStr != NULL) {
        // Term term = parseTerm(termStr);
        // printf("Coefficient: %f, Exponent: %d\n", term.coefficient, term.exponent);
        printf("%s\n",termStr);
        termStr = strtok(NULL, "+-");
    }
    
    // return 0;
}
