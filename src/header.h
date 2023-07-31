#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[50];
    char country[50];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

const char *getPassword(struct User u);
void printRecord(struct Record *r, struct User u);

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerAcc(char a[50], char pass[50]);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void updateAcc(struct User u);
