#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

// struct Process
// {
//   int id = 0;
//   int arrivalTime = 0;
//   int burstTime = 0;
//   int completionTime = 0;
//   int waitingTime = 0;
//   int turnaroundTime = 0;
//   bool completed = false;
//   int startTime = 0;
// };

// void customSwap(Process &a, Process &b)
// {
//   Process temp = a;
//   a = b;
//   b = temp;
// }

// void selectSort(Process processes[], int n)
// {
//   for (int i = 0; i < n; i++)
//   {
//     int mnindex = i;
//     for (int j = i + 1; j < n; j++)
//     {
//       if (processes[i].arrivalTime > processes[mnindex].arrivalTime)
//       {
//         mnindex = j;
//       }
//     }
//     if (mnindex != i)
//     {
//       customSwap(processes[i], processes[mnindex]);
//     }
//   }
// }

// int main()
// {
//   int n;
//   float avg_waiting_time = 0, avg_turnaround_time = 0;
//   cout << "Enter the number of processes: ";
//   cin >> n;
//   Process processes[n];
//   for (int i = 0; i < n; i++)
//   {
//     cout << "Enter arrival time and burst time of process " << i + 1 << ": ";
//     cin >> processes[i].arrivalTime >> processes[i].burstTime;
//     processes[i].id = i + 1; // Assign process ID
//   }

//   selectSort(processes, n);

//   // Calculate Completion Time
//   int currentTime = 0;
//   for (int i = 0; i < n; i++)
//   {
//     if (processes[i].arrivalTime > currentTime)
//     {
//       currentTime = processes[i].arrivalTime;
//     }
//     processes[i].completionTime = currentTime + processes[i].burstTime;
//     currentTime = processes[i].completionTime;
//   }

//   // Calculate Waiting and Turnaround Time
//   for (int i = 0; i < n; i++)
//   {
//     processes[i].waitingTime = processes[i].completionTime - processes[i].arrivalTime - processes[i].burstTime;
//     processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
//   }

//   // Calculate Average Waiting and Turnaround Time
//   for (int i = 0; i < n; i++)
//   {
//     avg_waiting_time += processes[i].waitingTime;
//     avg_turnaround_time += processes[i].turnaroundTime;
//   }

//   avg_waiting_time /= n;
//   avg_turnaround_time /= n;

//   // Display Output
//   cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting time\t Turn Around Time: " << endl;
//   for (int i = 0; i < n; i++)
//   {
//     cout << "P" << processes[i].id << "\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
//   }

//   cout << "Avg waiting time: " << avg_waiting_time << endl;
//   cout << "Avg turnaround time: " << avg_turnaround_time << endl;

//   return 0;
// }

struct process
{
  int pid;
  int arrival_time;
  int burst_time;
  int start_time;
  int completion_time;
  int turnaround_time;
  int waiting_time;
};

int main()
{

  int n;
  struct process p[100];
  float avg_turnaround_time;
  float avg_waiting_time;
  float avg_response_time;
  int total_turnaround_time = 0;
  int total_waiting_time = 0;
  int is_completed[100];
  memset(is_completed, 0, sizeof(is_completed)); // copies a single character for a specified number of times to an object


  cout << "Enter the number of processes: ";
  cin >> n;

  for (int i = 0; i < n; i++)
  {
    cout << "Enter arrival time of process " << i + 1 << ": ";
    cin >> p[i].arrival_time;
    cout << "Enter burst time of process " << i + 1 << ": ";
    cin >> p[i].burst_time;
    p[i].pid = i + 1;
    cout << endl;
  }

  int current_time = 0;
  int completed = 0;
  int prev = 0;

  while (completed != n)
  {
    int idx = -1;
    int mn = 10000000;
    for (int i = 0; i < n; i++)
    {
      if (p[i].arrival_time <= current_time && is_completed[i] == 0)
      {
        if (p[i].burst_time < mn)
        {
          mn = p[i].burst_time;
          idx = i;
        }
        if (p[i].burst_time == mn)
        {
          if (p[i].arrival_time < p[idx].arrival_time)
          {
            mn = p[i].burst_time;
            idx = i;
          }
        }
      }
    }
    if (idx != -1)
    {
      p[idx].start_time = current_time;
      p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
      p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
      p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

      total_turnaround_time += p[idx].turnaround_time;
      total_waiting_time += p[idx].waiting_time;

      is_completed[idx] = 1;
      completed++;
      current_time = p[idx].completion_time;
      prev = current_time;
    }
    else
    {
      current_time++;
    }
  }

  int min_arrival_time = 10000000;
  int max_completion_time = -1;
  for (int i = 0; i < n; i++)
  {
    min_arrival_time = min(min_arrival_time, p[i].arrival_time);
    max_completion_time = max(max_completion_time, p[i].completion_time);
  }

  avg_turnaround_time = (float)total_turnaround_time / n;
  avg_waiting_time = (float)total_waiting_time / n;

  cout << endl
       << endl;

  cout << "#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "\n"
       << endl;

  for (int i = 0; i < n; i++)
  {
    cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << "\n"
         << endl;
  }
  cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
  cout << "Average Waiting Time = " << avg_waiting_time << endl;
}
