#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<numeric> // Add this line for accumulate

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
};

// Function to calculate waiting time and turnaround time for each process
void calculateWaitingTurnaroundTime(vector<Process>& processes, vector<int>& waitingTime, vector<int>& turnaroundTime) {
    int n = processes.size();
    int currentTime = 0;

    // Initialize remaining time for each process
    for (int i = 0; i < n; ++i) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Priority Scheduling
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority < b.priority;
    });

    // Variables for Round Robin
    queue<int> rrQueue;
    int rrTimeQuantum = 4;
    int rrCurrentIndex = 0;
    int rrCurrentQuantum = 0;

    for (int i = 0; i < n; ++i) {
        Process& currentProcess = processes[i];

        // Handle FCFS
        while (currentTime < currentProcess.arrivalTime) {
            currentTime++;
        }

        // Handle Round Robin
        while (rrCurrentIndex < n && processes[rrCurrentIndex].arrivalTime <= currentTime) {
            rrQueue.push(rrCurrentIndex);
            rrCurrentIndex++;
        }

        // Calculate waiting time
        if (rrQueue.empty()) {
            currentTime = max(currentTime, currentProcess.arrivalTime);
        }

        // Execute processes in Round Robin
        while (!rrQueue.empty() && rrCurrentQuantum < rrTimeQuantum) {
            int index = rrQueue.front();
            rrQueue.pop();
            Process& rrProcess = processes[index];

            int executeTime = min(rrTimeQuantum - rrCurrentQuantum, rrProcess.remainingTime);
            rrCurrentQuantum += executeTime;
            currentTime += executeTime;
            rrProcess.remainingTime -= executeTime;

            // Re-add the process to the queue if it's not finished
            if (rrProcess.remainingTime > 0) {
                rrQueue.push(index);
            }
        }

        // Calculate waiting time and reset RR quantum
        if (rrCurrentQuantum == rrTimeQuantum) {
            rrQueue.push(currentProcess.id);
            rrCurrentQuantum = 0;
        }

        currentProcess.remainingTime = max(0, currentProcess.remainingTime);
        waitingTime[currentProcess.id] = currentTime - currentProcess.arrivalTime - currentProcess.burstTime;
        turnaroundTime[currentProcess.id] = currentTime - currentProcess.arrivalTime;
    }
}

int main() {
    // Define the processes
    vector<Process> processes = {
        {1, 0, 24, 3},
        {2, 4, 3, 1},
        {3, 5, 3, 4},
        {4, 6, 12, 2}
    };

    int n = processes.size();
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);

    calculateWaitingTurnaroundTime(processes, waitingTime, turnaroundTime);

    // Print the results
    cout << "Process\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "P" << processes[i].id << "\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
    }

    // Calculate and print average waiting time and average turnaround time
    double avgWaitingTime = accumulate(waitingTime.begin(), waitingTime.end(), 0.0) / n;
    double avgTurnaroundTime = accumulate(turnaroundTime.begin(), turnaroundTime.end(), 0.0) / n;

    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    return 0;
}
