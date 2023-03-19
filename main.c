#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int main() {
    int useCase;
    //user and admins
    char * user[2][2];
    char * admin[1][1];
    char * officer[1][1];

    char *usernameUser1 = "JohnUser";
    char *passwordUser1 = "Passw0rd";
    char *usernameUser2 = "JaneUser";
    char *passwordUser2 = "PaSsWoRd";

    char *usernameAdmin1 = "JohnAdmin";
    char *passwordAdmin1 = "Passw0rd";

    char *usernameOfficer = "JaneOfficer";
    char *passwordOfficer = "icountvotes";

    bool run = true;

    void useExp();
    void admExp();
    void polExp();


    do{
        printf("Key: User = 1 | Admin = 2 | Polling Officer = 3 | Exit = 0\n");
        printf("What type of user are you?\n");

        scanf("%d", &useCase);

        //Clears the scanf buffer
        fflush(stdin);

        //Separates the outcomes for use case selection.
        //User, Admin, Polling officer, quit or invalid response.
            switch (useCase) {
                case 1:
                    //User
                    useExp();
                    break;
                case 2:
                    //Admin
                    admExp();
                    break;
                case 3:
                    //Polling Officer
                    polExp();
                    break;
                case 0:
                    //Quit
                    printf("Quiting program, have a great day!\n");
                    run = false;
                    break;
                default:
                    //Error
                printf("Invalid user\n");
                printf("Please enter the correct number for type of account.\n");
            }
    }while(run == true);
    return 0;
}

void useExp() {
    int logReg;

    printf("Key: Login = 1 | Register = 2\n");
    printf("Would you like to login or register?\n");
    scanf("%d", &logReg);
    //Clears the scanf buffer
    fflush(stdin);

};

void admExp() {
    int logReg;

    printf("Key: Login = 1 | Register = 2\n");
    printf("Would you like to login or register?\n");
    scanf("%d", &logReg);
    //Clears the scanf buffer
    fflush(stdin);

};

void polExp() {
    int logReg;

    printf("Key: Login = 1 | Register = 2\n");
    printf("Would you like to login or register?\n");
    scanf("%d", &logReg);
    //Clears the scanf buffer
    fflush(stdin);

};
