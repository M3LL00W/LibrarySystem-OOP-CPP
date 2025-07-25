#include "User.h"
#include <iostream>
using namespace std;

User::User() {}

User::User(const string &id, const string &username)
    : userId(id), name(username) {}

string User::getId() const { return userId; }
string User::getName() const { return name; }

void User::borrowBook(const string &bookId, const Date &dueDate)
{
    borrowedBooks[bookId] = dueDate;
}

void User::returnBook(const string &bookId)
{
    borrowedBooks.erase(bookId);
}

const std::map<string, Date> &User::getBorrowedBooks() const
{
    return borrowedBooks;
}

void User::display() const
{
    std::cout << "User ID: " << userId << " | Name: " << name << "\nBorrowed Books:\n";
    if (borrowedBooks.empty())
    {
        std::cout << "  None\n";
    }
    else
    {
        for (const auto &[bookId, dueDate] : borrowedBooks)
        {
            std::cout << "  Book ID: " << bookId << ", Due Date: " << dueDate.toString() << "\n";
        }
    }
}

int User::calculateFine(const Date &currentDate, int finePerDay) const
{
    int totalFine = 0;
    for (const auto &[bookId, dueDate] : borrowedBooks)
    {
        if (dueDate < currentDate)
        {
            int overdueDays = dueDate.daysBetween(currentDate);
            totalFine += overdueDays * finePerDay;
        }
    }
    return totalFine;
}
