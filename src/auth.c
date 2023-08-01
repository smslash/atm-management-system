#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\nBank Management System\n\nLogin: ");
    scanf("%s", a);

    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    printf("\nPassword: ");
    scanf("%s", pass);

    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
}

const char *getPassword(struct User u)
{
    FILE *f;
    struct User user;

    if ((f = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    while (fscanf(f, "%d %s %s", &user.id, user.name, user.password) != EOF)
    {   
      
        
        if (strcmp(user.name, u.name) == 0)
        {   
            fclose(f);\
            char *buff = user.password;
            return buff;
        }
    }

    fclose(f);
    return "No User Found\n\n";
}

const int userID(struct User u)
{
    FILE *f;

    if ((f = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    struct User a;

    while (fscanf(f, "%d %s %s", &a.id, a.name, a.password) != EOF)
    {   
        if (strcmp(a.name, u.name) == 0)
        {   
            fclose(f);
            return a.id;
        }
    }

    fclose(f);
    return -1;
}

void registerMenu(char a[50], char pass[50])
{   
    struct termios oflags, nflags;
    struct User user;

    here:

    system("clear");
    printf("\nRegistration Menu\n\nUser Name: ");
    scanf("%s", a);

    FILE *file1;
    int option;

    if ((file1 = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    while (fscanf(file1, "%d %s %s", &user.id, user.name, user.password) != EOF)
    {   
      
        
        if (strcmp(user.name, a) == 0)
        {   
            fclose(file1);
            system("clear");
            printf("\n✖ The user with the same name already exists ✖\n\n");

            invalid:

            printf("Choose :\n\n[1] - Try Again\n[0] - Exit!\n\n");
            printf("Enter: ");
            scanf("%d", &option);
            system("clear");
            if (option == 1)
            {
               goto here;
            }
            else if (option == 0)
            {
                exit(1);
            }
            else
            {
                printf("Insert a valid operation!\n\n");
                goto invalid;
            }
            
        }
    }
    
    fclose(file1);

    FILE *file2;

    if ((file2 = fopen(USERS, "a+")) == NULL)
    {
        printf("Error! opening file\n\n");
        exit(1);
    }

    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    printf("\nPassword: ");
    scanf("%s", pass);

    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    user.id = user.id + 1;

    if (user.id > 100 || user.id < 0)
    {
        user.id = 0;
    }

    fprintf(file2, "%d %s %s\n\n", user.id , a, pass);

    fclose(file2);
}

