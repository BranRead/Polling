#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

//region structs
struct Voter {
    char username[20];
    char password[16];
    char fName[20];
    char lName[20];
    char address[30];
    char phoneNum[10];
    bool voted;
    bool valid;
};

struct Staff {
    char username[20];
    char password[16];
    char fName[20];
    char lName[20];
    char address[30];
    char phoneNum[10];
};

struct Candidate {
    char fName[20];
    char lName[20];
    char address[30];
    char phoneNum[10];
    int votes;
};
//endregion

struct Voter accountSettingsVoter(struct Voter voter);
struct Staff accountSettingsAdmin(struct Staff admin);
struct Staff accountSettingsOffic(struct Staff officer);


void userLogin(struct Voter, struct Candidate, struct Candidate, struct Candidate);

void staffLogin(int useCase, char usernameFile[50], char passwordFile[50], FILE *username, FILE *password,
                struct Staff, struct Staff, struct Voter, struct Candidate, struct Candidate, struct Candidate);

void loggedInVoter(char username[], struct Voter, struct Candidate, struct Candidate, struct Candidate);

void loggedInAdmin(char username[], struct Staff, struct Voter);

void loggedInOfficer(char username[], struct Staff, struct Staff, struct Voter, struct Candidate,
                     struct Candidate, struct Candidate);

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

FILE *issues_Officer;
FILE *issues_Admin;

FILE *voterToOfficer;
FILE *adminToOfficer;

FILE *officerToAdmin;
FILE *officerToVoter;

//region main
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
    struct Voter voterAccount;
    voterAccount.voted = false;
    voterAccount.valid = true;
    strcpy(voterAccount.username, "JohnUser");
    strcpy(voterAccount.password, "Passw0rd");
    strcpy(voterAccount.fName, "John\n");
    strcpy(voterAccount.lName, "User\n");
    strcpy(voterAccount.address, "123 Fake Street\n");
    strcpy(voterAccount.phoneNum, "1845\n");

    //Staff
    usernameData_Admin = fopen("usernameAdmin_column.txt", "w");
    fprintf(usernameData_Admin, "JohnAdmin\n");
    fclose(usernameData_Admin);

    passwordData_Admin = fopen("passwordAdmin_column.txt", "w");
    fprintf(passwordData_Admin, "P@ssw0rd\n");
    fclose(passwordData_Admin);

    issues_Admin = fopen("issues_admin.txt", "w");
    fprintf(issues_Admin, "Hello there I am unable to vote because it says I am not a valid user\n"
                          "User: JohnUser\n");
    fclose(issues_Admin);

    //Staff struct
    struct Staff adminAccount;
    strcpy(adminAccount.username, "JohnAdmin");
    strcpy(adminAccount.password, "P@ssw0rd");
    strcpy(adminAccount.fName, "John");
    strcpy(adminAccount.lName, "Staff");
    strcpy(adminAccount.address, "650 Fake Street");
    strcpy(adminAccount.phoneNum, "1765");

    //Polling Officer
    usernameData_Officer = fopen("usernameOfficer_column.txt", "w");
    fprintf(usernameData_Officer, "JohnOff\n");
    fclose(usernameData_Officer);

    passwordData_Officer = fopen("passwordOfficer_column.txt", "w");
    fprintf(passwordData_Officer, "secret\n");
    fclose(passwordData_Officer);

    issues_Officer = fopen("issues_off.txt", "w");
    fprintf(issues_Admin, "Hello there I would like to register for the election\n"
                          "First Name: Monopoly\n Last Name: Man\n Address: 23 Forest Highway\n Phone # 7867");
    fclose(issues_Officer);

    voterToOfficer = fopen("voter_queries.txt", "w");
    fprintf(voterToOfficer, "Hello, my votes won't go through.\n");
    fclose(voterToOfficer);

    adminToOfficer = fopen("admin_queries.txt", "w");
    fprintf(adminToOfficer, "Hey, a user has an issue registering, can I get your help?\n");
    fclose(adminToOfficer);

    //Officer struct
    struct Staff officerAccount;
    strcpy(officerAccount.username, "JohnOff");
    strcpy(officerAccount.password, "secret");
    strcpy(officerAccount.fName, "John");
    strcpy(officerAccount.lName, "Officer");
    strcpy(officerAccount.address, "101 Fake Street");
    strcpy(officerAccount.phoneNum, "1234");

    //Candidate struct
    struct Candidate candidate1;
    struct Candidate candidate2;
    struct Candidate candidate3;

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
        //User, Staff, Polling officer, quit or invalid response.
            switch (useCase) {
                case 1:
                    //User
                    userLogin(voterAccount, candidate1, candidate2, candidate3);
                    break;
                case 2:
                    //Admin
                    staffLogin(useCase, "usernameAdmin_column.txt", "passwordAdmin_column.txt",
                               usernameData_Admin, passwordData_Admin, adminAccount,
                               officerAccount, voterAccount, candidate1, candidate2, candidate3);
                    break;
                case 3:
                    //Polling Officer
                    staffLogin(useCase, "usernameOfficer_column.txt", "passwordOfficer_column.txt",
                               usernameData_Officer, passwordData_Officer, adminAccount,
                               officerAccount, voterAccount, candidate1, candidate2, candidate3);
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
//endregion

//region userLogin
void userLogin(struct Voter voter, struct Candidate candidate1, struct Candidate candidate2,
               struct Candidate candidate3) {
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
                                loggedInVoter(username, voter, candidate1, candidate2, candidate3);
                                keep_reading = false;
                            } else {
                                printf("Username/Password Combo incorrect\n");
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
            printf("Please register!\n");
            break;
        default:
            printf("Invalid response, please try again.\n");
    }
};
//endregion

//region staffLogin
void staffLogin(int useCase, char usernameFile[50], char passwordFile[50], FILE *usernameVar, FILE *passwordVar,
                struct Staff admin, struct Staff officer, struct Voter voter, struct Candidate candidate1,
                        struct Candidate candidate2, struct Candidate candidate3) {
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
                            loggedInAdmin(username, admin, voter);
                        } else if (useCase == 3){
                            loggedInOfficer(username, admin, officer, voter, candidate1, candidate2, candidate3);
                        } else {
                            printf("Please report this error to the person responsible for this software."
                                   " Code:197\n");
                        }
                        keep_reading = false;
                    } else {
                        printf("Username/Password Combo incorrect\n");
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
//endregion

//region Account details Voter
struct Voter accountSettingsVoter(struct Voter voter){
    bool edit = true;
    printf("Editing account\n");
    int response;
    do {
        printf("What would you like to change?\n");
        printf("Key: Username = 1 | Password = 2 | First Name = 3 | Last Name = 4 | Address = 5 |"
               " Phone Number = 6 | Exit = 0\n");

        char blank[10];
        scanf("%i", &response);
        fgets(blank, 10, stdin);
        fflush(stdin);

        switch (response) {
            case 1:
                printf("Username is: %s\n", voter.username);
                printf("Type in what you would like to change it to: \n");
                char usernameChng[50];
                fgets(usernameChng, 50, stdin);
                strcpy(voter.username, usernameChng);
                break;

            case 2:
                printf("Please type in your old password: \n");
                char oldPass[16];
                fgets(oldPass, 16, stdin);
                if(oldPass == voter.password) {
                    printf("Type in what you would like to change it to: \n");
                    char passwordChng[50];
                    fgets(passwordChng, 50, stdin);
                    strcpy(voter.password, passwordChng);
                } else {
                    printf("You have entered an incorrect password, please try again.\n");
                }
                break;
            case 3:
                printf("First Name: %s", voter.fName);
                printf("Type in what you would like to change it to: \n");
                char fNameChng[50];
                fgets(fNameChng, 50, stdin);
                strcpy(voter.fName, fNameChng);
                break;
            case 4:
                printf("Last Name: %s", voter.lName);
                printf("Type in what you would like to change it to: \n");
                char lNameChng[50];
                fgets(lNameChng, 50, stdin);
                strcpy(voter.lName, lNameChng);
                break;
            case 5:
                printf("Address on file: %s", voter.address);
                printf("Type in what you would like to change it to: \n");
                char addressChng[50];
                fgets(addressChng, 50, stdin);
                strcpy(voter.address, addressChng);
                break;
            case 6:
                printf("Phone Number: %s", voter.phoneNum);
                printf("Type in what you would like to change it to: \n");
                char phoneNumChng[4];
                fgets(phoneNumChng, 4, stdin);
                strcpy(voter.phoneNum, phoneNumChng);
                break;
            case 0:
                printf("Exiting\n");
                edit = false;
                break;
            default:
                printf("ERROR\n");
        }
    } while (edit);
    return voter;
};
//endregion

//region loggedInVoter
void loggedInVoter(char username[], struct Voter voter, struct Candidate candidate1, struct Candidate candidate2,
                   struct Candidate candidate3){
    bool run = true;
    printf("Hello: %s\n", username);
    printf("What would you like to do today?\n");
    bool edit;
    do {
        printf("Key: Edit Account Details = 1 | Vote = 2 | Contact Support = 3 | Exit = 0\n");
        int response;
        scanf("%i", &response);

        switch (response) {
            case 1:
                voter = accountSettingsVoter(voter);
                break;
            case 2:
                printf("Voting\n");
                printf("Who would you like to vote for: \n");
                printf("%s %s = 1 | %s %s = 2 | %s %s = 3 | exit = 0\n", candidate1.fName, candidate1.lName,
                       candidate2.fName, candidate2.lName, candidate3.fName, candidate3.lName);
                int castVote;

                char blank[10];
                scanf("%d", &castVote);
                fgets(blank, 10, stdin);
                fflush(stdin);

                if(voter.valid && !voter.voted){
                    switch (castVote) {
                        case 1:
                            printf("You have voted for: %s %s\n", candidate1.fName, candidate1.lName);
                            candidate1.votes++;
                            voter.voted = true;
                            break;
                        case 2:
                            printf("You have voted for: %s %s\n", candidate2.fName, candidate2.lName);
                            candidate2.votes++;
                            voter.voted = true;
                            break;
                        case 3:
                            printf("You have voted for: %s %s\n", candidate3.fName, candidate3.lName);
                            candidate3.votes++;
                            voter.voted = true;
                            break;
                        default:
                            printf("There was an issue casting your vote, please try again later.\n");
                    }
                } else if (voter.voted){
                    printf("You have already voted, you are unable to vote twice during this election period.\n");
                } else {
                    printf("Please contact the administrator to approve your account\n");
                }
                break;
            case 3:
                printf("Contacting Polling Officer\n");
                voterToOfficer = fopen("voter_queries.txt", "w");
                fgets(blank, 10, stdin);
                char text[100];
                printf("Please type out your query here: \n");
                fgets(text, 100, stdin);
                fprintf(voterToOfficer, "%s", text);
                fclose(voterToOfficer);
                printf("Message sent to Polling Officer\n");
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
//endregion

//region Account details admin
struct Staff accountSettingsAdmin(struct Staff admin){
    bool edit = true;
    int response;
    printf("Editing account\n");
    do {
        printf("What would you like to change?\n");
        printf("Key: Username = 1 | Password = 2 | First Name = 3 | Last Name = 4 | Address = 5 |"
               " Phone Number = 6 | Exit = 0\n");
        char blank[10];
        scanf("%i", &response);
        fgets(blank, 10, stdin);
        fflush(stdin);

        switch (response) {
            case 1:
                printf("Username is: %s\n", admin.username);
                printf("Type in what you would like to change it to: \n");
                char usernameChng[50];
                fgets(usernameChng, 50, stdin);
                strcpy(admin.username, usernameChng);
                break;

            case 2:
                fgets(blank, 10, stdin);
                fflush(stdin);
                printf("Please type in your old password: \n");
                char oldPass[16];
                fgets(oldPass, 16, stdin);
                oldPass[strcspn(oldPass, "\n")] = '\0';
                if(strcmp(oldPass, admin.password) == 0) {
                    printf("Type in what you would like to change it to: \n");
                    char passwordChng[50];
                    fgets(passwordChng, 50, stdin);
                    strcpy(admin.password, passwordChng);
                } else {
                    printf("You have entered an incorrect password, please try again.\n");
                }
                break;
            case 3:
                printf("First Name: %s", admin.fName);
                printf("Type in what you would like to change it to: \n");
                char fNameChng[50];
                fgets(fNameChng, 50, stdin);
                strcpy(admin.fName, fNameChng);
                break;
            case 4:
                printf("Last Name: %s", admin.lName);
                printf("Type in what you would like to change it to: \n");
                char lNameChng[50];
                fgets(lNameChng, 50, stdin);
                strcpy(admin.lName, lNameChng);
                break;
            case 5:
                printf("Address on file: %s", admin.address);
                printf("Type in what you would like to change it to: \n");
                char addressChng[50];
                fgets(addressChng, 50, stdin);
                strcpy(admin.address, addressChng);
                break;
            case 6:
                printf("Phone Number: %s", admin.phoneNum);
                printf("Type in what you would like to change it to: \n");
                char phoneNumChng[4];
                fgets(phoneNumChng, 4, stdin);
                strcpy(admin.phoneNum, phoneNumChng);
                break;
            case 0:
                printf("Exiting\n");
                edit = false;
                break;
            default:
                printf("ERROR");
        }
    } while (edit);
    return admin;
};
//endregion

//region loggedInAdmin
void loggedInAdmin(char username[], struct Staff staff, struct Voter voter){
    bool run = true;
    printf("Hello: %s\n", username);
    printf("What would you like to do today?\n");
    bool edit;
    do {
        printf("Key: Edit Account Details = 1 | Accept Work = 2 | Contact Polling Officer = 3 | Exit = 0\n");
        int response;
        scanf("%i", &response);
        char blank[10];

        switch (response) {
            case 1:
                staff = accountSettingsAdmin(staff);
                break;
            case 2:
                printf("Fixing account issues\n");
                fgets(blank, 10, stdin);
                char text[100];
                printf("What would you like to do?\n");
                printf("Old = 1 | New = 2 | Work on Issues = 3 | Exit = 0\n");
                scanf("%d", &response);
                switch (response) {
                    case 1:
                        printf("Old messages\n");
                        issues_Admin = fopen("issues_admin.txt", "r");
                        while (fgets(text, 100, issues_Admin)) {
                            printf("%s", text);
                        };
                        fclose(issues_Admin);
                        break;
                    case 2:
                        printf("New Messages\n");
                        officerToAdmin = fopen("offToAdmin.txt", "r");
                        while (fgets(text, 100, officerToAdmin)) {
                            printf("%s", text);
                        };
                        fclose(officerToAdmin);
                        break;
                    case 3:
                        fgets(blank, 10, stdin);
                        printf("Editing Voter account\n");
                        accountSettingsVoter(voter);
                        break;
                    default:
                        scanf("ERROR");
                        break;
                }
            case 3:
                printf("Contacting Polling Officer\n");
                adminToOfficer = fopen("admin_queries.txt", "w");
                fgets(blank, 10, stdin);
                printf("Please type out your message here: \n");
                fgets(text, 100, stdin);
                fprintf(adminToOfficer, "%s", text);
                fclose(adminToOfficer);
                printf("Message sent to Polling Officer\n");
                break;
            case 0:
                printf("Remember to fully close out your session and to punch out.\nHave a great day!\n");
                run = false;
                break;
            default:
                printf("Please enter a valid response\n");
        }
    } while (run);
};
//endregion

//region Account details officer
struct Staff accountSettingsOffic(struct Staff officer){
    bool edit = true;
    int response;
    char blank[10];
    printf("Editing account\n");
    do {
        printf("What would you like to change?\n");
        printf("Key: Username = 1 | Password = 2 | First Name = 3 | Last Name = 4 | Address = 5 |"
               " Phone Number = 6 | Exit = 0\n");


        scanf("%i", &response);
        fgets(blank, 10, stdin);
        fflush(stdin);

        switch (response) {
            case 1:
                printf("Username is: %s\n", officer.username);
                printf("Type in what you would like to change it to: \n");
                char usernameChng[50];
                fgets(usernameChng, 50, stdin);
                strcpy(officer.username, usernameChng);
                break;
            case 2:
                printf("Please type in your old password: \n");
                char oldPass[16];
                fgets(oldPass, 16, stdin);
                if(oldPass == officer.password) {
                    printf("Type in what you would like to change it to: \n");
                    char passwordChng[50];
                    fgets(passwordChng, 50, stdin);
                    strcpy(officer.password, passwordChng);
                } else {
                    printf("You have entered an incorrect password, please try again.\n");
                }
                break;
            case 3:
                printf("First Name: %s\n", officer.fName);
                printf("Type in what you would like to change it to: \n");
                char fNameChng[50];
                fgets(fNameChng, 50, stdin);
                strcpy(officer.fName, fNameChng);
                break;
            case 4:
                printf("Last Name: %s\n", officer.lName);
                printf("Type in what you would like to change it to: \n");
                char lNameChng[50];
                fgets(lNameChng, 50, stdin);
                strcpy(officer.lName, lNameChng);
                break;
            case 5:
                printf("Address on file: %s\n", officer.address);
                printf("Type in what you would like to change it to: \n");
                char addressChng[50];
                fgets(addressChng, 50, stdin);
                strcpy(officer.address, addressChng);
                break;
            case 6:
                printf("Phone Number: %s", officer.phoneNum);
                printf("Type in what you would like to change it to: \n");
                char phoneNumChng[4];
                fgets(phoneNumChng, 4, stdin);
                strcpy(officer.phoneNum, phoneNumChng);
                break;
            case 0:
                printf("Exiting\n");
                edit = false;
                break;
            default:
                printf("ERROR\n");
        }
    } while (edit);
    return officer;
}
//endregion

//region loggedInOfficer
void loggedInOfficer(char username[], struct Staff admin, struct Staff officer, struct Voter voter,
        struct Candidate candidate1, struct Candidate candidate2, struct Candidate candidate3){
    bool run = true;
    printf("Hello: %s\n", username);
    printf("What would you like to do today?\n");
    bool edit;
    char blank[10];

    do {
        printf("Key: Edit Account Details = 1 | Accept Work = 2 | Count Votes = 3 | Exit = 0\n");
        int response;
        scanf("%i", &response);

        switch (response) {
            case 1:
                officer = accountSettingsOffic(officer);
                break;
            case 2:
                fgets(blank, 10, stdin);
                char text[100];
                printf("What would you like to do?\n");
                printf("Old = 1 | New = 2 | Work on Issues = 3 | Exit = 0\n");
                scanf("%d", &response);
                switch (response) {
                    case 1:
                        issues_Officer = fopen("issues_off.txt", "r");
                        while(fgets(text, 100, issues_Officer)) {
                            printf("%s", text);
                        };
                        fclose(issues_Officer);
                        break;
                    case 2:
                        printf("Voter issues\n");
                        voterToOfficer = fopen("voter_queries.txt", "r");
                        while(fgets(text, 100, voterToOfficer)) {
                            printf("%s", text);
                        };
                        fclose(voterToOfficer);

                        printf("Messages from admins\n");
                        adminToOfficer = fopen("admin_queries.txt", "r");
                        while(fgets(text, 100, adminToOfficer)) {
                            printf("%s", text);
                        };
                        fclose(adminToOfficer);
                        break;
                    case 3:
                        fgets(blank, 10, stdin);
                        printf("What would you like to do?\n");
                        printf("Send Messages = 1 | Edit Staff Account = 2 | Edit Voter Account = 3 "
                               "| Exit = 0\n");
                        scanf("%d", &response);
                        switch (response) {
                            case 1:
                                fgets(blank, 10, stdin);
                                printf("Send message to whom?\n");
                                printf("Voter = 1 | Admin = 2 | Exit = 0\n");
                                scanf("%d", &response);
                                switch (response) {
                                    case 1:
                                        officerToVoter = fopen("offToVoter.txt", "w");
                                        fgets(blank, 10, stdin);
                                        printf("Please type out your message here: \n");
                                        fgets(text, 100, stdin);
                                        fprintf(officerToVoter, "%s", text);
                                        fclose(officerToVoter);
                                        break;
                                    case 2:
                                        officerToAdmin = fopen("offToAdmin.txt", "w");
                                        fgets(blank, 10, stdin);
                                        printf("Please type out your message here: \n");
                                        fgets(text, 100, stdin);
                                        fprintf(officerToAdmin, "%s", text);
                                        fclose(officerToAdmin);
                                        break;
                                    case 0:
                                        printf("Exiting outgoing messages.\n");
                                        break;
                                    default:
                                        printf("ERROR\n");
                                }
                                break;
                            case 2:
                                accountSettingsAdmin(admin);
                                break;
                            case 3:
                                accountSettingsVoter(voter);
                                break;
                            default:
                                printf("ERROR\n");
                        }
                }
                break;
            case 3:
                printf("Counting votes\n");
                printf("%s %s has: %d votes.\n", candidate1.fName, candidate1.lName, candidate1.votes);
                printf("%s %s has: %d votes.\n", candidate2.fName, candidate2.lName, candidate2.votes);
                printf("%s %s has: %d votes.\n", candidate3.fName, candidate3.lName, candidate3.votes);
                break;
            case 0:
                printf("Remember to fully close out your session and to punch out.\nHave a great day!\n");
                run = false;
                break;
            default:
                printf("Please enter a valid response\n");
        }
    } while (run);
};
//endregion

