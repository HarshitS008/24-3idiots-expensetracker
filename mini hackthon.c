
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100
#define CATEGORIES 4

struct Expense {
    int category;
    double amount;
    char note[50];
};

struct Expense expenses[MAX];

char categoryNames[4][20] = {
    "Food", "Travel", "Books", "Entertainment"
};

double budget = 0;
double total = 0;
double categoryTotal[4] = {0};
int expenseCount = 0;


void clearInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}


int readInt(int *value) {
    int result = scanf("%d", value);
    clearInput();
    return result == 1;
}


int readAmount(double *value) {
    int result = scanf("%lf", value);
    clearInput();

    if (result != 1)
        return 0;

    return isfinite(*value) && *value > 0;
}


int saveBudget() {
    FILE *fp = fopen("budget.txt", "w");

    if (fp == NULL) {
        printf("Error saving budget!\n");
        return 0;
    }

    int ok = fprintf(fp, "%.2f\n", budget) > 0;

    if (fclose(fp) != 0)
        ok = 0;

    if (!ok)
        printf("Error writing budget file!\n");

    return ok;
}


void loadBudget() {
    FILE *fp = fopen("budget.txt", "r");
    double savedBudget;

    if (fp == NULL)
        return;

    if (fscanf(fp, "%lf", &savedBudget) == 1 &&
        isfinite(savedBudget) && savedBudget > 0) {
        budget = savedBudget;
    }

    fclose(fp);
}

int saveExpenses() {
    FILE *fp = fopen("expenses.txt", "w");

    if (fp == NULL) {
        printf("Error opening expense file!\n");
        return 0;
    }

    int ok = 1;

    for (int i = 0; i < expenseCount; i++) {
        if (fprintf(fp, "%d|%.2f|%s\n",
                    expenses[i].category,
                    expenses[i].amount,
                    expenses[i].note) < 0) {
            ok = 0;
            break;
        }
    }

    if (fclose(fp) != 0)
        ok = 0;

    if (!ok)
        printf("Error saving expenses!\n");

    return ok;
}


void loadExpenses() {
    FILE *fp = fopen("expenses.txt", "r");

    if (fp == NULL)
        return;

    char line[200];
    int category;
    double amount;
    char note[50];

    while (fgets(line, sizeof(line), fp) != NULL &&
           expenseCount < MAX) {

        if (sscanf(line, "%d|%lf|%49[^\n]",
                   &category, &amount, note) == 3) {

            if (category >= 1 && category <= 4 &&
                isfinite(amount) && amount > 0) {

                expenses[expenseCount].category = category;
                expenses[expenseCount].amount = amount;

                strcpy(expenses[expenseCount].note, note);

                expenseCount++;
                total += amount;
                categoryTotal[category - 1] += amount;
            }
        }
    }

    fclose(fp);
}


void setBudget() {
    double newBudget;

    do {
        printf("\nEnter monthly budget (Rs.): ");

        if (!readAmount(&newBudget)) {
            printf("Invalid amount! Try again.\n");
            newBudget = 0;
        }

    } while (newBudget <= 0);

    budget = newBudget;

    if (saveBudget())
        printf("Budget saved successfully!\n");

    if (total > budget) {
        printf("Warning: Existing expenses exceed this budget.\n");
    }
}


void addExpense() {
    int category;
    double amount;
    char note[50];

    if (expenseCount >= MAX) {
        printf("Expense storage is full!\n");
        return;
    }

    printf("\n========== ADD EXPENSE ==========\n");

    for (int i = 0; i < CATEGORIES; i++) {
        printf("%d. %s\n", i + 1, categoryNames[i]);
    }

    printf("Choose category: ");

    if (!readInt(&category) ||
        category < 1 || category > 4) {
        printf("Invalid category!\n");
        return;
    }

    printf("Enter amount (Rs.): ");

    if (!readAmount(&amount)) {
        printf("Invalid expense amount!\n");
        return;
    }

    printf("Enter expense note: ");

    if (fgets(note, sizeof(note), stdin) == NULL) {
        printf("Error reading note!\n");
        return;
    }

    if (strchr(note, '\n') == NULL)
        clearInput();

    note[strcspn(note, "\n")] = '\0';

    if (strlen(note) == 0)
        strcpy(note, "No note");

    /* Avoid file separator in notes */
    for (int i = 0; note[i] != '\0'; i++) {
        if (note[i] == '|')
            note[i] = '-';
    }

    expenses[expenseCount].category = category;
    expenses[expenseCount].amount = amount;
    strcpy(expenses[expenseCount].note, note);

    expenseCount++;
    total += amount;
    categoryTotal[category - 1] += amount;

    if (saveExpenses())
        printf("\nExpense added and saved successfully!\n");
    else
        printf("\nExpense added in memory, but saving failed.\n");

    if (total > budget) {
        printf("WARNING: Budget exceeded by Rs. %.2f\n",
               total - budget);
    }
    else if (total >= budget * 0.80) {
        printf("ALERT: You have used 80%% or more of your budget.\n");
    }
}

void viewExpenses() {
    printf("\n========== EXPENSE HISTORY ==========\n");

    if (expenseCount == 0) {
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("%-5s %-16s %-12s %s\n",
           "No.", "Category", "Amount", "Note");

    for (int i = 0; i < expenseCount; i++) {
        printf("%-5d %-16s Rs.%-9.2f %s\n",
               i + 1,
               categoryNames[expenses[i].category - 1],
               expenses[i].amount,
               expenses[i].note);
    }
}


int highestCategory() {
    int highest = 0;

    for (int i = 1; i < CATEGORIES; i++) {
        if (categoryTotal[i] > categoryTotal[highest])
            highest = i;
    }

    return highest;
}


void showSummary() {
    double remaining = budget - total;
    double percentage = (total / budget) * 100;

    printf("\n========== MONTHLY SUMMARY ==========\n");

    printf("Monthly Budget   : Rs. %.2f\n", budget);
    printf("Total Spending   : Rs. %.2f\n", total);
    printf("Remaining Budget : Rs. %.2f\n", remaining);
    printf("Budget Used      : %.2f%%\n", percentage);

    printf("\nCategory-wise Spending:\n");

    for (int i = 0; i < CATEGORIES; i++) {
        printf("%-16s : Rs. %.2f\n",
               categoryNames[i], categoryTotal[i]);
    }

    if (expenseCount > 0) {
        printf("\nHighest Spending Category: %s\n",
               categoryNames[highestCategory()]);
    } else {
        printf("\nNo expenses recorded yet.\n");
    }

    if (total > budget) {
        printf("\nWARNING: Monthly budget exceeded!\n");
        printf("Exceeded Amount: Rs. %.2f\n",
               total - budget);
    } else {
        printf("\nBudget Status: Within Budget\n");
    }
}


void spendingAdvisor() {
    double percentage = (total / budget) * 100;
    double remaining = budget - total;
    double dailyLimit;
    int daysLeft;

    printf("\n========== SMART SPENDING ADVISOR ==========\n");

    printf("Budget Used: %.2f%%\n", percentage);

    if (expenseCount == 0) {
        printf("No expenses recorded yet.\n");
        printf("Tip: Start tracking your daily expenses.\n");
    }
    else {
        if (percentage < 50) {
            printf("\nStatus: EXCELLENT\n");
            printf("Tip: Your spending is under control.\n");
        }
        else if (percentage < 80) {
            printf("\nStatus: GOOD\n");
            printf("Tip: Keep monitoring your expenses.\n");
        }
        else if (percentage <= 100) {
            printf("\nStatus: CAUTION\n");
            printf("Tip: Avoid unnecessary purchases.\n");
        }
        else {
            printf("\nStatus: OVER BUDGET\n");
            printf("Tip: Reduce optional expenses immediately.\n");
        }

        int highest = highestCategory();

        printf("\nHighest Spending Category: %s\n",
               categoryNames[highest]);

        printf("\nPersonalized Suggestion:\n");

        switch (highest) {
            case 0:
                printf("Try affordable canteen meals or homemade food.\n");
                break;

            case 1:
                printf("Use shared rides or public transport.\n");
                break;

            case 2:
                printf("Borrow books from the college library.\n");
                break;

            case 3:
                printf("Reduce unnecessary outings and subscriptions.\n");
                break;
        }
    }

    printf("\nEnter days remaining in the month: ");

    if (!readInt(&daysLeft) ||
        daysLeft < 1 || daysLeft > 31) {
        printf("Invalid days! Enter a value from 1 to 31.\n");
        return;
    }

    if (remaining > 0) {
        dailyLimit = remaining / daysLeft;

        printf("\nSuggested Daily Spending Limit: Rs. %.2f\n",
               dailyLimit);
    }
    else {
        printf("\nNo budget remaining for this month.\n");
        printf("Avoid additional non-essential expenses.\n");
    }
}

void deleteExpense() {
    int number;

    viewExpenses();

    if (expenseCount == 0)
        return;

    printf("\nEnter expense number to delete: ");

    if (!readInt(&number) ||
        number < 1 || number > expenseCount) {
        printf("Invalid expense number!\n");
        return;
    }

    int index = number - 1;

    total -= expenses[index].amount;

    categoryTotal[expenses[index].category - 1] -=
        expenses[index].amount;

    for (int i = index; i < expenseCount - 1; i++) {
        expenses[i] = expenses[i + 1];
    }

    expenseCount--;

    if (saveExpenses())
        printf("\nExpense deleted successfully!\n");
    else
        printf("\nExpense deleted in memory, but saving failed.\n");
}

int main() {
    int choice;

    printf("========================================\n");
    printf("       CAMPUSSPEND EXPENSE TRACKER\n");
    printf("             UPES BATCH 24\n");
    printf("========================================\n");

    loadBudget();
    loadExpenses();

    if (budget <= 0) {
        setBudget();
    }
    else {
        printf("\nSaved monthly budget: Rs. %.2f\n", budget);
        printf("Saved expenses loaded: %d\n", expenseCount);
    }

    do {
        printf("\n============== MAIN MENU ==============\n");
        printf("1. Add Expense\n");
        printf("2. View Expense History\n");
        printf("3. Monthly Expense Summary\n");
        printf("4. Smart Spending Advisor\n");
        printf("5. Update Monthly Budget\n");
        printf("6. Delete Expense\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");

        if (!readInt(&choice))
            choice = 0;

        switch (choice) {
            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                showSummary();
                break;

            case 4:
                spendingAdvisor();
                break;

            case 5:
                setBudget();
                break;

            case 6:
                deleteExpense();
                break;

            case 7:
                printf("\nThank you for using CampusSpend!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}
