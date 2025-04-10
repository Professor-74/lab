#include <stdio.h>

int n, m;
int alloc[10][10], max[10][10], need[10][10], avail[10];
int finish[10], work[10], safeSeq[10];


void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}


int isSafe() {
    for (int i = 0; i < m; i++) work[i] = avail[i];
    for (int i = 0; i < n; i++) finish[i] = 0;

    int count = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int flag = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    return count == n;
}


void printSafeSeq() {
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    calculateNeed();

    if (isSafe()) {
        printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
        printSafeSeq();
    } else {
        printf("\nSystem is NOT in a safe state.\n");
        return 0;
    }

   
    char choice;
    printf("\nDo you want to make a resource request? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        int p, req[10];
        printf("Enter process number (0 to %d): ", n - 1);
        scanf("%d", &p);

        if (p < 0 || p >= n) {
            printf("Invalid process number.\n");
            return 1;
        }

        printf("Enter request for P%d:\n", p);
        for (int i = 0; i < m; i++)
            scanf("%d", &req[i]);

        int valid = 1;
        for (int i = 0; i < m; i++) {
            if (req[i] < 0) {
                printf("Error: Negative request not allowed.\n");
                valid = 0;
                break;
            }
            if (req[i] > need[p][i]) {
                printf("Error: Request exceeds maximum need.\n");
                valid = 0;
                break;
            }
            if (req[i] > avail[i]) {
                printf("Resources not available. P%d must wait.\n", p);
                valid = 0;
                break;
            }
        }

        if (valid) {
           
            for (int i = 0; i < m; i++) {
                avail[i] -= req[i];
                alloc[p][i] += req[i];
                need[p][i] -= req[i];
            }

            if (isSafe()) {
                printf("Request granted. New Safe Sequence: ");
                printSafeSeq();
            } else {
                printf("Request leads to unsafe state. Request denied.\n");
                // Rollback to previous state
                for (int i = 0; i < m; i++) {
                    avail[i] += req[i];
                    alloc[p][i] -= req[i];
                    need[p][i] += req[i];
                }
            }
        }
    }

    return 0;
}
