#pragma once
#include <string>
#include <map>
#include "Date.h"
using namespace std;

class User
{
private:
    string userId;
    string name;

    // borrowedBooks: key=bookId, value=dueDate
    map<string, Date> borrowedBooks;

public:
    User();
    User(const string &id, const string &username);

    string getId() const;
    string getName() const;

    void borrowBook(const string &bookId, const Date &dueDate);
    void returnBook(const string &bookId);
    const map<string, Date> &getBorrowedBooks() const;

    void display() const;

    int calculateFine(const Date &currentDate, int finePerDay) const;
};
