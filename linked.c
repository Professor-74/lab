#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_BLOCKS 50
#define MAX_FILES 10
#define MAX_BLOCKS_PER_FILE 10

int memory[TOTAL_BLOCKS]; 


struct File {
    int startBlock;
    int blockCount;
    int blocks[MAX_BLOCKS_PER_FILE];
};

int main() {
    struct File files[MAX_FILES];
    int fileCount = 0;
    char choice;
    srand(time(0)); 

    printf("Linked File Allocation Strategy Simulation\n");
    printf("Total disk blocks: %d\n", TOTAL_BLOCKS);

    do {
        if (fileCount >= MAX_FILES) {
            printf("Max file limit reached!\n");
            break;
        }

        int nBlocks;
        printf("\nEnter number of blocks required for the file (max %d): ", MAX_BLOCKS_PER_FILE);
        scanf("%d", &nBlocks);

        if (nBlocks <= 0 || nBlocks > MAX_BLOCKS_PER_FILE) {
            printf("Invalid block count.\n");
            continue;
        }

        int allocated[MAX_BLOCKS_PER_FILE];
        int count = 0;


        for (int i = 0; i < TOTAL_BLOCKS && count < nBlocks; i++) {
            if (memory[i] == 0) {
                allocated[count++] = i;
            }
        }

        if (count < nBlocks) {
            printf("Not enough free blocks available.\n");
            continue;
        }

       
        for (int i = 0; i < nBlocks; i++) {
            memory[allocated[i]] = 1;
        }

       
        files[fileCount].startBlock = allocated[0];
        files[fileCount].blockCount = nBlocks;
        for (int i = 0; i < nBlocks; i++) {
            files[fileCount].blocks[i] = allocated[i];
        }
        fileCount++;

        printf("File allocated successfully.\n");

        printf("Do you want to allocate another file? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');


    printf("\n--- File Allocation Table (Linked) ---\n");
    for (int i = 0; i < fileCount; i++) {
        printf("File %d:\n", i + 1);
        printf("Start Block: %d\n", files[i].startBlock);
        printf("Block Chain: ");
        for (int j = 0; j < files[i].blockCount; j++) {
            printf("%d", files[i].blocks[j]);
            if (j != files[i].blockCount - 1) {
                printf(" -> ");
            }
        }
        printf(" -> NULL\n-------------------------\n");
    }

 
    printf("\nFinal memory block allocation status:\n");
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");

    return 0;
}

