#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_BLOCKS 50
#define MAX_FILES 10
#define MAX_BLOCKS_PER_FILE 10

int memory[TOTAL_BLOCKS];


struct File {
    int indexBlock;
    int dataBlocks[MAX_BLOCKS_PER_FILE];
    int blockCount;
};

int main() {
    struct File files[MAX_FILES];
    int fileCount = 0;
    char choice;
    srand(time(0));  // seed for random block selection

    printf("Indexed File Allocation Strategy (with Index Table)\n");
    printf("Total disk blocks: %d\n", TOTAL_BLOCKS);

    do {
        if (fileCount >= MAX_FILES) {
            printf("Max file count reached!\n");
            break;
        }

        int indexBlock, nBlocks;
        printf("\nEnter index block: ");
        scanf("%d", &indexBlock);

        if (indexBlock < 0 || indexBlock >= TOTAL_BLOCKS || memory[indexBlock] == 1) {
            printf("Invalid or already allocated index block.\n");
            continue;
        }

        printf("Enter number of data blocks required (max %d): ", MAX_BLOCKS_PER_FILE);
        scanf("%d", &nBlocks);

        if (nBlocks <= 0 || nBlocks > MAX_BLOCKS_PER_FILE) {
            printf("Invalid number of blocks.\n");
            continue;
        }

     
        int tempBlocks[MAX_BLOCKS_PER_FILE];
        int count = 0;

        for (int i = 0; i < TOTAL_BLOCKS && count < nBlocks; i++) {
            if (memory[i] == 0 && i != indexBlock) {
                tempBlocks[count++] = i;
            }
        }

        if (count < nBlocks) {
            printf("Not enough free blocks available.\n");
            continue;
        }

        memory[indexBlock] = 1;
        for (int i = 0; i < nBlocks; i++) {
            memory[tempBlocks[i]] = 1;
        }

      
        files[fileCount].indexBlock = indexBlock;
        files[fileCount].blockCount = nBlocks;
        for (int i = 0; i < nBlocks; i++) {
            files[fileCount].dataBlocks[i] = tempBlocks[i];
        }
        fileCount++;

        printf("File allocated successfully.\n");

        printf("Do you want to allocate another file? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    
    printf("\n--- File Allocation Table ---\n");
    for (int i = 0; i < fileCount; i++) {
        printf("File %d\n", i + 1);
        printf("Index Block: %d\n", files[i].indexBlock);
        printf("Data Blocks: ");
        for (int j = 0; j < files[i].blockCount; j++) {
            printf("%d ", files[i].dataBlocks[j]);
        }
        printf("\n----------------------------\n");
    }

    printf("\nFinal memory block allocation status:\n");
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");

    return 0;
}

