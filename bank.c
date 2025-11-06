#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
    char password[20];
};

const char *DATAFILE = "bank.dat";
float g_amount; // global variable to pass deposit/withdraw amount

// Function declarations
void createAccount();
void displayAll();
void searchAccount();
void depositMoney();
void withdrawMoney();
void modifyAccount();
void deleteAccount();
int accountExists(int accNo);
int updateAccount(int accNo, void (*modify)(struct Account *));
void depositHelper(struct Account *a);
void withdrawHelper(struct Account *a);
void modifyHelper(struct Account *a);
void deleteHelper(struct Account *a);

// Helper function to print a line
void printLine(char ch, int len) {
    for (int i = 0; i < len; i++) putchar(ch);
    putchar('\n');
}

// Main function
int main() {
    int choice;
    while (1) {
        printLine('=', 50);
        printf("              BANK MANAGEMENT SYSTEM\n");
        printLine('=', 50);
        printf("1. Create New Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Search Account by Number\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Modify Account\n");
        printf("7. Delete Account\n");
        printf("8. Exit\n");
        printLine('-', 50);
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear invalid input
            continue;
        }

        switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAll(); break;
            case 3: searchAccount(); break;
            case 4: depositMoney(); break;
            case 5: withdrawMoney(); break;
            case 6: modifyAccount(); break;
            case 7: deleteAccount(); break;
            case 8: printf("Thank you for using the system!\n"); exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// ----------------------------
// Check if account exists
// ----------------------------
int accountExists(int accNo) {
    struct Account a;
    FILE *fp = fopen(DATAFILE, "rb");
    if (!fp) return 0;
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == accNo) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// ----------------------------
// Update account using helper
// ----------------------------
int updateAccount(int accNo, void (*modify)(struct Account *)) {
    struct Account a;
    int found = 0;

    FILE *fp = fopen(DATAFILE, "rb");
    FILE *fpTemp = fopen("temp.dat", "wb");
    if (!fp || !fpTemp) {
        if (fp) fclose(fp);
        if (fpTemp) fclose(fpTemp);
        return 0;
    }

    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == accNo) {
            modify(&a);
            found = 1;
        }
        if (a.accNo != -1) fwrite(&a, sizeof(a), 1, fpTemp);
    }

    fclose(fp);
    fclose(fpTemp);
    remove(DATAFILE);
    rename("temp.dat", DATAFILE);
    return found;
}

// ----------------------------
// CREATE ACCOUNT
// ----------------------------
void createAccount() {
    struct Account a;
    printf("\nEnter Account Number: ");
    scanf("%d", &a.accNo);

    if (accountExists(a.accNo)) {
        printf("Account already exists!\n");
        return;
    }

    while (getchar() != '\n');
    printf("Enter Name: ");
    fgets(a.name, sizeof(a.name), stdin);
    a.name[strcspn(a.name, "\n")] = '\0';

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    while (getchar() != '\n');
    printf("Set Password: ");
    fgets(a.password, sizeof(a.password), stdin);
    a.password[strcspn(a.password, "\n")] = '\0';

    FILE *fp = fopen(DATAFILE, "ab");
    if (!fp) { printf("Error writing file\n"); return; }
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("Account created successfully!\n");
}

// ----------------------------
// DISPLAY ALL ACCOUNTS
// ----------------------------
void displayAll() {
    struct Account a;
    FILE *fp = fopen(DATAFILE, "rb");
    if (!fp) { printf("No records found!\n"); return; }

    printLine('=', 70);
    printf("| %-10s | %-30s | %-15s |\n", "Acc Number", "Name", "Balance");
    printLine('=', 70);

    while (fread(&a, sizeof(a), 1, fp) == 1) {
        printf("| %-10d | %-30s | %-15.2f |\n", a.accNo, a.name, a.balance);
    }
    printLine('=', 70);
    fclose(fp);
}

// ----------------------------
// SEARCH ACCOUNT
// ----------------------------
void searchAccount() {
    int num; 
    struct Account a; 
    int found = 0;

    printf("Enter account number: "); 
    scanf("%d", &num);

    FILE *fp = fopen(DATAFILE, "rb");
    if (!fp) { printf("No records found!\n"); return; }

    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == num) {
            printLine('-', 50);
            printf("Account Number : %d\n", a.accNo);
            printf("Name           : %s\n", a.name);
            printf("Balance        : %.2f\n", a.balance);
            printLine('-', 50);
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
    fclose(fp);
}

// ----------------------------
// DEPOSIT MONEY
// ----------------------------
void depositMoney() {
    int num;
    printf("Enter account number: "); 
    scanf("%d", &num);

    printf("Enter amount to deposit: "); 
    scanf("%f", &g_amount);

    if (!updateAccount(num, depositHelper)) printf("Account not found!\n");
}

// Deposit helper function
void depositHelper(struct Account *a) {
    char pass[20];

    while (getchar() != '\n');
    printf("Enter password: "); 
    fgets(pass, sizeof(pass), stdin); 
    pass[strcspn(pass, "\n")] = '\0';

    if (strcmp(pass, a->password) != 0) { 
        printf("Wrong password!\n");
        return;
    }

    a->balance += g_amount;
    printf("Deposit successful! New balance: %.2f\n", a->balance);
}

// ----------------------------
// WITHDRAW MONEY
// ----------------------------
void withdrawMoney() {
    int num;
    printf("Enter account number: "); 
    scanf("%d", &num);

    printf("Enter amount to withdraw: "); 
    scanf("%f", &g_amount);

    if (!updateAccount(num, withdrawHelper)) printf("Account not found!\n");
}

// Withdraw helper function
void withdrawHelper(struct Account *a) {
    char pass[20];

    while (getchar() != '\n');
    printf("Enter password: "); 
    fgets(pass, sizeof(pass), stdin); 
    pass[strcspn(pass, "\n")] = '\0';

    if (strcmp(pass, a->password) != 0) { 
        printf("Wrong password!\n");
        return;
    }

    if (g_amount > a->balance) {
        printf("Insufficient balance!\n");
        return;
    }

    a->balance -= g_amount;
    printf("Withdrawal successful! New balance: %.2f\n", a->balance);
}

// ----------------------------
// MODIFY ACCOUNT
// ----------------------------
void modifyAccount() {
    int num;
    printf("Enter account number: "); 
    scanf("%d", &num);

    if (!updateAccount(num, modifyHelper)) printf("Account not found!\n");
}

// Modify helper function
void modifyHelper(struct Account *a) {
    char pass[20];

    while (getchar() != '\n');
    printf("Enter password: "); 
    fgets(pass, sizeof(pass), stdin); 
    pass[strcspn(pass, "\n")] = '\0';

    if (strcmp(pass, a->password) != 0) { 
        printf("Wrong password!\n");
        return;
    }

    printf("Enter new name: "); 
    fgets(a->name, sizeof(a->name), stdin); 
    a->name[strcspn(a->name, "\n")] = '\0';

    printf("Enter new balance: "); 
    scanf("%f", &a->balance);

    while (getchar() != '\n'); 
    printf("Enter new password: "); 
    fgets(a->password, sizeof(a->password), stdin); 
    a->password[strcspn(a->password, "\n")] = '\0';

    printf("Account modified successfully!\n");
}

// ----------------------------
// DELETE ACCOUNT
// ----------------------------
void deleteAccount() {
    int num;
    printf("Enter account number: "); 
    scanf("%d", &num);

    if (!updateAccount(num, deleteHelper)) printf("Account not found!\n");
}

// Delete helper function
void deleteHelper(struct Account *a) {
    char pass[20];

    while (getchar() != '\n');
    printf("Enter password: "); 
    fgets(pass, sizeof(pass), stdin); 
    pass[strcspn(pass, "\n")] = '\0';

    if (strcmp(pass, a->password) != 0) { 
        printf("Wrong password!\n");
        return;
    }

    a->accNo = -1;
    printf("Account deleted successfully!\n");
}
