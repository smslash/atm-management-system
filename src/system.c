#include "header.h"

const char *RECORDS = "./data/records.txt";


int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r->id,
		          &r->userId,
		          r->name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
            r.id,
	        r.userId,
	        r.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success! ✔\n\n");

    invalid:;

    printf("Choose :\n\n[1] - Main Menu\n[0] - Exit\n\n");
    printf("Enter: ");
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

void createNewAccount(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];

    noAccount:;
    
    FILE *pf;

    if ((pf = fopen(RECORDS, "a+")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }
    
    system("clear");
    printf("\n=========> New Record <=========\n");

    printf("\nEnter today's date(mm/dd/yyyy): ");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number: ");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {   
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            fclose(pf);
            goto noAccount;
        }
    }

    u.id = userID(u);

    if (u.id == -1) 
    {
        printf("Error when receiving user ID\n\n");
    }

    r.userId = u.id;

    r.id = cr.id + 1;

    strcpy(r.name, u.name);

    printf("\nEnter the country: ");
    scanf("%s", r.country);

    printf("\nEnter the phone number: ");
    scanf("%s", r.phone);

    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);

    printf("\nChoose the type of account :\n\t-> saving\n\t-> current\n\t-> fixed01 (for 1 year)\n\t-> fixed02 (for 2 years)\n\t-> fixed03 (for 3 years)\n\nEnter your choice: ");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char name[100];
    struct Record r;

    FILE *f;

    if ((f = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    system("clear");
    printf("\n=======> All accounts from user, %s <======\n\n", u.name);

    while (getAccountFromFile(f, name, &r))
    {
        if (strcmp(r.name, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number: %d\nDeposit Date: %d/%d/%d \ncountry: %s \nPhone number: %s \nAmount deposited: $%.2f \nType of Account: %s\n",
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
    fclose(f);
    success(u);
}

void updateRecord(struct User u, struct Record r, int option, int l)
{
    struct Record cr;

    FILE *file1;

    if ((file1 = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    FILE *file2;

    if ((file2 = fopen("./data/template.txt", "w")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    int ans = 0;

    while (getAccountFromFile(file1, u.name, &cr))
    {   
        ans = ans + 1;
        if (ans == l) {
            if (option == 1) 
            {
                strcpy(cr.phone, r.phone);
            } 
            else if (option == 2) 
            {
                strcpy(cr.country, r.country);
            }
        }
        
        saveAccountToFile(file2, u, cr);
    }

    fclose(file1);
    fclose(file2);

    remove(RECORDS);
    rename("./data/template.txt", RECORDS);
}

void updateAccount(struct User u)
{

account:;
    struct Record r;
    struct Record cr;
    int option;

    printf("\nWrite account number that you want to change: ");
    scanf("%d", &r.accountNbr);
    
    FILE *f;

    if ((f = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    int exist = 0;
    int n = 0;

    while (getAccountFromFile(f, u.name, &cr))
    {   
        n = n + 1;
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            exist = 1;
            break;
        }
    }

    if (!exist) 
    {
        system("clear");
        printf("\n✖ The account does not exist ✖\nTry again ...\n");
        goto account;
    }

    fclose(f);

invalid:;
    printf("\nWhich information do you want to update?\n\n[1] -> Phone Number\n[2] -> Country\n\nEnter: "); 
    scanf("%d", &option);

    if (option == 1)
    {   
        system("clear");
        printf("\nNew phone number: ");
        scanf("%s", r.phone);
    } 
    else if (option == 2)
    {
        system("clear");
        printf("\nNew country: ");
        scanf("%s", r.country);
    }
    else
    {
        system("clear");
        printf("Insert a valid operation!\n\n");
        goto invalid;
    }

    updateRecord(u, r, option, n);

    success(u);
}

void checkAccount(struct User u)
{
    struct Record r;
    struct Record cr;

    printf("\nEnter the account number: ");
    scanf("%d", &r.accountNbr);

    FILE *f;

    if ((f = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }


    int exist = 0;
    while (getAccountFromFile(f, u.name, &cr))
    {
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {   
            system("clear");
            printf("\nAccount number: %d\nDeposit Date: %d/%d/%d \nCountry: %s \nPhone number: %s \nAmount deposited: $%.2f \nType of Account: %s\n",
                   cr.accountNbr,
                   cr.deposit.month,
                   cr.deposit.day,
                   cr.deposit.year,
                   cr.country,
                   cr.phone,
                   cr.amount,
                   cr.accountType);

            if (strcmp(cr.accountType, "saving") == 0 ) 
            {   
                printf("\n\n->You will get $%.2f as interest on day 10 of every month", cr.amount * 0.07 / 12);
            }
            else if (strcmp(cr.accountType, "fixed01") == 0 ) 
            {
                cr.deposit.year++;
                printf("\n\n->You will get $%.2f as interest on %d/%d/%d", cr.amount * 0.04, cr.deposit.month, cr.deposit.day, cr.deposit.year);
            }
            else if (strcmp(cr.accountType, "fixed02") == 0 ) 
            {
                cr.deposit.year+=2;
                printf("\n\n->You will get $%.2f as interest on %d/%d/%d", cr.amount * 0.05 * 2, cr.deposit.month, cr.deposit.day, cr.deposit.year);
            }
            else if (strcmp(cr.accountType, "fixed03") == 0 ) 
            {
                cr.deposit.year+=3;
                printf("\n\n->You will get $%.2f as interest on %d/%d/%d", cr.amount * 0.08 * 3, cr.deposit.month, cr.deposit.day, cr.deposit.year);
            }
            else if (strcmp(cr.accountType, "current") == 0 ) 
            {
                printf("\n\n->You will not get interests because the account is of type current");
            }
            exist = 1;
        }
        
    }
    
    fclose(f);

    if (exist) 
    {
        success(u);
    }
    else
    {
        int option;
        system("clear");
        printf("\n✖ No such account ✖\n\n");

    invalid:;

        printf("Choose :\n\n[1] - Main Menu\n[0] - Exit\n");
        printf("Enter: ");
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
}


void deleteAccount(struct User u)
{
    here:;

    struct Record r;
    struct Record cr;

    printf("\nEnter the account number that you want to delete: ");
    scanf("%d", &r.accountNbr);

    FILE *f;

    if ((f = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    int option, ans = 0, exist = 0;

    while (getAccountFromFile(f, u.name, &cr))
    {   
        ans = ans + 1;
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {   
            exist = 1;
            break;
        }
    }

    fclose(f);

    if (!exist) {
        system("clear");

        printf("\nThere is no such account");

        invalid:;

        printf("\nChoose :\n\n[1] - Main Menu\n[2] - Try Again\n[0] - Exit\n\nEnter: ");
        scanf("%d", &option);

        system("clear");

        if (option == 1)
        {
            mainMenu(u);
        }
        else if (option == 2)
        {
            goto here;
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

    FILE *file1;

    if ((file1 = fopen("./data/template.txt", "w")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    FILE *file2;

    if ((file2 = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    int res = 0;

    while (getAccountFromFile(file2, u.name, &cr))
    {   
        res = res + 1;

        if (res == ans) 
        {
            exist = 1;
            continue;
        }

        if (exist == 1)
        {
            cr.id = cr.id - 1;
        }

        saveAccountToFile(file1, u, cr);
    }

    fclose(file2);
    fclose(file1);

    remove (RECORDS);
    rename("./data/template.txt", RECORDS);

    success(u);
}

void transferOwner(struct User u)
{
    here:;

    struct Record r;
    struct Record cr;

    printf("\nEnter the account number you want to transfere ownership: ");
    scanf("%d",&r.accountNbr);


    FILE *file;

    if ((file = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    int option, l = 0, exist;
    char owner[50];

    while (getAccountFromFile(file, u.name, &cr))
    {   
        l = l + 1;
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {   
            exist = 1;
            break;
        }
    }

    fclose(file);

    if (!exist){
        system("clear");

        printf("\nThere is no such account\n");
        
        invalid:;
        
        printf("\nChoose :\n\n[1] - Main Menu\n[2] - Try Again\n[0] - Exit\n\nEnter: ");
        scanf("%d", &option);

        system("clear");

        if (option == 1)
        {
            mainMenu(u);
        }
        else if (option == 2)
        {
            goto here;
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

    user:;

    printf("\nWhich user you want transfer ownership?\n\nWrite User Name: ");
    scanf("%s",owner);

    struct User user;

    FILE *file2;

    if ((file2 = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    while (fscanf(file2, "%d %s %s", &user.id, user.name, user.password) != EOF)
    {   
        if (strcmp(user.name, owner) == 0)
        {   
            exist = 1;
            break;
        }
    }

    fclose(file2);

    int input;
    
    if (!exist){
        system("clear");

        printf("\n✖ There is no such user ✖\n");

        invalid_2:;

        printf("\nChoose :\n\n[1] - Main Menu\n[2] - Try Again\n[0] - Exit\n\nEnter: ");
        scanf("%d", &input);

        system("clear");

        if (input == 1)
        {
            mainMenu(u);
        }
        else if (input == 2)
        {
            goto user;
        }
        else if (input == 0)
        {
            goto user;
        }
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid_2;
        }
    }
     
    r.userId = user.id;
    strcpy(r.name, user.name);

    updateOwner(u, r, l);

    success(u);
}

void updateOwner(struct User u, struct Record r, int l){
    
    struct Record cr;

    FILE *file1;

    if ((file1 = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    FILE *file2;

    if ((file2 = fopen("./data/template.txt", "w")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    int ans = 0;
   
    while (getAccountFromFile(file1, u.name, &cr))
    {   
        ans = ans + 1;
        if (ans == l) 
        {
            cr.userId = r.userId;
            strcpy(cr.name, r.name);
        }
    
        saveAccountToFile(file2, u, cr);
    }

    fclose(file1);
    fclose(file2);

    remove (RECORDS);
    rename("./data/template.txt", RECORDS);
}

void updateCash(struct User u, struct Record r, int l){

    struct Record cr;

    FILE *file1;

    if ((file1 = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    FILE *file2;

    if ((file2 = fopen("./data/template.txt", "w")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    int ans = 0;
   
    while (getAccountFromFile(file1, u.name, &cr))
    {   
        ans = ans + 1;
        if (ans == l) {
            cr.amount = r.amount;
        }

        saveAccountToFile(file2, u, cr);
    }

    fclose(file1);
    fclose(file2);

    remove (RECORDS);
    rename("./data/template.txt", RECORDS);

    success(u);
}

void  makeTransaction(struct User u)
{
    here:;

    struct Record r;
    struct Record cr;

    printf("\nEnter the account number of the customer: ");
    scanf("%d", &r.accountNbr);

    FILE *f;

    if ((f = fopen(RECORDS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    double money;
    int option, l = 0, exist = 0;

    while (getAccountFromFile(f, u.name, &cr))
    {   
        l = l + 1;
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {   
            exist = 1;
            break;
        }
    }

    fclose(f);

    if (!exist) {
        printf("Account was not found");
         system("clear");
        printf("\nThere is no such account");

        invalid:;

        printf("\nChoose :\n\n[1] - Main Menu\n[2] - Try Again\n[0] - Exit\n\nEnter: ");
        scanf("%d", &option);

        system("clear");

        if (option == 1)
        {
            mainMenu(u);
        }
        else if (option == 2)
        {
            goto here;
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

    withdraw:;

    printf("\n\nChoose :\n\n[1] -> Deposit\n[2] -> Withdraw\n\nEnter: ");
    scanf("%d", &option);

    if (strcmp(cr.accountType, "fixed01") == 0 || strcmp(cr.accountType, "fixed02")==0 || strcmp(cr.accountType, "fixed03")==0)
    {   
        printf("\nYou cannot deposit or withdraw cash in fixed (fixed01, fixed02, fixed03) accounts!\n\n");
        sleep(2);
        mainMenu(u);
    }

    if (option == 1) 
    {
        printf("\n\nEnter the amount you want to deposit: $");
        scanf("%lf", &money);    
        r.amount = cr.amount + money;
    }
    else if (option == 2)
    {
        printf("\n\nEnter the amount you want to withdraw: $");
        scanf("%lf", &money);
        if(cr.amount < money){
            system("clear");

            printf("\nThe amount you have selected to withdraw exceeds your available balance.\nTry again ...");

            goto withdraw;
        }
        r.amount = cr.amount-money;
    }
    else
    {
        printf("Invalid operation!\n");
        goto withdraw;
    }

    updateCash(u, r, l);
    success(u);
}
