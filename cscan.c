#include <stdio.h>
#include <stdlib.h> 


int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


void cscan_disk_scheduling(int requests[], int num_requests, int initial_head_pos, int disk_size) {
    int total_seek_time = 0;
    int current_head_pos = initial_head_pos;
    int i;

    printf("\nC-SCAN disk scheduling (Right then Wrap-Around)\n");
    printf("Initial head position = %d\n", initial_head_pos);
    printf("Seek Sequence: %d", initial_head_pos);


    int sorted_requests[num_requests];
    for (i = 0; i < num_requests; i++) {
        sorted_requests[i] = requests[i];
    }
    qsort(sorted_requests, num_requests, sizeof(int), compare);


    int right_of_head[num_requests];
    int left_of_head[num_requests];
    int right_count = 0;
    int left_count = 0;

    for (i = 0; i < num_requests; i++) {
        if (sorted_requests[i] >= initial_head_pos) {
            right_of_head[right_count++] = sorted_requests[i];
        } else {
            left_of_head[left_count++] = sorted_requests[i];
        }
    }


    for (i = 0; i < right_count; i++) {
        total_seek_time += abs(right_of_head[i] - current_head_pos);
        current_head_pos = right_of_head[i];
        printf(" -> %d", current_head_pos);
    }


    if (current_head_pos != (disk_size - 1)) {
        total_seek_time += abs((disk_size - 1) - current_head_pos);
        current_head_pos = disk_size - 1;
        printf(" -> %d (End of Disk)", current_head_pos);
    }


    if (left_count > 0 || current_head_pos != 0) { 
        total_seek_time += abs(0 - current_head_pos); 
        current_head_pos = 0;
        printf(" -> %d (Wrap-Around)", current_head_pos);
    }


    for (i = 0; i < left_count; i++) {
        total_seek_time += abs(left_of_head[i] - current_head_pos);
        current_head_pos = left_of_head[i];
        printf(" -> %d", current_head_pos);
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int num_requests;
    int initial_head_pos;
    int disk_size; 

    printf("Enter the number of disk requests:\t");
    scanf("%d", &num_requests);

    int requests[num_requests];
    printf("Enter the disk requesting sequence:\t");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position:\t");
    scanf("%d", &initial_head_pos);

    printf("Enter the total disk size (e.g., 200 for 0-199 cylinders):\t");
    scanf("%d", &disk_size);


    cscan_disk_scheduling(requests, num_requests, initial_head_pos, disk_size);

    return 0;
}
