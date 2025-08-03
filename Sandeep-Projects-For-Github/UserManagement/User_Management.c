#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h> 

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

typedef struct
{
    char username[30];
    char password[30];
} User;

User users[MAX_USERS];
int user_count = 0;


void set_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void register_user()
{
    if (user_count == MAX_USERS)
    {
        set_color(12); 
        printf("\nMaximum %d users are supported! No more users are allowed!!!\n", MAX_USERS);
        set_color(7); 
        return;
    }

    int new_index = user_count;

    set_color(10); 
    printf("\n*************** Register a new User ***************\n");
    set_color(7); 

    printf("\nEnter Username: ");
    fgets(users[new_index].username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(users[new_index].username);

    
    printf("\nEnter Password: ");
    input_password(users[new_index].password);

    user_count++;
    set_color(10); 
    printf("\nRegistration Successful!\n");
    set_color(7); 
}

int login_user()
{
    char username[CREDENTIAL_LENGTH], password[CREDENTIAL_LENGTH];

    set_color(9); 
    printf("\n*************** Login to Your Account ***************\n");
    set_color(7); 

    printf("\nEnter Username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);

    
    printf("\nEnter Password: ");
    input_password(password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return i;
        }
    }

    return -1;
}

void fix_fgets_input(char* string)
{
    int index = strcspn(string, "\n");
    string[index] = '\0';
}

void input_password(char* password)
{
    int i = 0;
    char ch;

    while (1)
    {
        ch = _getch();
        if (ch == '\r')
        {
            break;
        }
        password[i++] = ch;
        printf("*");
    }

    password[i] = '\0';
}

int main()
{
    int user_index;
    int option;

label:
    set_color(14); 
    printf("\n\n************** Welcome to User Management **************\n");
    set_color(7); 

    printf("\n1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Select an option: ");
    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 1:
        register_user();
        break;

    case 2:
        user_index = login_user();
        if (user_index >= 0)
        {
            set_color(10); 
            printf("\nLogin successful! Welcome, %s!\n", users[user_index].username);
            set_color(7); 
        }
        else
        {
            set_color(12); 
            printf("\nLogin failed! Incorrect username or password!\n");
            set_color(7); 
        }
        break;

    case 3:
        set_color(8); 
        printf("\nExiting Program...\n");
        set_color(7); 
        return 0;
        break;

    default:
        set_color(12); 
        printf("\nInvalid Option. Please try again.\n");
        set_color(7); 
        break;
    }

    goto label;
    return 0;
}

/*
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define max_users 10
int user_count = 0;

typedef struct
{
  char username[30];
  char password[30];
} User;
User users[max_users];

void input_password(char *password);
void fix_fgets_input(char *string);
void register_user();
int login_user();

void set_color(int color)
{

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{
  int option;
  int user_index;
label:
  set_color(13);
  printf("\n\n\n\n***************WELCOME TO THE PORTAL***************\n");
  set_color(11);
  printf("1.Register\n");
  set_color(9);
  printf("2.Login\n");
  set_color(14);
  printf("3.Exit from Portal\n");
  set_color(15);
  scanf("%d", &option);
  getchar();
  switch (option)
  {
  case 1:
    register_user();
    break;
  case 2:
    user_index = login_user();
    if (user_index >= 0)
    {
      set_color(10);
      printf("\nLogin successful! Welcome, %s!\n\n\n\n", users[user_index].username);
      set_color(7);
    }
    else
    {
      set_color(12);
      printf("\nLogin failed! Incorrect username or password!\n\n\n\n");
      set_color(7);
    }
    break;
  case 3:
    set_color(8);
    printf("\nExiting Program...\n");
    set_color(7);
    return 0;
    break;

  default:
    set_color(12);
    printf("\nInvalid input ! please enter a valid input !\n\n\n");
    set_color(7);
    break;
  }

  goto label;
  return 0;
}

void register_user()
{
  if (user_count == max_users)
  {
    set_color(12);
    printf("\nSorry we support maximum only %d User,s Registeration at a time !\n\n\n\n", max_users);
  }
  int new_index = user_count;
  set_color(5);
  printf("\n............Register To a New User............\n");
  set_color(9);
  printf("Enter Username :");
  fgets(users[new_index].username, 30, stdin);
  fix_fgets_input(users[new_index].username);
  printf("Enter Password :");
  input_password(users[new_index].password);
  set_color(10);
  printf("\nRegisteration Successfull ! \n");
  user_count++;
}

int login_user()
{
  set_color(5);
  printf("\n............Login To a New User............\n");
  char username[30], password[30];
  set_color(9);
  printf("Enter Username :");
  fgets(username, 30, stdin);
  fix_fgets_input(username);
  printf("Enter Password :");
  input_password(password);
  for (int i = 0; i < max_users; i++)
  {
    if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
    {
      return i;
    }
  }

  return -1;
}

void fix_fgets_input(char *string)
{

  int index = strcspn(string, "\n");
  string[index] = '\0';
}

void input_password(char *password)
{
  int i = 0;
  char ch;
  while (1)
  {
    ch = _getch();
    if (ch == '\r')
    {
      break;
    }
    password[i++] = ch;
    set_color(8);
    printf("*");
  }
  password[i] = '\0';
}


*/