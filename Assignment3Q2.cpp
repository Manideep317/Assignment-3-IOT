#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Patient {
    char id;
    int arrivalTime;
    int treatmentTime;
    int urgencyLevel;
};

bool compareArrivalTime(const Patient& a, const Patient& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareTreatmentTime(const Patient& a, const Patient& b) {
    return a.treatmentTime < b.treatmentTime;
}

bool compareUrgencyLevel(const Patient& a, const Patient& b) {
    return a.urgencyLevel < b.urgencyLevel;
}

void calculateTurnaroundTime(vector<Patient>& patients, vector<int>& turnaroundTime) {
    int n = patients.size();
    vector<int> completionTime(n);

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            completionTime[i] = patients[i].arrivalTime + patients[i].treatmentTime;
        } else {
            completionTime[i] = max(patients[i].arrivalTime, completionTime[i - 1]) + patients[i].treatmentTime;
        }
        turnaroundTime[i] = completionTime[i] - patients[i].arrivalTime;
    }
}

void calculateWaitingTime(vector<Patient>& patients, vector<int>& turnaroundTime, vector<int>& waitingTime) {
    int n = patients.size();
    
    for (int i = 0; i < n; i++) {
        waitingTime[i] = turnaroundTime[i] - patients[i].treatmentTime;
    }
}

void FCFS(vector<Patient>& patients) {
    sort(patients.begin(), patients.end(), compareArrivalTime);
    vector<int> turnaroundTime(patients.size());
    calculateTurnaroundTime(patients, turnaroundTime);
    
    vector<int> waitingTime(patients.size());
    calculateWaitingTime(patients, turnaroundTime, waitingTime);

    cout << "FCFS Order: ";
    for (const Patient& p : patients) {
        cout << p.id << " ";
    }
    cout << endl;
    
    double avgTurnaroundTime = 0, avgWaitingTime = 0;
    for (int i = 0; i < patients.size(); i++) {
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime /= patients.size();
    avgWaitingTime /= patients.size();

    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
}

void SJF(vector<Patient>& patients) {
    sort(patients.begin(), patients.end(), compareTreatmentTime);
    vector<int> turnaroundTime(patients.size());
    calculateTurnaroundTime(patients, turnaroundTime);
    
    vector<int> waitingTime(patients.size());
    calculateWaitingTime(patients, turnaroundTime, waitingTime);

    cout << "SJF Order: ";
    for (const Patient& p : patients) {
        cout << p.id << " ";
    }
    cout << endl;
    
    double avgTurnaroundTime = 0, avgWaitingTime = 0;
    for (int i = 0; i < patients.size(); i++) {
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime /= patients.size();
    avgWaitingTime /= patients.size();

    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
}

void PriorityScheduling(vector<Patient>& patients) {
    sort(patients.begin(), patients.end(), compareUrgencyLevel);
    vector<int> turnaroundTime(patients.size());
    calculateTurnaroundTime(patients, turnaroundTime);
    
    vector<int> waitingTime(patients.size());
    calculateWaitingTime(patients, turnaroundTime, waitingTime);

    cout << "Priority Scheduling Order: ";
    for (const Patient& p : patients) {
        cout << p.id << " ";
    }
    cout << endl;
    
    double avgTurnaroundTime = 0, avgWaitingTime = 0;
    for (int i = 0; i < patients.size(); i++) {
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime /= patients.size();
    avgWaitingTime /= patients.size();

    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
}

int main() {
    vector<Patient> patients = {
        {'A', 0, 30, 3},
        {'B', 10, 20, 5},
        {'C', 15, 40, 2},
        {'D', 20, 15, 4}
    };

    FCFS(patients);
    SJF(patients);
    PriorityScheduling(patients);

    return 0;
}

