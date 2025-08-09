#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Expense {
    string date;
    string category;
    float amount;
    string note;
};

vector<Expense> expenses;

// Load existing data
void loadExpenses() {
    ifstream file("expenses.txt");
    Expense e;
    while (file >> e.date >> e.category >> e.amount) {
        getline(file, e.note); // get note (rest of the line)
        expenses.push_back(e);
    }
    file.close();
}

// Save data on exit
void saveExpenses() {
    ofstream file("expenses.txt");
    for (Expense e : expenses) {
        file << e.date << " " << e.category << " " << e.amount << " " << e.note << endl;
    }
    file.close();
}

void addExpense() {
    Expense e;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> e.date;
    cout << "Enter category (Food, Travel, Bills, etc.): ";
    cin >> e.category;
    cout << "Enter amount: ";
    cin >> e.amount;
    cout << "Enter note: ";
    cin.ignore();
    getline(cin, e.note);
    expenses.push_back(e);
    cout << "✅ Expense added!\n";
}

void showAllExpenses() {
    cout << "\nAll Expenses:\n";
    cout << left << setw(12) << "Date" << setw(10) << "Category" << setw(10) << "Amount" << "Note" << endl;
    for (Expense e : expenses) {
        cout << left << setw(12) << e.date << setw(10) << e.category << setw(10) << e.amount << e.note << endl;
    }
}

void showTotalExpense() {
    float total = 0;
    for (Expense e : expenses)
        total += e.amount;
    cout << "\n💰 Total Expense: ₹" << total << endl;
}

void categorySummary() {
    string category;
    cout << "Enter category to summarize: ";
    cin >> category;
    float sum = 0;
    for (Expense e : expenses) {
        if (e.category == category)
            sum += e.amount;
    }
    cout << "📊 Total spent on " << category << ": ₹" << sum << endl;
}

int main() {
    loadExpenses();

    int choice;
    do {
        cout << "\n📋 Personal Expense Tracker\n";
        cout << "1. Add Expense\n";
        cout << "2. Show All Expenses\n";
        cout << "3. Show Total Expense\n";
        cout << "4. Category Summary\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addExpense(); break;
            case 2: showAllExpenses(); break;
            case 3: showTotalExpense(); break;
            case 4: categorySummary(); break;
            case 5: saveExpenses(); cout << "💾 Data saved. Exiting...\n"; break;
            default: cout << "❌ Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
