#include <stdio.h>
#include <stdlib.h>

// Initial balances
float savings_balance = 1000.0;
float checking_balance = 1000.0;

// Function declarations
void displayMenu();
void transferToSavings();
void transferToChecking();
void displaySavingsBalance();
void displayCheckingBalance();
void withdrawCash();
int validatePIN();

int main() {
    int attempts = 0;
    int pinValid = 0;

    // PIN validation
    while (attempts < 3 && !pinValid) {
        printf("*** Welcome to Cal Poly's ATM ****\n");
        printf("Please enter your PIN: ");
        int pin;
        scanf("%d", &pin);

        if (pin == 1111) {
            pinValid = 1;
        } else {
            system("cls");
            printf("Invalid PIN. Please try again.\n");
            attempts++;
        }
    }

    if (!pinValid) {
        printf("Too many illegal PINs. Try later again.\n");
        return 0;
    }

    // Main menu loop
    int option = 0;
    while (option != 6) {
        displayMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                transferToSavings();
                break;
            case 2:
                transferToChecking();
                break;
            case 3:
                displaySavingsBalance();
                break;
            case 4:
                displayCheckingBalance();
                break;
            case 5:
                withdrawCash();
                break;
            case 6:
                printf("Thank you for using the ATM system.\n");
                break;
            default:
                system("cls");
                printf("Invalid option. Please select a valid option.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n*** Welcome To Cal Poly's ATM System ***\n");
    printf("(1) Transfer from checking account to savings account\n");
    printf("(2) Transfer from savings account to checking account\n");
    printf("(3) Savings account balance\n");
    printf("(4) Checking account balance\n");
    printf("(5) Withdraw Cash from either account\n");
    printf("(6) Exit\n");
    printf("==> Please select option (1-6): ");
}

void transferToSavings() {
    float amount;
    printf("Enter the amount to transfer from checking to savings: ");
    scanf("%f", &amount);

    if (amount > checking_balance) {
        printf("Transaction not completed. Insufficient balance in checking account.\n");
        printf("Current checking balance: $%.2f\n", checking_balance);
    } else {
        checking_balance -= amount;
        savings_balance += amount;
        printf("Transfer completed.\n");
        printf("New checking balance: $%.2f\n", checking_balance);
        printf("New savings balance: $%.2f\n", savings_balance);
    }
    system("cls");
}

void transferToChecking() {
    float amount;
    printf("Enter the amount to transfer from savings to checking: ");
    scanf("%f", &amount);

    if (amount > savings_balance) {
        printf("Transaction not completed. Insufficient balance in savings account.\n");
        printf("Current savings balance: $%.2f\n", savings_balance);
    } else {
        savings_balance -= amount;
        checking_balance += amount;
        printf("Transfer completed.\n");
        printf("New savings balance: $%.2f\n", savings_balance);
        printf("New checking balance: $%.2f\n", checking_balance);
    }
    system("cls");
}

void displaySavingsBalance() {
    printf("Savings account balance: $%.2f\n", savings_balance);
}

void displayCheckingBalance() {
    printf("Checking account balance: $%.2f\n", checking_balance);
}

void withdrawCash() {
    int account;
    float amount;
    printf("Withdraw from:\n");
    printf("(1) Savings Account\n");
    printf("(2) Checking Account\n");
    printf("Select account: ");
    scanf("%d", &account);

    if (account == 1) {
        printf("Enter amount to withdraw from savings: ");
        scanf("%f", &amount);
        if (amount > savings_balance) {
            printf("Transaction not completed. Insufficient balance in savings account.\n");
            printf("Current savings balance: $%.2f\n", savings_balance);
        } else {
            savings_balance -= amount;
            printf("Withdrawal completed.\n");
            printf("New savings balance: $%.2f\n", savings_balance);
        }
    } else if (account == 2) {
        printf("Enter amount to withdraw from checking: ");
        scanf("%f", &amount);
        if (amount > checking_balance) {
            printf("Transaction not completed. Insufficient balance in checking account.\n");
            printf("Current checking balance: $%.2f\n", checking_balance);
        } else {
            checking_balance -= amount;
            printf("Withdrawal completed.\n");
            printf("New checking balance: $%.2f\n", checking_balance);
        }
    } else {
        printf("Invalid account selection.\n");
    }
    system("cls");
}
