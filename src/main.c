#include "header.h"

void mainMenu(struct User u)
{
    int option;
    system("clear");
    printf("\n============== ATM - MANAGEMENT - SYSTEM =============\n\n");
    printf("-->> Feel free to choose one of the options below <<--\n\n");
    printf("[1] - Create a new account\n\n");
    printf("[2] - Update account information\n\n");
    printf("[3] - Check accounts\n\n");
    printf("[4] - Check list of owned account\n\n");
    printf("[5] - Make Transaction\n\n");
    printf("[6] - Remove existing account\n\n");
    printf("[7] - Transfer ownership\n\n");
    printf("[8] - Exit\n\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAccount(u);
        break;
    case 2:
        updateAccount(u);
        break;
    case 3:
        checkAccount(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        makeTransaction(u);
        break;
    case 6:
        deleteAccount(u);
        break;
    case 7:
        transferOwner(u);
        break;
    case 8:
        system("clear");
        break;
    default:
        system("clear");
        printf("Invalid operation!\n");
        break;
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    printf("\n======== ATM - MANAGEMENT - SYSTEM ========\n\n");
    printf("-->> Feel free to login / register :\n\n");
    printf("[1] - Login\n\n");
    printf("[2] - Register\n\n");
    printf("[3] - Exit\n\n");
    while (!r)
    {   
        printf("Enter: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {   
                printf("\n✔ Password Match! ✔\n\n");
            }
            else
            {
                printf("\n✖ Wrong Password or User Name ✖\n\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            registerMenu(u->name, u->password);
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n\n");
        }
    }
};

int main()
{
    struct User u;

    initMenu(&u);
    mainMenu(u);
    return 0;
}
