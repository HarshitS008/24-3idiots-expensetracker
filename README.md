# CampusSpend - Personal Expense Tracker

**C Programming Mini Hackathon | UPES | Batch 24**

## Team Details

- **Batch:** 24
- **Team members:**
  1. Anuj Choudhary
  2. Ali Hasan
  3. Harshit Sangani
- **Problem number:** 4 - Personal Expense Tracker
- **Language:** C

## Problem Statement

Build a simple expense tracker to help a student manage a monthly budget. The program should record expenses under different categories, calculate total spending and remaining budget, identify the category with the highest spending, and warn the user if the budget is exceeded.

## Our Solution

We developed **CampusSpend**, a menu-driven C program for students to keep track of expenses. It stores the monthly budget and expense records in text files so the information can be loaded when the program is opened again. We also added a basic Smart Spending Advisor that gives suggestions based on spending patterns.

## Objectives

- Record expenses under Food, Travel, Books and Entertainment.
- Calculate total expenses and remaining budget.
- Show category-wise spending and the highest-spending category.
- Warn when spending crosses the monthly budget.
- Save and load records using file handling.
- Provide simple spending tips and a suggested daily spending limit.

## Features

1. **Add Expense:** Enter a category, amount and short note.
2. **Expense History:** View saved expense records.
3. **Monthly Summary:** View budget, total spending, remaining balance and category totals.
4. **Smart Spending Advisor:** See budget-use percentage, spending status and category-specific tips. Enter days remaining to calculate a suggested daily limit.
5. **Update Budget:** Change the stored budget.
6. **Delete Expense:** Remove an incorrect record by its displayed number.
7. **File Handling:** Automatically save and reload the budget and expenses.
8. **Input Validation:** Reject invalid menu selections, categories, amounts and day counts.

## Algorithm

1. Start the program.
2. Load the saved budget from `budget.txt` and expenses from `expenses.txt`, if available.
3. If there is no valid saved budget, ask the user to enter one.
4. Display the menu and accept a choice.
5. For **Add Expense**, validate the category and amount, save the expense and update totals.
6. For **Expense History**, display all recorded expenses.
7. For **Monthly Summary**, calculate the remaining budget, spending percentage, category totals and highest-spending category.
8. For **Smart Spending Advisor**, check the spending percentage, suggest a way to reduce expenses and calculate a daily spending limit from the remaining budget and days left.
9. For **Update Budget** or **Delete Expense**, update the records and save them to files.
10. Repeat the menu until the user chooses Exit.

## C Programming Concepts Used

| Concept | How it is used |
| --- | --- |
| Variables and data types | Store budget, amounts, counts and choices |
| `if-else` and `switch` | Validate input, select menu actions and show advice |
| Loops | Repeat the menu and process records |
| Arrays | Store category names, totals and expenses |
| Structures | Store an expense's category, amount and note |
| Functions | Separate adding, deleting, saving, loading and reporting |
| Strings | Store expense notes and category names |
| File handling | Read and write text files using `FILE *`, `fopen`, `fprintf`, `fscanf`, `fgets` and `fclose` |

## Project Files

```text
CampusSpend/
|-- expense_tracker.c
|-- README.md
|-- presentation.pptx       (add before Lab 2)
|-- budget.txt              (generated when program runs)
`-- expenses.txt            (generated when expenses are saved)
```

`budget.txt` and `expenses.txt` are local data files. They do not need to be uploaded with the source code. The program uses the working directory from which it is run.

## How to Compile and Run

You need GCC or another C compiler.

**Compile:**

```bash
gcc expense_tracker.c -o expense_tracker -lm
```

**Run on Windows:**

```bash
expense_tracker.exe
```

**Run on Linux or macOS:**

```bash
./expense_tracker
```

## Sample Test Cases

These are **expected results**. Fill in the **actual result** column after running the final program; do not mark them as passed without testing.

| Test | Input / Action | Expected Result | Actual Result |
| --- | --- | --- | --- |
| 1. Normal spending | Budget Rs. 5000; Food Rs. 1200, Travel Rs. 800, Books Rs. 500 | Total Rs. 2500; remaining Rs. 2500; highest category Food | To be tested |
| 2. Over budget | Budget Rs. 1000; Food Rs. 700, Travel Rs. 500 | Total Rs. 1200; exceeded by Rs. 200 | To be tested |
| 3. No expenses | Budget Rs. 3000; view summary | Total Rs. 0; remaining Rs. 3000; no expenses recorded | To be tested |
| 4. Invalid amount | Enter -100 as an expense | Invalid expense amount; record not added | To be tested |
| 5. File handling | Add an expense, exit, reopen in the same working directory | Saved expense loads again | To be tested |
| 6. Delete expense | Add two expenses, delete expense number 1 | First expense removed and totals updated | To be tested |
| 7. Advisor | Budget Rs. 5000; spent Rs. 4250; 10 days left | 85% used; CAUTION; daily limit Rs. 75 | To be tested |

**Testing note:** For each independent test, use a fresh copy of the data files or clear the previous test data first. Otherwise, saved expenses from earlier tests will affect totals.

## Limitations

- Stores up to 100 expenses.
- Keeps one budget and one set of expense records; it does not automatically create separate monthly histories.
- Saves data in plain-text files, not a database.
- The Smart Spending Advisor uses simple rules, not artificial intelligence.

## Conclusion

CampusSpend helps students record expenses and check how much of their budget is left. Through this project, we practiced basic C programming concepts along with file handling, functions, structures and input validation. The spending suggestions are an extra feature to help users think about where they can save money.

## Team Contributions

The following is a suggested division of work for the three members. Update it to match the work each person actually completes.

- **Anuj Choudhary:** Program structure, main menu, adding expenses, and expense history.
- **Ali Hasan:** File handling (saving and loading records), updating the budget, and deleting expenses.
- **Harshit Sangani:** Monthly summary, Smart Spending Advisor, test cases, README, and presentation preparation.

All three members should test the final program together and be able to explain the code during the demonstration.
