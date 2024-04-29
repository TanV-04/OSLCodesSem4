#include<iostream>
using namespace std;
struct Process
{
    int id;
    float arrivaltime;
    float burstTime;
    float completionTime;
    float waitingTime;
    float TurnaroundTime;
};

void customSwap(Process &a, Process &b)
{
    Process temp = a;
    a = b;
    b = temp;
}

void selectionSort(Process processes[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int minindex = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (processes[j].arrivaltime < processes[minindex].arrivaltime)
            {
                minindex = j;
            }
        }
        if (minindex != i)
            customSwap(processes[i], processes[minindex]);
    }
}
void calculateTime(Process processes[], int n)
{
    int currentTime = 0;
    int totalwaitingTime = 0;
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; ++i)
    {
        if (currentTime < processes[i].arrivaltime)
            currentTime = processes[i].arrivaltime;
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].waitingTime = currentTime - processes[i].arrivaltime;
        processes[i].TurnaroundTime = currentTime - processes[i].arrivaltime + processes[i].burstTime;
        currentTime = processes[i].completionTime;
        totalwaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].TurnaroundTime;
    }
   float avgwaitingTime = totalwaitingTime / n;
   float avgTurnaroundTime = totalTurnaroundTime / n;
   cout << "Average waiting time: " << avgwaitingTime << endl;
   cout << "Average turnaround time: " << avgTurnaroundTime << endl;
}
void displayProcesses(Process processes[], int n)
{
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting time\t Turn Around Time: " << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "P" << processes[i].id << "\t" << processes[i].arrivaltime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].waitingTime << "\t\t" << processes[i].TurnaroundTime << endl;
    }
    // float avgwaitingTime = totalwaitingTime / n;
    // float avgTurnaroundTime = totalTurnaroundTime / n;
    // cout << "Average waiting time: " << avgwaitingTime << endl;
    // cout << "Average turnaround time: " << avgTurnaroundTime << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    Process processes[n];
    cout << "Enter arrival time and burst time for each process: \n";
    for (int i = 0; i < n; ++i)
    {
        processes[i].id = i + 1;
        cout << "Process: " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrivaltime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
    }
    calculateTime(processes,n);
    displayProcesses (processes, n);
    return 0;
}