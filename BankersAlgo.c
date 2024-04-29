#include <stdio.h>

int max[10][10], allocation[10][10], need[10][10];
int available[10];
int num_processes, num_resources;

void readMatrix(int matrix[10][10])
{
  for (int i = 0; i < num_processes; i++)
  {
    for (int j = 0; j < num_resources; j++)
    {
      scanf("%d", &matrix[i][j]);
    }
  }
}

void displayMatrix(int matrix[10][10])
{
  for (int i = 0; i < num_processes; i++)
  {
    printf("\n P%d", i);
    for (int j = 0; j < num_resources; j++)
    {
      printf(" %d", matrix[i][j]);
    }
  }
}

void calculateNeed()
{
  for (int i = 0; i < num_processes; i++)
  {
    for (int j = 0; j < num_resources; j++)
    {
      need[i][j] = max[i][j] - allocation[i][j];
    }
  }
}

void bankerAlgo()
{
  int k = 0, flag, finish[10], safeSequence[10];

  // declare all processes as incomplete
  for (int i = 0; i < num_processes; i++)
  {
    finish[i] = 0;
  }

  for (int i = 0; i < num_processes; i++)
  {
    flag = 0;
    if (finish[i] == 0)
    {
      for (int j = 0; j < num_resources; j++)
      {
        if (need[i][j] > available[j])
        {
          flag = 1;
          break;
        }
      }
      if (flag == 0)     {
        finish[i] = 1;
        safeSequence[k] = i;
        k++;

        for (int j = 0; j < num_resources; j++)
        {
          available[j] = available[j] + allocation[i][j];
        }
        i = -1;
      }
    }
  }
  flag = 0;
  for (int i = 0; i < num_processes; i++)
  {
    if (finish[i] == 0)
    {
      printf("The system is in a deadlock state\n");
      flag = 1;
      break;
    }
  }
  if (flag == 0)
  {
    printf("The system is in a safe state. The safe sequence is: \n");
    for (int i = 0; i < num_processes; i++)
    {
      printf("P%d ", safeSequence[i]);
    }
  }
}

int main()
{
  int j;

  printf("Enter the number of processes: ");
  scanf("%d", &num_processes);
  printf("Enter the number of resources: ");
  scanf("%d", &num_resources);

  printf("Enter the initial allocation matrix: \n");
  readMatrix(allocation);
  printf("Enter the maximum requirement matrix: \n");
  readMatrix(max);
  printf("Enter available resources: \n");
  for (int j = 0; j < num_resources; j++)
  {
    scanf("%d", &available[j]);
  }

  printf("Initial allocation matrix: ");
  displayMatrix(allocation);
  printf("\n");

  printf("Maximum requirements matrix: ");
  displayMatrix(max);
  printf("\n");

  printf("Available resources: ");
  for (int j = 0; j < num_resources; j++)
  {
    printf(" %d", available[j]);
  }

  calculateNeed();
  printf("\n");
  printf("The need is: \n");
  displayMatrix(need);
  printf("\n");
  bankerAlgo();
}
