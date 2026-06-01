#include <stdio.h>

struct ProcessControlBlock
{
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main()
{
    int total_processes, time_quantum;
    int current_time = 0, completed_processes_count = 0;
    float total_waiting_time = 0;

    printf("Enter number of processes and Time Quantum: ");
    scanf("%d %d", &total_processes, &time_quantum);

    struct ProcessControlBlock process_list[total_processes];

    // Step 1: Input process metrics
    for (int i = 0; i < total_processes; i++)
    {
        process_list[i].process_id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &process_list[i].arrival_time, &process_list[i].burst_time);

        // At start, remaining time is exactly equal to the total burst time
        process_list[i].remaining_time = process_list[i].burst_time;
    }

    // Step 2: Main Scheduling Simulation Loop
    while (completed_processes_count < total_processes)
    {
        int cpu_was_idle_this_cycle = 1; // Flag to catch gaps where no process has arrived yet

        for (int i = 0; i < total_processes; i++)
        {
            // A process can execute only if it has arrived and still needs CPU time
            if (process_list[i].arrival_time <= current_time && process_list[i].remaining_time > 0)
            {
                cpu_was_idle_this_cycle = 0; // CPU is actively processing data

                // Determine execution slice: either the full time quantum or the leftover work time
                int execution_slice = (process_list[i].remaining_time < time_quantum)
                                          ? process_list[i].remaining_time
                                          : time_quantum;

                current_time += execution_slice;
                process_list[i].remaining_time -= execution_slice;

                // Check if the process finished its execution work load
                if (process_list[i].remaining_time == 0)
                {
                    process_list[i].completion_time = current_time;

                    // Direct math calculations derived from standard scheduling formulas
                    process_list[i].turnaround_time = process_list[i].completion_time - process_list[i].arrival_time;
                    process_list[i].waiting_time = process_list[i].turnaround_time - process_list[i].burst_time;

                    total_waiting_time += process_list[i].waiting_time;
                    completed_processes_count++;
                }
            }
        }

        // If the entire array loop ran and no ready process was found, advance the system clock
        if (cpu_was_idle_this_cycle)
        {
            current_time++;
        }
    }

    // Step 3: Print Structured Output Table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < total_processes; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               process_list[i].process_id,
               process_list[i].arrival_time,
               process_list[i].burst_time,
               process_list[i].completion_time,
               process_list[i].turnaround_time,
               process_list[i].waiting_time);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_waiting_time / total_processes);

    return 0;
}