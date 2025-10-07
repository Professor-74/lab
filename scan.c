#include <stdio.h>
#include <stdlib.h> 


int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void scan_one_direction(int requests[], int num_requests, int initial_head_pos, int disk_size) {
    int total_seek_time = 0;
    int current_head_pos = initial_head_pos;
    int i;

    printf("\nSCAN disk scheduling (Right then Left)\n");
    printf("Initial head position = %d\n", initial_head_pos);
    printf("Seek Sequence: %d", initial_head_pos);


    int sorted_requests[num_requests];
    for (i = 0; i < num_requests; i++) {
        sorted_requests[i] = requests[i];
    }
    qsort(sorted_requests, num_requests, sizeof(int), compare);

 
    int left_requests[num_requests], right_requests[num_requests];
    int left_count = 0, right_count = 0;

    for (i = 0; i < num_requests; i++) {
        if (sorted_requests[i] < initial_head_pos) {
            left_requests[left_count++] = sorted_requests[i];
        } else {
            right_requests[right_count++] = sorted_requests[i];
        }
    }

   
    for (i = 0; i < right_count; i++) {
        total_seek_time += abs(right_requests[i] - current_head_pos);
        current_head_pos = right_requests[i];
        printf(" -> %d", current_head_pos);
    }

    
    if (current_head_pos != disk_size - 1) {
        total_seek_time += abs((disk_size - 1) - current_head_pos);
        current_head_pos = disk_size - 1;
        printf(" -> %d (End of Disk)", current_head_pos);
    }


    for (i = left_count - 1; i >= 0; i--) {
        total_seek_time += abs(left_requests[i] - current_head_pos);
        current_head_pos = left_requests[i];
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


    scan_one_direction(requests, num_requests, initial_head_pos, disk_size);

    return 0;
}
