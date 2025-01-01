// Adnan Kazi's Password Manager

#include <stdio.h>
#include <string.h>

#define NEWCRED 1
#define DISPCRED 2 
#define DELCRED 3 
#define EXITPROG 4

// Function declaration
void encryptDecrypt(char *, char *, char *);
void Newcredential(char *);
void Displaycredential(char *);
void Deletecredential();

int main()
{
    char KEY[100];
    printf("Enter your master password: ");
    scanf("%s", KEY);

    int option;

    do {
        printf("Login Credential Manager\n");
        printf("Please select one of the options (1-4):\n");
        printf("1. Add a new credential\n");
        printf("2. Display current credentials\n");
        printf("3. Delete a credential\n");
        printf("4. Exit\n");
        scanf("%d", &option);

        while (option > 4 || option < 1)
        {
            printf("You did not enter a valid entry. Try Again!\n");
            scanf("%d", &option);
        }

        switch (option)
        {
            case NEWCRED:
                Newcredential(KEY);
                break;
            case DISPCRED:
                Displaycredential(KEY);
                break;
            case DELCRED:
                Deletecredential();
                break;
            case EXITPROG:
                printf("Exiting Program\n");
                break;
        }
    } while (option != 4);

    return 0;
}

void encryptDecrypt(char *input, char *output, char *KEY)
{
    int i;
    for (i = 0; i < strlen(input); i++) {
        output[i] = input[i] ^ KEY[i%strlen(KEY)] ^ 128;
    }
    output[i] = '\0';
}

void Newcredential(char *KEY)
{
    char name[100];
    char email[100];
    char password[100];
    char encryptedPassword[100];

    FILE *LoginDetails = fopen("LoginDetails.txt", "a");

    printf("Please provide the name for Credential: ");
    scanf("%s", name);

    printf("Please provide the email: ");
    scanf("%s", email);

    printf("Please provide the password: ");
    scanf("%s", password);

    encryptDecrypt(password, encryptedPassword, KEY);

    fprintf(LoginDetails, "Name: %s\n", name);
    fprintf(LoginDetails, "Email: %s\n", email);
    fprintf(LoginDetails, "Password: %s\n", encryptedPassword);
    fprintf(LoginDetails, "\n");

    fclose(LoginDetails);

    printf("Credential added successfully.\n");
}

void Displaycredential(char *KEY)
{

    FILE *LoginDetails = fopen("LoginDetails.txt", "r");

    char line[150];

    if (LoginDetails == NULL) {
        printf("No credentials found.\n");
        return;
    }

    rewind(LoginDetails);

    while (fgets(line, sizeof(line), LoginDetails)) {
        if (strstr(line, "Password:")) {
            // Decrypt the password
            char encryptedPassword[100];
            char decryptedPassword[100];
            sscanf(line, "Password: %s\n", encryptedPassword);
            encryptDecrypt(encryptedPassword, decryptedPassword, KEY);
            printf("Password: %s\n", decryptedPassword);
        } else {
            printf("%s", line);
        }
    }

    fclose(LoginDetails);
}

void Deletecredential()
{
    char name[100];
    printf("Enter the name of the credential to delete: ");
    scanf("%s", name);

    FILE *LoginDetails = fopen("LoginDetails.txt", "r");
    FILE *TempFile = fopen("TempLoginDetails.txt", "w");

    if (LoginDetails == NULL) {
        printf("No credentials found.\n");
        return;
    }

    int found = 0;
    char line[150];

    while (fgets(line, sizeof(line), LoginDetails)) {
        if (strstr(line, "Name:") && strstr(line, name)) {
            found = 1;
            fgets(line, sizeof(line), LoginDetails);
            fgets(line, sizeof(line), LoginDetails);
            fgets(line, sizeof(line), LoginDetails);
        } else {
            fputs(line, TempFile);
        }
    }

    fclose(LoginDetails);
    fclose(TempFile);

    remove("LoginDetails.txt");
    rename("TempLoginDetails.txt", "LoginDetails.txt");

    if (found) {
        printf("Credential deleted successfully.\n");
    } else {
        printf("Credential with name '%s' not found.\n", name);
    }
}