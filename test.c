#include <stdio.h>

// Define a structure to represent a process
struct Process {
    char name;
    int arrivalTime;
    int burstTime;
    int priority;
};

// Function to calculate the average wait time
float calculateAverageWaitTime(int n, int waitTime[]) {
    int totalWaitTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitTime += waitTime[i];
    }
    return (float)totalWaitTime / n;
}

// Function to calculate the average turnaround time
float calculateAverageTurnaroundTime(int n, int turnaroundTime[]) {
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += turnaroundTime[i];
    }
    return (float)totalTurnaroundTime / n;
}

// Function to implement First-Come-First-Serve (FCFS) scheduling
void FCFS(struct Process processes[], int n) {
    int waitTime[n], turnaroundTime[n];

    waitTime[0] = 0;
    turnaroundTime[0] = processes[0].burstTime;

    for (int i = 1; i < n; i++) {
        waitTime[i] = turnaroundTime[i - 1];
        turnaroundTime[i] = waitTime[i] + processes[i].burstTime;
    }

    float avgWaitTime = calculateAverageWaitTime(n, waitTime);
    float avgTurnaroundTime = calculateAverageTurnaroundTime(n, turnaroundTime);

    printf("FCFS Scheduling Results:\n");
    printf("Process\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t%d\t\t%d\n", processes[i].name, waitTime[i], turnaroundTime[i]);
    }
    printf("Average Wait Time: %.2f\n", avgWaitTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

// Function to implement Priority-Based Scheduling
void PriorityScheduling(struct Process processes[], int n) {
    int waitTime[n], turnaroundTime[n];

    // Sort processes by priority (higher priority first)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                // Swap processes[i] and processes[j]
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    waitTime[0] = 0;
    turnaroundTime[0] = processes[0].burstTime;

    for (int i = 1; i < n; i++) {
        waitTime[i] = turnaroundTime[i - 1];
        turnaroundTime[i] = waitTime[i] + processes[i].burstTime;
    }

    float avgWaitTime = calculateAverageWaitTime(n, waitTime);
    float avgTurnaroundTime = calculateAverageTurnaroundTime(n, turnaroundTime);

    printf("Priority Scheduling Results:\n");
    printf("Process\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t%d\t\t%d\n", processes[i].name, waitTime[i], turnaroundTime[i]);
    }
    printf("Average Wait Time: %.2f\n", avgWaitTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    int n = 4; // Number of processes
    struct Process processes[n];

    // Initialize processes for different scenarios
    processes[0] = (struct Process){'A', 0, 5, 1};
    processes[1] = (struct Process){'B', 1, 3, 2};
    processes[2] = (struct Process){'C', 2, 8, 3};
    processes[3] = (struct Process){'D', 3, 6, 4};

    printf("Scenario 1: FCFS - User processes arrive before the kernel\n");
    FCFS(processes, n);

    // Swap arrival times to simulate another scenario
    processes[0].arrivalTime = 1;
    processes[1].arrivalTime = 0;

    printf("\nScenario 2: FCFS - Kernel processes arrive before the user\n");
    FCFS(processes, n);

    // Restore arrival times and update priorities for priority-based scheduling
    processes[0].arrivalTime = 0;
    processes[1].arrivalTime = 1;
    processes[0].priority = 1; // Highest priority for user process A
    processes[1].priority = 2;
    processes[2].priority = 3;
    processes[3].priority = 4;

    printf("\nScenario 3: Priority - User process has the highest priority\n");
    PriorityScheduling(processes, n);

    // Swap priorities to simulate another scenario
    processes[0].priority = 4; // Highest priority for kernel process A
    processes[3].priority = 1;

    printf("\nScenario 4: Priority - Kernel processes have the highest priority\n");
    PriorityScheduling(processes, n);

    return 0;
}
