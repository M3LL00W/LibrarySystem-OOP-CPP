#pragma once
#include <map>
#include <string>
#include "Book.h"
#include "User.h"
#include "Date.h"
using namespace std;

class LibrarySystem
{
private:
    map<string, Book> books;
    map<string, User> users;

    const int loanPeriodDays = 14;
    const int finePerDay = 2;

public:
    LibrarySystem();

    void loadBooksFromFile(const string &filename);
    void saveBooksToFile(const string &filename);

    void loadUsersFromFile(const string &filename);
    void saveUsersToFile(const string &filename);

    void addBook(const string &id, const string &title, const string &author);
    void registerUser(const string &userId, const string &userName);

    bool borrowBook(const string &userId, const string &bookId);
    bool returnBook(const string &userId, const string &bookId);

    void listAllBooks() const;
    void listAllUsers() const;

    int getUserFine(const string &userId) const;
};
