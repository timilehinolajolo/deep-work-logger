#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void playGame() {
    int secret_number, guess, attempts = 0;
    const int MAX_ATTEMPTS = 5;

    // Generate a random number between 1 and 50
    secret_number = (rand() % 50) + 1;

    printf("\n=== New Game Started ===\n");
    printf("I have chosen a number between 1 and 50.\n");
    printf("You have %d attempts to guess it!\n", MAX_ATTEMPTS);

    // Game loop
    while (attempts < MAX_ATTEMPTS) {
        printf("\nAttempt %d/%d. Enter your guess: ", attempts + 1, MAX_ATTEMPTS);
        
        // Validate integer input
        if (scanf("%d", &guess) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        attempts++;

        // Check the guess
        if (guess == secret_number) {
            printf("🎉 Congratulations! You guessed the number in %d attempts!\n", attempts);
            return;
        } else if (guess < secret_number) {
            printf("Too low! Try a higher number.");
        } else {
            printf("Too high! Try a lower number.");
        }
    }

    printf("\n😢 Game Over! You've run out of attempts. The number was %d.\n", secret_number);
}

int main() {
    int choice;

    // Seed the random number generator using the current time
    srand(time(0));

    printf("=================================\n");
    printf("   WELCOME TO THE GUESSING GAME  \n");
    printf("=================================\n");

    do {
        printf("\n1. Play Game\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                printf("\nThank you for playing! Goodbye.\n");
                break;
            default:
                printf("Invalid selection! Please enter 1 or 2.\n");
        }
    } while (choice != 2);

    return 0;
}
