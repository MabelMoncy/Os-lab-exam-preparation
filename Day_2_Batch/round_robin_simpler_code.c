#include <stdio.h>

struct Process
{
    int id, at, bt, rt, ct, tat, wt;
};

int main()
{
    int n, tq, time = 0, completed = 0;
    float totalWT = 0;

    printf("Enter number of processes and Time Quantum: ");
    scanf("%d %d", &n, &tq);

    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // Remaining time initialization
    }

    // Main Simulation Loop
    while (completed < n)
    {
        int idle = 1; // Flag to track if CPU did nothing this cycle

        for (int i = 0; i < n; i++)
        {
            // Process can run only if it has arrived and is not finished
            if (p[i].at <= time && p[i].rt > 0)
            {
                idle = 0;
                int exec = (p[i].rt < tq) ? p[i].rt : tq;

                time += exec;
                p[i].rt -= exec;

                if (p[i].rt == 0)
                { // Process completes
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    totalWT += p[i].wt;
                    completed++;
                }
            }
        }
        if (idle)
            time++; // If no process was ready, advance time (CPU idle)
    }

    // Output Display
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    return 0;
}