#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

//user and admins

void userLogin();
void staffLogin(int useCase, char usernameFile[50], char passwordFile[50], FILE *username, FILE *password);

void loggedInVoter();
void loggedInAdmin();
void loggedInOfficer();

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

char filename[FILENAME_SIZE];
char buffer[MAX_LINE];

FILE *usernameData_Voter;
FILE *passwordData_Voter;

FILE *usernameData_Admin;
FILE *passwordData_Admin;

FILE *usernameData_Officer;
FILE *passwordData_Officer;



int main() {
    int useCase;

    //Voter
    usernameData_Voter = fopen("usernameVoter_column.txt", "w");
    fprintf(usernameData_Voter, "JohnUser\n");
    fclose(usernameData_Voter);

    passwordData_Voter = fopen("passwordVoter_column.txt", "w");
    fprintf(passwordData_Voter, "Passw0rd\n");
    fclose(passwordData_Voter);

    //Admin
    usernameData_Admin = fopen("usernameAdmin_column.txt", "w");
    fprintf(usernameData_Admin, "JohnAdmin\n");
    fclose(usernameData_Admin);

    passwordData_Admin = fopen("passwordAdmin_column.txt", "w");
    fprintf(passwordData_Admin, "Passw0rd\n");
    fclose(passwordData_Admin);

    //Polling Officer
    usernameData_Officer = fopen("usernameOfficer_column.txt", "w");
    fprintf(usernameData_Officer, "JohnOff\n");
    fclose(usernameData_Officer);

    passwordData_Officer = fopen("passwordOfficer_column.txt", "w");
    fprintf(passwordData_Officer, "Passw0rd\n");
    fclose(passwordData_Officer);

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
                    userLogin();
                    break;
                case 2:
                    //Admin
                    staffLogin(useCase, "usernameAdmin_column.txt", "passwordAdmin_column.txt",
                               usernameData_Admin, passwordData_Admin);
                    break;
                case 3:
                    //Polling Officer
                    staffLogin(useCase, "usernameOfficer_column.txt", "passwordOfficer_column.txt",
                               usernameData_Officer, passwordData_Officer);
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

            usernameData_Voter = fopen("username_column.txt", "r");
            bool keep_reading = true;
            int current_line = 1;
            int readLine = 0;
            do {
                fgets(buffer, MAX_LINE, usernameData_Voter);
                if(feof(usernameData_Voter)){
                    printf("Not found!\n");
                    keep_reading = false;
                } else if(strcmp(buffer, username) == 0){
                    printf("Correct username!\n");
                    readLine++;
                    passwordData_Voter = fopen("password_column.txt", "r");
                    do {
                        fgets(buffer, MAX_LINE, passwordData_Voter);
                        if(feof(passwordData_Voter)){
                            printf("Not found!\n");
                            keep_reading = false;
                        } else if(current_line == readLine){
                            if(strcmp(buffer, password) == 0){
                                printf("Password Matches login name, you are now logged in\n");
                                loggedInVoter();
                                keep_reading = false;
                            } else {
                                printf("Username/Password Combo incorrect");
                            }
                        }
                        current_line++;
                    } while(keep_reading);
                    fclose(passwordData_Voter);
                    keep_reading = false;
                } else {
                    readLine++;
                }
            } while(keep_reading);
            fclose(usernameData_Voter);
            break;
        case 2:
            printf("Please register!");
            break;
        default:
            printf("Invalid response, please try again.");
    }
};

void staffLogin(int useCase, char usernameFile[50], char passwordFile[50], FILE *usernameVar, FILE *passwordVar) {
    printf("Please enter username: ");
    char username[20];
    fgets(username, 21, stdin);
    char password[20];
    printf("Please enter password: ");
    fgets(password, 21, stdin);

    usernameVar = fopen((const char *) usernameFile, "r");
    bool keep_reading = true;
    int current_line = 1;
    int readLine = 0;
    do {
        fgets(buffer, MAX_LINE, usernameData_Voter);
        if(feof(usernameVar)){
            printf("Not found!\n");
            keep_reading = false;
        } else if(strcmp(buffer, username) == 0){
            printf("Correct username!\n");
            readLine++;
            passwordVar = fopen((const char *) passwordFile, "r");
            do {
                fgets(buffer, MAX_LINE, passwordVar);
                if(feof(passwordVar)){
                    printf("Not found!\n");
                    keep_reading = false;
                } else if(current_line == readLine){
                    if(strcmp(buffer, password) == 0){
                        printf("Password Matches login name, you are now logged in\n");
                        if(useCase == 2){
                            loggedInAdmin();
                        } else if (useCase == 3){
                            loggedInOfficer();
                        } else {
                            printf("Please report this error to the person responsible for this software."
                                   " Code:197");
                        }
                        keep_reading = false;
                    } else {
                        printf("Username/Password Combo incorrect");
                    }
                }
                current_line++;
            } while(keep_reading);
            fclose(passwordVar);
            keep_reading = false;
        } else {
            readLine++;
        }
    } while(keep_reading);
    fclose(usernameVar);
};

void loggedInVoter(){
    printf("You are now logged in as user\n");
};

void loggedInAdmin(){
    printf("You are now logged in as admin\n");
};

void loggedInOfficer(){
    printf("You are now logged in as polling officer\n");
};