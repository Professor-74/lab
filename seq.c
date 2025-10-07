#include <stdio.h>
#include <stdbool.h>

#define TOTAL_BLOCKS 50

int main() {
    int memory[TOTAL_BLOCKS] = {0};  
    int start, length;

    printf("Sequential File Allocation Strategy Simulation\n");
    printf("Total blocks available: %d\n", TOTAL_BLOCKS);

    char choice;
    do {
        printf("\nEnter the starting block and length of the file: ");
        scanf("%d %d", &start, &length);

        if (start < 0 || start + length > TOTAL_BLOCKS) {
            printf("Invalid input. Out of bounds.\n");
        } else {
            bool isFree = true;
            for (int i = start; i < start + length; i++) {
                if (memory[i] == 1) {
                    isFree = false;
                    break;
                }
            }

            if (isFree) {
                for (int i = start; i < start + length; i++) {
                    memory[i] = 1;
                }
                printf("File allocated from block %d to %d\n", start, start + length - 1);
            } else {
                printf("Error: Some blocks already allocated. Cannot allocate file.\n");
            }
        }

        printf("Do you want to allocate another file? (y/n): ");
        scanf(" %c", &choice); 

    } while (choice == 'y' || choice == 'Y');

    printf("\nFinal memory block allocation status:\n");
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");

    return 0;
}

