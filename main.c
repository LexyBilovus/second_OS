#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int coins = 1000;

    printf("One-armed bandit\n");

    int length = 7;

    while (coins > 0) {
        int bet, win = 0;
        printf("You have %d coins\n", coins);
        printf("Enter your bet or enter 0 to exit): ");
        scanf("%d", &bet);

        if (bet == 0)
            break;
        if (bet > coins) {
            printf("You cannot bet more coins than you have!\n");
            continue;
        }

        int *sequence = malloc(length * sizeof(int));
        if (sequence == NULL) {
            printf("Memory allocation error!\n");
            return 1;
        }

        printf("Sequence: ");
        for (int i = 0; i < length; i++) {
            sequence[i] = rand() % 10;
            printf("%d ", sequence[i]);
            if (sequence[i] == 7)
                win = bet;
        }
        printf("\n");

        int *frequency = calloc(10, sizeof(int));
        if (frequency == NULL) {
            free(sequence);
            printf("Memory allocation error!\n");
            return 1;
        }

        for (int i = 0; i < length; i++) {
            frequency[sequence[i]]++;
        }

        for (int i = 0; i < 10; i++) {
            if (frequency[i] == length) {
                win = i == 7 ? bet * 3 : bet * 2;
                printf("All digits are the same! Win: %d\n", win);
                break;
            }
        }

        for (int i = 0; i < 10; i++) {
            if (frequency[i] >= (length + 2) / 3) {
                if (win == 0) {
                    win = bet;
                    printf("At least one-third of the digits are the same! Win: %d\n", win);
                }
                break;
            }
        }

        coins = coins - bet + win;

        if (win) {
            printf("Congratulations! You won %d coins\n", win);
        } else {
            printf("Sorry! You lost your bet!\n");
        }

        free(sequence);
        free(frequency);

        if (coins == 0) {
            printf("You have spent all your coins!\n");
        }
    }
    printf("Game over!\n");
    printf("You have %d coins left\n", coins);
    return 0;
}
