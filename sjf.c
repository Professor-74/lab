#include <stdio.h>

struct Process {
    int pid;
    int at;  
    int bt;  
    int ct;  
    int tat; 
    int wt;  
    int completed; 
};

int main() {
    int n, i, completed = 0, time = 0;
    float total_tat = 0, total_wt = 0;

    struct Process p[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);


    for(i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for P%d: ", i+1);
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    while(completed < n) {
        int idx = -1;
        int min_bt = 9999;

    
        for(i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].completed == 0) {
                if(p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
                
                if(p[i].bt == min_bt && p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            
            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            time = p[idx].ct;
            p[idx].completed = 1;
            completed++;

            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
        } else {
            time++; 
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
            p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}
