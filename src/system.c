#include "header.h"

const char *RECORDS = "./data/records.txt";


void printRecord(struct Record *r, struct User u) {
    printf("ID: %d", r->id);
    printf("UserID: %d", u.id);
    printf("Name: %s", r->name);
    printf("Country: %s", r->country);
    printf("Phone: %d", r->phone);
    printf("Account Type: %s", r->accountType);
    printf("Account Number: %d", r->accountNbr);
    printf("Amount: %.2f", r->amount);
    printf("Date: %d/%d/%d", r->deposit.day, r->deposit.month, r->deposit.year);
}

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
		          &r->userId,
		          name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
	        u.id,
	        u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("Enter:\n\n [0] - Try again\n [1] - Main Menu\n [2] - Exit!\n");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("Enter:\n\n [1] - Main Menu\n [0] - Exit!\n\n");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");

    invalid:

    printf("Enter:\n\n [1] - Main Menu\n [0] - Exit!\n\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

    noAccount:

    system("clear");
    printf("============= New record =============\n");

    printf("\nEnter today's date(mm/dd/yyyy): ");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);

    printf("\nEnter the account number: ");
    scanf("%d", &r.accountNbr);

    for (int i = 0; i < 50; i++)
    {
        r.name[i] = u.name[i];
    }
    r.userId = u.id; 

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }

    printf("\nEnter the country: ");
    scanf("%s", r.country);
    printf("\nEnter the phone number: ");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n  -> saving\n  -> current\n  -> fixed01(for 1 year)\n  -> fixed02(for 2 years)\n  -> fixed03(for 3 years)\n\nEnter your choice: ");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);
    fclose(pf);

    printRecord(&r, u);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number: %d\nDeposit Date: %d/%d/%d \nCountry: %s \nPhone number: %d \nAmount deposited: $%.2f \nType Of Account: %s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void updateAcc(struct User u) {
    system("clear");

    int phone, accountNbr;
    char country[100];

    FILE * f;
    struct Record r;
    char userName[50];

    if ((f = fopen(RECORDS, "r+")) == NULL)  {
        printf("Error! opening file");
        exit(1);
    }

    printf("\nWrite account number that you want to change: ");
    scanf("%d", &accountNbr);

    int exist = 0;

    while(getAccountFromFile(f, userName, &r)) {
        if (strcmp(userName, u.name) == 0 && accountNbr == r.accountNbr) {
            exist = 1;
        }      
    }

    if (exist == 0)  {
        printf("\nInvalid Account Number\n");
        stayOrReturn(1, mainMenu, u);
    }
    
    int n;

    printf("\nWhich information do you want to update?\n\n1 -> Phone number\n2 -> Country\n\n");
    scanf("%d", &n);

    system("clear");

    if (n == 1) 
    {
        printf("New phone number: ");
        scanf("%d", &phone);
    } 
    else if (n == 2) 
    {
        printf("New country: ");
        scanf("%s", country);
    }
    else 
    {
        printf("Invalid operation!\n");
        stayOrReturn(1, mainMenu, u);
    }

    FILE * tmp;
    
    if ((tmp = fopen( "./data/template.txt", "w")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    struct Record rec;
    userName[0] = '\0';
    
    if ((f = fopen(RECORDS, "r+")) == NULL)  {
        printf("Error! opening file");
        exit(1);
    }

    while (getAccountFromFile(f, userName, &rec)) {
        if (strcmp(userName, u.name) == 0 && accountNbr == rec.accountNbr) {
            if (n == 1) 
            {
                rec.phone = phone;
            }
            else if (n == 2) 
            {
                strcpy(rec.country, country);
            }
        }
        saveAccountToFile(tmp, u, rec);
    }

    remove(RECORDS);
    rename("./data/template.txt", RECORDS);

    fclose(f); 
    fclose(tmp);
    success(u);
}
