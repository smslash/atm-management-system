#include "header.h"

void mainMenu(struct User u)
{
    int option;
    system("clear");
    printf("================ ATM MANAGEMENT SYSTEM ===============\n\n");
    printf("-->> Feel free to choose one of the options below <<--\n\n");
    printf("[1]- Create a new account\n\n");
    printf("[2]- Update account information\n\n");
    printf("[3]- Check accounts\n\n");
    printf("[4]- Check list of owned account\n\n");
    printf("[5]- Make Transaction\n\n");
    printf("[6]- Remove existing account\n\n");
    printf("[7]- Transfer ownership\n\n");
    printf("[8]- Exit\n\n\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateAcc(u);
        break;
    case 3:
        // student TODO : add your **Check the details of existing accounts** function
        // here
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // student TODO : add your **Make transaction** function
        // here
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        // here
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    printf("\n====== ATM MANAGEMENT SYSTEM ======\n\n");
    printf("-->> Feel free to login / register :\n\n");
    printf("[1]- login\n\n");
    printf("[2]- register\n\n");
    printf("[3]- exit\n\n\n");
    printf("Enter: ");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("Password Match!\n");
            }
            else
            {
                printf("Wrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            registerAcc(u->name, u->password);
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
