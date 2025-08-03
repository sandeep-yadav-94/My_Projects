#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 50
#define HEIGHT 20
#define MAX_LENGTH 100

int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];
int length = 5;
int direction = 2;
int foodX, foodY;
int score = 0;
bool gameover = FALSE;
int powerUpX, powerUpY;
int obstacleX, obstacleY;
bool hasPowerUp = false;
bool hasObstacle = false;

void gotoxy(int x, int y);
void showLoading();
void showInstructions();
void setup();
void draw();
void input();
void logic();
void delay(int milliseconds);
void hideCursor();


int main()
{
    showLoading();
    showInstructions();
    setup();

    while (!gameover)
    {
        draw();
        input();
        logic();
        delay(100 - (score / 10));
    }

    printf("Game Over! Final Score: %d\n", score);

    return 0;
}

void gotoxy(int x, int y)
{

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showLoading()
{

    system("cls");
    gotoxy(36, 14);
    printf("Loading...");
    gotoxy(30, 15);
    for (int i = 0; i <= 20; i++)
    {
        printf("%c", 177);
        sleep(1);
    }
}

void showInstructions()
{

    system("cls");
    printf("Welcome to Snake Game!\n");
    printf("Here are the game rules:\n\n");
    printf("1. Use 'W' to move Up, 'S' to move Down, 'A' to move Left, 'D' to move Right.\n");
    printf("2. Collect food (F) to grow the snake and earn points.\n");
    printf("3. Collect power-ups (P) to gain bonus points.\n");
    printf("4. Avoid obstacles (X) and walls (#) as hitting them will end the game.\n");
    printf("5. The longer the snake, the faster the game becomes.\n\n");
    printf("Press any key to start the game...\n");
    _getch();
}

void setup()
{

    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        snakeX[i] = WIDTH / 2 + i;
        snakeY[i] = HEIGHT / 2;
    }
    foodX = rand() % (WIDTH - 2) + 1;
    foodY = rand() % (HEIGHT - 2) + 1;
    powerUpX = rand() % (WIDTH - 2) + 1;
    powerUpY = rand() % (HEIGHT - 2) + 1;
    obstacleX = rand() % (WIDTH - 2) + 1;
    obstacleY = rand() % (HEIGHT - 2) + 1;
}

void draw()
{

    gotoxy(0, 0);
    for (int i = 0; i <= HEIGHT; i++)
    {
        for (int j = 0; j <= WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT || j == 0 || j == WIDTH)
            {
                printf("#");
            }
            else if (i == foodY && j == foodX)
            {
                printf("F");
            }
            else if (i == powerUpY && j == powerUpX)
            {
                printf("P");
            }
            else if (i == obstacleY && j == obstacleX)
            {
                printf("X");
            }
            else
            {
                bool printSnake = false;
                for (int k = 0; k < length; k++)
                {
                    if (snakeX[k] == j && snakeY[k] == i)
                    {
                        printf("O");
                        printSnake = true;
                        break;
                    }
                }
                if (!printSnake)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void input(){

 if (_kbhit()) {
        switch (_getch()) {
            case 'w': if (direction != 1) direction = 0; break;
            case 's': if (direction != 0) direction = 1; break;
            case 'a': if (direction != 3) direction = 2; break;
            case 'd': if (direction != 2) direction = 3; break;
        }
    }
}

void logic(){

int prevX = snakeX[0];
    int prevY = snakeY[0];
    int tempX, tempY;
    
    switch (direction) {
        case 0: snakeY[0]--; break;
        case 1: snakeY[0]++; break;
        case 2: snakeX[0]--; break;
        case 3: snakeX[0]++; break;
    }

    for (int i = 1; i < length; i++) {
        tempX = snakeX[i];
        tempY = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }
    
    // Collision with walls
    if (snakeX[0] <= 0 || snakeX[0] >= WIDTH || snakeY[0] <= 0 || snakeY[0] >= HEIGHT) {
        gameover = true;
    }
    
    // Collision with itself
    for (int i = 1; i < length; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameover = true;
        }
    }
    
    // Eating food
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        length++;
        score += 10;
        foodX = rand() % (WIDTH - 2) + 1;
        foodY = rand() % (HEIGHT - 2) + 1;
    }
    
    // Power-Up
    if (snakeX[0] == powerUpX && snakeY[0] == powerUpY) {
        score += 20;
        powerUpX = rand() % (WIDTH - 2) + 1;
        powerUpY = rand() % (HEIGHT - 2) + 1;
    }
    
    // Collision with obstacle
    if (snakeX[0] == obstacleX && snakeY[0] == obstacleY) {
        gameover = true;
    }   
}

void delay(int milliseconds) {
    Sleep(milliseconds);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}