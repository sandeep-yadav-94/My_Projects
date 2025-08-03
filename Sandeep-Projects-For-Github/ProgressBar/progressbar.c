#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

const int MAX_TASKS = 5;
const int BAR_LENGTH = 50;

typedef struct
{
    int id;
    int progress;
    int step;
} Task;

void bar(Task task)
{

    int bars_to_show = (BAR_LENGTH * task.progress) / 100;

    printf("\nTask %d: [", task.id);

    for (int i = 0; i < BAR_LENGTH; i++)
    {
        if (i < bars_to_show)
        {
            printf("=");
        }
        else
        {
            printf(" ");
        }
    }

    printf("] %d%%", task.progress);
}

int main()
{

    Task tasks[MAX_TASKS];
    srand(time(NULL));

    for (int i = 0; i < MAX_TASKS; i++)
    {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % 5 + 1;
    }

    int tasks_incomplete = 1;
    while (tasks_incomplete)
    {
        tasks_incomplete = 0;
        system("cls");
        for (int i = 0; i < MAX_TASKS; i++)
        {
            tasks[i].progress += tasks[i].step;
            if (tasks[i].progress > 100)
            {
                tasks[i].progress = 100;
            }
            else if (tasks[i].progress < 100)
            {
                tasks_incomplete = 1;
            }
            bar(tasks[i]);
        }

        sleep(1);
    }

    printf("All Tasks Completed !");

    return 0;
}