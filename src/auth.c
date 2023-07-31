#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\nBank Management System\n\nUser Login: ");
    scanf("%s", a);

    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }

    printf("\nEnter the password to login: ");
    scanf("%s", pass);

    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen(USERS, "r")) == NULL)
    {
        printf("\nError! opening file");
        exit(1);
    }

    int id;
    while (fscanf(fp, "%d %s %s", &id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "\nno user found";
}

void registerAcc(char login[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\nBank Management System\n\nLogin: ");
    scanf("%s", login);

    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }

    printf("\nPassword: ");
    scanf("%s", pass);

    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }

    FILE *file;
    char userName[50];
    char userPass[50];
    int id;
    int counter = 0;

    if ((file = fopen("./data/users.txt", "r")) == NULL) 
    {
        perror("ERROR! opening file");
        exit(1);
    }

    while(fscanf(file, "%d %s %s", &id, userName, userPass) != EOF) 
    {
        if (strcmp(userName, login) == 0) {
            printf("\nERROR! name `%s` already exists\n", userName);
            fclose(file);
            exit(1);
        }
        counter++; 
    }
    fclose(file);

    id = id + 1;
    if (counter == 0)
    {
        id = 0;
    }

    if ((file = fopen("./data/users.txt", "a")) == NULL)
    {
        perror("Error! opening file");
        exit(1);
    }
    fprintf(file, "%d %s %s\n\n", id, login, pass);

    fclose(file);
}
