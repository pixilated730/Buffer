#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *cmd = "ls";  // Command to execute

// Function prototypes
void banner();
void vulnerable_function();

int main() {
    banner();
    vulnerable_function();
    return 0;
}

// Print a banner
void banner() {
    printf("====================================\n");
    printf("  Vulnerable Calculator\n");
    printf("====================================\n");
}

// Vulnerable function
void vulnerable_function() {
    char buffer[50]; // Fixed-size buffer
    int num1, num2, result;
    char operation;

    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    // Consume newline from the input buffer
    getchar();

    printf("Enter the operation (+, -, *, /): ");
    scanf("%c", &operation);

    // Overflow happens here when user inputs more than 50 characters
    printf("Enter a comment: ");
    getchar(); // Clear input buffer
    gets(buffer); // Unsafe function (vulnerable to overflow)

    printf("\nPerforming calculation...\n");

    switch (operation) {
        case '+':
            result = num1 + num2;
            printf("Result: %d\n", result);
            break;
        case '-':
            result = num1 - num2;
            printf("Result: %d\n", result);
            break;
        case '*':
            result = num1 * num2;
            printf("Result: %d\n", result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("Result: %d\n", result);
            } else {
                printf("Error: Division by zero.\n");
            }
            break;
        default:
            printf("Invalid operation.\n");
    }

    printf("\nYou entered: %s\n", buffer); // Display the comment

    // If buffer overflow happens, this will execute
    system(cmd);  // Execute the command
}
