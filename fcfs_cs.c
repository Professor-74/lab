#include <stdio.h>

struct process{
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	};
	
int main(){
	int n,i;
	struct process p[100];
	
	printf("Enter the number of process:\t");
	scanf("%d", &n);
	
	for(i=0; i<n;i++)
	{
		printf("Enter the pid, AT, BT of the process:\n");
		scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
		}
		
for(i=0; i<n; i++)
{
	for(int j=i+1; j<n;j++)
	{
		if (p[i].at> p[j].at)
		{
			struct process temp = p[i];
			p[i] = p[j];
			p[j] = temp;
			}
		}
	}
	
 int time=0;
 for(i=0; i<n;i++)
 {
	 if (time< p[i].at)
	 {
		 time = p[i].at;
		 }
		 
	   p[i].ct = time+ p[i].bt;
	   p[i].tat = p[i].ct - p[i].at;
	   p[i].wt = p[i].tat - p[i].bt;
	   
	   time = p[i].ct;
	   
	 }
	 
	 float total_tat = 0, total_wt = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
	
	
	}
