#include <stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
    char name[50];
    int acc_no;
    float balance;
} Account;




void set_color(int color);
void create_account();
void deposite_money();
void withdraw_money();
void check_balance();

int main()
{
    int c;
    label:
    
    set_color(10);
    printf("\n\n\n\n         ***WELCOME TO SANDEEP,S BANK***        \n\n\n\n");
    set_color(13);
    printf("\n1.Create Account");
    set_color(13);
    printf("\n2.Deposite Money");
    set_color(13);
    printf("\n3.Withdraw Money");
    set_color(13);
    printf("\n4.Check balance");
    set_color(13);
    printf("\n5.Exit");
    set_color(9);
    printf("\nEnter your choice :");
    scanf("%d", &c);

    switch (c)
    {
    case 1 :
        set_color(12);
        create_account();
        break;
    case 2 :
        deposite_money();
        break;
    case 3 :
        withdraw_money();
        break;
    case 4 :
        check_balance();
        break;
    case 5 :
        printf("Closing the Bank ! THANKS FOR VISIT...\n");
        return 0;
        break;
    
    default:
        printf("invalid Choice");
        break;
    }

    goto label;

    return 0;
}

void create_account(){
    Account acc;

    FILE *file = fopen("account.dat", "ab+");
   if (file == NULL)
   {
    printf("Unable to open file");
   }
   char c;
   while ((c = getchar()) != '\n' && c != EOF);
    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
   int ind =  strcspn(acc.name, "\n");
    acc.name[ind] = '\0';

   printf("Enter your Account :");
   scanf("%d", &acc.acc_no);

   acc.balance = 0;

   fwrite(&acc, sizeof(acc), 1, file);
   fclose(file);

   printf("\nAccount Created Successfully !");

   
   
}

void deposite_money(){

    FILE *file = fopen("account.dat", "rb+");
    if (file == NULL)
    {
        printf("\nUnable to open the account file !!!\n");
    }
    

int money;
int acc_no;
Account acc_r;
printf("\nEnter Your Account Number :");
scanf("%d", &acc_no);
printf("\nEnter Amount to Deposit:");
scanf("%d", &money);

while(fread(&acc_r, sizeof(acc_r), 1, file)){
if (acc_r.acc_no == acc_no)
{
    acc_r.balance +=money;
    fseek(file, -sizeof(acc_r), SEEK_CUR);
    fwrite(&acc_r, sizeof(acc_r), 1, file);
    fclose(file);
    printf("Hello %s sir ", acc_r.name);
    printf("Successfully deposited Rs. %d in your account ... ", money);
    return;
}



}
fclose(file);
printf("Sir Money Could not be deposited as the Account no. %d was not found in our record.", acc_no);

}

void withdraw_money(){
   
 FILE *file = fopen("account.dat", "rb+");
    if (file == NULL)
    {
        printf("\nUnable to open the account file !!!\n");
    }
    

int money;
int acc_no;
Account acc_r;
printf("\nEnter Your Account Number :");
scanf("%d", &acc_no);
printf("\nEnter Amount to Withdrawn:");
scanf("%d", &money);

while(fread(&acc_r, sizeof(acc_r), 1, file)){
if (acc_r.acc_no == acc_no)
{
   if (acc_r.balance >= money)
   {
    acc_r.balance -= money;
     fseek(file, -sizeof(acc_r), SEEK_CUR);
    fwrite(&acc_r, sizeof(acc_r), 1, file);
    fclose(file);
    printf("Hello %s sir ", acc_r.name);
    printf("Successfully Withdrawn Rs. %d in your account ... ", money);
    printf("%s sir your remaining amount is %.2f", acc_r.name, acc_r.balance);
    return;
   }else
   {
    printf("Insufficient Balance !");
   }
   fclose(file);
   return;
   
   
}




}
fclose(file);
printf("Sir Money Could not be Withdrawn as the Account no. %d was not found in our record.", acc_no);

}


void check_balance(){
FILE *file = fopen("account.dat", "rb");
if (file == NULL)
   {
    printf("Unable to open file");
   }

    int acc_no;
    Account acc_read;
printf("\nEnter your Account Number :");
scanf("%d", &acc_no);

while(fread(&acc_read, sizeof(acc_read), 1, file)){

if(acc_read.acc_no == acc_no){
    printf("Welcome %s ! ", acc_read.name);
    printf("Your Current Balance is Rs. %.2f", acc_read.balance);
    fclose(file);
    return;
}

}
fclose(file);
printf("\n Account No. %d was not found.\n", acc_no);

}

void set_color(int color){

SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}

    
