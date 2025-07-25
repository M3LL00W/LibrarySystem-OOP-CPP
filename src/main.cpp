#include "LibrarySystem.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void displayMenu()
{
    cout << "\n--- Library Management System ---\n";
    cout << "1. Add a new book\n";
    cout << "2. Register a new user\n";
    cout << "3. Borrow a book\n";
    cout << "4. Return a book\n";
    cout << "5. Calculate user fine\n";
    cout << "6. List all books\n";
    cout << "7. List all users\n";
    cout << "8. Exit\n";
    cout << "---------------------------------\n";
    cout << "Enter your choice: ";
}

int main()
{
    LibrarySystem library;
    string bookFile = "data/books.txt";
    string userFile = "data/users.txt";

    // Load existing data
    library.loadBooksFromFile(bookFile);
    library.loadUsersFromFile(userFile);

    int choice;
    string bookId, title, author, userId, userName;

    while (true)
    {
        displayMenu();
        cin >> choice;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 8)
        {
            break;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter Book ID: ";
            getline(cin, bookId);
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            library.addBook(bookId, title, author);
            break;
        case 2:
            cout << "Enter User ID: ";
            getline(cin, userId);
            cout << "Enter User Name: ";
            getline(cin, userName);
            library.registerUser(userId, userName);
            break;
        case 3:
            cout << "Enter User ID: ";
            getline(cin, userId);
            cout << "Enter Book ID: ";
            getline(cin, bookId);
            library.borrowBook(userId, bookId);
            break;
        case 4:
            cout << "Enter User ID: ";
            getline(cin, userId);
            cout << "Enter Book ID: ";
            getline(cin, bookId);
            library.returnBook(userId, bookId);
            break;
        case 5:
            cout << "Enter User ID to calculate fine: ";
            getline(cin, userId);
            {
                int fine = library.getUserFine(userId);
                if (fine >= 0)
                {
                    cout << "Total outstanding fine for user " << userId << " is Rs. " << fine << endl;
                }
            }
            break;
        case 6:
            cout << "\n--- All Books ---\n";
            library.listAllBooks();
            break;
        case 7:
            cout << "\n--- All Users ---\n";
            library.listAllUsers();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    // Save data before exiting
    library.saveBooksToFile(bookFile);
    library.saveUsersToFile(userFile);
    cout << "Data saved. Exiting system. Goodbye! 👋\n";

    return 0;
}