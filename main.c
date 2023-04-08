#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

//user and admins

void userLogin();
void staffLogin();

void loggedIn();

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

char filename[FILENAME_SIZE];
char buffer[MAX_LINE];

FILE *usernameData;
FILE *passwordData;



int main() {
    int useCase;

    usernameData = fopen("username_column.txt", "w");
    fprintf(usernameData, "JohnUser\n");
    fclose(usernameData);

    passwordData = fopen("password_column.txt", "w");
    fprintf(passwordData, "Passw0rd\n");
    fclose(passwordData);

//    char enteredName[] = "JohnUser\n";

//
//     "JohnUser",
//    "Passw0rd",
//    "JaneUser",
//    "PaSsWoRd",
//

//   "JohnAdmin";
//    "PASSw0rd";
//
//
//    "JaneOfficer";
//    "icountvotes";
//
//
    bool run = true;
//
    void useExp();
    void admExp();
    void polExp();

//
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
                    userLogin();
                    break;
                case 2:
                    //Admin
                    staffLogin();
                    break;
                case 3:
                    //Polling Officer
                    staffLogin();
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

void userLogin() {
    int logReg;

    printf("Key: Login = 1 | Register = 2\n");
    printf("Would you like to login or register?\n");
    scanf("%d", &logReg);
    //Clears the scanf buffer
    fflush(stdin);

    switch (logReg) {
        case 1:
            printf("Please enter username: ");
            char username[20];
           fgets(username, 21, stdin);
//            strncat(username, "\n", 1);
            char password[20];
            printf("Please enter password: ");
            fgets(password, 21, stdin);

            usernameData = fopen("username_column.txt", "r");
            bool keep_reading = true;
            int current_line = 1;
            int readLine = 0;
            do {
                fgets(buffer, MAX_LINE, usernameData);
                if(feof(usernameData)){
                    printf("Not found!\n");
                    keep_reading = false;
                } else if(strcmp(buffer, username) == 0){
                    printf("Correct username!\n");
                    readLine++;
                    passwordData = fopen("password_column.txt", "r");
                    do {
                        fgets(buffer, MAX_LINE, passwordData);
                        if(feof(passwordData)){
                            printf("Not found!\n");
                            keep_reading = false;
                        } else if(current_line == readLine){
                            if(strcmp(buffer, password) == 0){
                                printf("Password Matches login name, you are now logged in\n");
                                loggedIn();
                                keep_reading = false;
                            } else {
                                printf("Username/Password Combo incorrect");
                            }
                        }
                        current_line++;
                    } while(keep_reading);
                    fclose(passwordData);
                    keep_reading = false;
                } else {
                    readLine++;
                }
            } while(keep_reading);
            fclose(usernameData);
            break;
        case 2:
            printf("Please register!");
            break;
        default:
            printf("Invalid response, please try again.");
    }
};

void staffLogin() {
    printf("Please enter username: ");
    char username[20];
    scanf("%s", username);
    char password[20];
    printf("Please enter password: ");
    scanf("%s", password);
};

void loggedIn(){
    printf("You are now logged in\n");
};

