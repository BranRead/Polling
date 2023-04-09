#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

//user and admins

void userLogin(struct voterStruct *voter);
void staffLogin(int useCase, char usernameFile[50], char passwordFile[50], FILE *username, FILE *password);

void loggedInVoter(char username[], struct voterStruct *voter);
void loggedInAdmin(char username[]);
void loggedInOfficer(char username[]);

struct voterStruct {
    char username[20];
    char password[16];
    char fName[20];
    char lName[20];
    char address[30];
    char phoneNum[10];
    bool voted;
    bool valid;
};

struct staffStruct {
    char username[20];
    char password[16];
    char fName[20];
    char lName[20];
    char address[30];
    char phoneNum[10];
};

struct canStruct {
    char fName[20];
    char lName[20];
    char address[30];
    char phoneNum[10];
    int votes;
};

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

    //Voter File for username and password
    usernameData_Voter = fopen("usernameVoter_column.txt", "w");
    fprintf(usernameData_Voter, "JohnUser\n");
    fclose(usernameData_Voter);

    passwordData_Voter = fopen("passwordVoter_column.txt", "w");
    fprintf(passwordData_Voter, "Passw0rd\n");
    fclose(passwordData_Voter);

    //Voter struct
    struct voterStruct voterAccount;
    voterAccount.voted = false;
    voterAccount.valid = false;
    strcpy(voterAccount.username, "JohnUser");
    strcpy(voterAccount.password, "Passw0rd");
    strcpy(voterAccount.fName, "John");
    strcpy(voterAccount.lName, "User");
    strcpy(voterAccount.address, "123 Fake Street");
    strcpy(voterAccount.phoneNum, "1845");

    //Admin
    usernameData_Admin = fopen("usernameAdmin_column.txt", "w");
    fprintf(usernameData_Admin, "JohnAdmin\n");
    fclose(usernameData_Admin);

    passwordData_Admin = fopen("passwordAdmin_column.txt", "w");
    fprintf(passwordData_Admin, "P@ssw0rd\n");
    fclose(passwordData_Admin);

    //Admin struct
    struct staffStruct adminAccount;
    strcpy(voterAccount.username, "JohnAdmin");
    strcpy(voterAccount.password, "P@ssw0rd");
    strcpy(voterAccount.fName, "John");
    strcpy(voterAccount.lName, "Admin");
    strcpy(voterAccount.address, "650 Fake Street");
    strcpy(voterAccount.phoneNum, "1765");

    //Polling Officer
    usernameData_Officer = fopen("usernameOfficer_column.txt", "w");
    fprintf(usernameData_Officer, "JohnOff\n");
    fclose(usernameData_Officer);

    passwordData_Officer = fopen("passwordOfficer_column.txt", "w");
    fprintf(passwordData_Officer, "secret\n");
    fclose(passwordData_Officer);

    //Officer struct
    struct staffStruct officerAccount;
    strcpy(voterAccount.username, "JohnOff");
    strcpy(voterAccount.password, "secret");
    strcpy(voterAccount.fName, "John");
    strcpy(voterAccount.lName, "Officer");
    strcpy(voterAccount.address, "101 Fake Street");
    strcpy(voterAccount.phoneNum, "1234");

    //Candidate struct
    struct canStruct candidate1;
    struct canStruct candidate2;
    struct canStruct candidate3;

    strcpy(candidate1.fName, "Can");
    strcpy(candidate1.lName, "One");
    strcpy(candidate1.address, "1 Fake Street");
    strcpy(candidate1.phoneNum, "9082");
    candidate1.votes = 5;

    strcpy(candidate2.fName, "Can");
    strcpy(candidate2.lName, "Two");
    strcpy(candidate2.address, "2 Fake Street");
    strcpy(candidate2.phoneNum, "0032");
    candidate2.votes = 25;

    strcpy(candidate3.fName, "Can");
    strcpy(candidate3.lName, "Three");
    strcpy(candidate3.address, "3 Fake Street");
    strcpy(candidate3.phoneNum, "8034");
    candidate3.votes = 12;

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
                    userLogin(&voterAccount);
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

void userLogin(struct voterStruct *voter) {
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
                    readLine++;
                    passwordData_Voter = fopen("password_column.txt", "r");
                    do {
                        fgets(buffer, MAX_LINE, passwordData_Voter);
                        if(feof(passwordData_Voter)){
                            printf("Not found!\n");
                            keep_reading = false;
                        } else if(current_line == readLine){
                            if(strcmp(buffer, password) == 0){
                                loggedInVoter(username, voter);
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
            readLine++;
            passwordVar = fopen((const char *) passwordFile, "r");
            do {
                fgets(buffer, MAX_LINE, passwordVar);
                if(feof(passwordVar)){
                    printf("Not found!\n");
                    keep_reading = false;
                } else if(current_line == readLine){
                    if(strcmp(buffer, password) == 0){
                        if(useCase == 2){
                            loggedInAdmin(username);
                        } else if (useCase == 3){
                            loggedInOfficer(username);
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

void loggedInVoter(char username[], struct voterStruct *voter){
    bool run = true;
    printf("Hello: %s\n", username);
    printf("What would you like to do today?\n");
    do {
        printf("Key: Edit Account Details = 1 | Vote = 2 | Contact Support = 3 | Exit = 0\n");
        int response;
        scanf("%i", &response);

        switch (response) {
            case 1:
                bool run = true;
                printf("Editing account\n");
                do {
                    printf("What would you like to change?");
                    printf("Key: username = 1 | password = 2 | first name = 3 | last name = 4 | address = 5 |"
                           " phone number = 6 | Exit = 0\n");
                    scanf("%i", &response);

                    switch (response) {
                        case 1:
                            printf("Username is: %s\n", voter->username);
                            printf("Type in what you would like to change it to: \n");
                            char usernameChng[50];
                            fgets(usernameChng, 50, stdin);
                            strcpy(voter->username, usernameChng);
                            break;

                        case 2:
                            printf("Please type in your old password: \n");
                            char oldPass[16];
                            fgets(oldPass, 16, stdin);
                            if(oldPass == voter->password) {
                                printf("Type in what you would like to change it to: \n");
                                char passwordChng[50];
                                fgets(passwordChng, 50, stdin);
                                strcpy(voter->password, passwordChng);
                            } else {
                                printf("You have entered an incorrect password, please try again.");
                            }
                            break;
                        case 3:
                            printf("First Name: %s", voter->fName);
                            printf("Type in what you would like to change it to: \n");
                            char fNameChng[50];
                            fgets(fNameChng, 50, stdin);
                            strcpy(voter->fName, fNameChng);
                            break;
                        case 4:
                            printf("Last Name: %s", voter->lName);
                            printf("Type in what you would like to change it to: \n");
                            char lNameChng[50];
                            fgets(lNameChng, 50, stdin);
                            strcpy(voter->lName, lNameChng);
                            break;
                        case 5:
                            printf("Address on file: %s", voter->address);
                            printf("Type in what you would like to change it to: \n");
                            char addressChng[50];
                            fgets(addressChng, 50, stdin);
                            strcpy(voter->address, addressChng);
                            break;
                        case 6:
                            printf("Phone Number: %s", voter->phoneNum);
                            printf("Type in what you would like to change it to: \n");
                            char phoneNumChng[4];
                            fgets(phoneNumChng, 4, stdin);
                            strcpy(voter->phoneNum, phoneNumChng);
                            break;
                        case 0:
                            printf("Exiting\n");
                            run = false;
                            break;
                        default:
                            printf("ERROR");
                    }
                } while (run);
                break;
            case 2:
                printf("Voting\n");
                break;
            case 3:
                printf("Contacting Support\n");
                break;
            case 0:
                printf("Thank you for using online polling.\nHave a great day!\n");
                run = false;
                break;
            default:
                printf("Please enter a valid response\n");
        }
    } while (run);
};

void loggedInAdmin(char username[]){
    bool run = true;
    printf("Hello: %s\n", username);
    printf("What would you like to do today?\n");
    do {
        printf("Key: Edit Account Details = 1 | Vote = 2 | Contact Support = 3 | Exit = 0\n");
        int response;
        scanf("%i", &response);

        switch (response) {
            case 1:
                printf("Editing account\n");
                break;
            case 2:
                printf("Fixing account issues\n");
                break;
            case 3:
                printf("Contacting Polling Officer\n");
                break;
            case 0:
                printf("Remember to fully close out your session and to punch out.\nHave a great day!");
                run = false;
                break;
            default:
                printf("Please enter a valid response\n");
        }
    } while (run);
};

void loggedInOfficer(char username[]){
    bool run = true;
    printf("Hello: %s\n", username);
    printf("What would you like to do today?\n");
    do {
        printf("Key: Edit Account Details = 1 | Vote = 2 | Contact Support = 3 | Exit = 0\n");
        int response;
        scanf("%i", &response);

        switch (response) {
            case 1:
                printf("Editing account\n");
                break;
            case 2:
                printf("Fixing issues related to polling\n");
                break;
            case 3:
                printf("Counting votes\n");
                break;
            case 0:
                printf("Thank you for using online polling.\nHave a great day!\n");
                run = false;
                break;
            default:
                printf("Please enter a valid response\n");
        }
    } while (run);
};

