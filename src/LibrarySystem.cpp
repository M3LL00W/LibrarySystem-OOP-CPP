#include "LibrarySystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

LibrarySystem::LibrarySystem() {}

void LibrarySystem::loadBooksFromFile(const string &filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
        return;

    string id, title, author;
    bool available;
    while (getline(fin, id))
    {
        getline(fin, title);
        getline(fin, author);
        fin >> available;
        fin.ignore();
        books[id] = Book(id, title, author);
        books[id].setAvailability(available);
    }
    fin.close();
}

void LibrarySystem::saveBooksToFile(const string &filename)
{
    ofstream fout(filename);
    for (const auto &[id, book] : books)
    {
        fout << book.getId() << "\n"
             << book.getTitle() << "\n"
             << book.getAuthor() << "\n"
             << book.available() << "\n";
    }
    fout.close();
}

void LibrarySystem::loadUsersFromFile(const string &filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
        return;

    string userId, userName, bookId, dueDateStr;
    int borrowedCount;
    while (getline(fin, userId))
    {
        getline(fin, userName);
        fin >> borrowedCount;
        fin.ignore();

        User user(userId, userName);
        for (int i = 0; i < borrowedCount; ++i)
        {
            getline(fin, bookId);
            getline(fin, dueDateStr);
            user.borrowBook(bookId, Date::fromString(dueDateStr));
        }
        users[userId] = user;
    }
    fin.close();
}

void LibrarySystem::saveUsersToFile(const string &filename)
{
    ofstream fout(filename);
    for (const auto &[userId, user] : users)
    {
        fout << user.getId() << "\n"
             << user.getName() << "\n"
             << user.getBorrowedBooks().size() << "\n";
        for (const auto &[bookId, dueDate] : user.getBorrowedBooks())
        {
            fout << bookId << "\n"
                 << dueDate.toString() << "\n";
        }
    }
    fout.close();
}

void LibrarySystem::addBook(const string &id, const string &title, const string &author)
{
    if (books.count(id))
    {
        cout << "Error: Book with this ID already exists.\n";
        return;
    }
    books[id] = Book(id, title, author);
    cout << "Book added successfully.\n";
}

void LibrarySystem::registerUser(const string &userId, const string &userName)
{
    if (users.count(userId))
    {
        cout << "Error: User with this ID already exists.\n";
        return;
    }
    users[userId] = User(userId, userName);
    cout << "User registered successfully.\n";
}

bool LibrarySystem::borrowBook(const string &userId, const string &bookId)
{
    auto userIt = users.find(userId);
    if (userIt == users.end())
    {
        cout << "Error: User not found.\n";
        return false;
    }

    auto bookIt = books.find(bookId);
    if (bookIt == books.end())
    {
        cout << "Error: Book not found.\n";
        return false;
    }

    if (!bookIt->second.available())
    {
        cout << "Book is currently not available.\n";
        return false;
    }

    // *** CRITICAL BUG FIX: Correctly calculate due date ***
    time_t now = time(nullptr);
    tm *dueDateTm = localtime(&now);
    dueDateTm->tm_mday += loanPeriodDays; // Add loan period days
    mktime(dueDateTm);                    // Normalize the date (handles month/year rollovers)
    Date dueDate = Date::today().addDays(loanPeriodDays);


    bookIt->second.setAvailability(false);
    userIt->second.borrowBook(bookId, dueDate);

    cout << "Book borrowed successfully. Due date: " << dueDate.toString() << "\n";
    return true;
}

bool LibrarySystem::returnBook(const string &userId, const string &bookId)
{
    auto userIt = users.find(userId);
    if (userIt == users.end())
    {
        cout << "Error: User not found.\n";
        return false;
    }

    auto bookIt = books.find(bookId);
    if (bookIt == books.end())
    {
        cout << "Error: Book not found.\n";
        return false;
    }

    User &user = userIt->second;
    const auto &borrowedBooks = user.getBorrowedBooks();
    auto borrowedIt = borrowedBooks.find(bookId);

    if (borrowedIt == borrowedBooks.end())
    {
        cout << "Error: This user has not borrowed the specified book.\n";
        return false;
    }

    Date dueDate = borrowedIt->second;
    Date today = Date::today();
    int fineAmount = 0;

    if (dueDate < today)
    {
        int overdueDays = dueDate.daysBetween(today);
        fineAmount = overdueDays * finePerDay;
    }

    bookIt->second.setAvailability(true);
    user.returnBook(bookId);

    cout << "Book returned successfully.\n";
    if (fineAmount > 0)
    {
        cout << "A fine of Rs. " << fineAmount << " has been charged for the overdue return.\n";
    }
    return true;
}

void LibrarySystem::listAllBooks() const
{
    if (books.empty())
    {
        cout << "No books in the library.\n";
        return;
    }
    for (const auto &[id, book] : books)
    {
        book.display();
    }
}

void LibrarySystem::listAllUsers() const
{
    if (users.empty())
    {
        cout << "No users registered in the system.\n";
        return;
    }
    for (const auto &[id, user] : users)
    {
        user.display();
        cout << "---------------------\n";
    }
}

int LibrarySystem::getUserFine(const string &userId) const
{
    auto userIt = users.find(userId);
    if (userIt == users.end())
    {
        cout << "Error: User not found.\n";
        return -1; // Indicate error
    }
    return userIt->second.calculateFine(Date::today(), finePerDay);
}