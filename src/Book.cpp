#include "Book.h"
#include <iostream>
using namespace std;

Book::Book() : isAvailable(true) {}

Book::Book(const string &bookId, const string &bookTitle, const string &bookAuthor)
    : id(bookId), title(bookTitle), author(bookAuthor), isAvailable(true) {}

string Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
bool Book::available() const { return isAvailable; }
void Book::setAvailability(bool status) { isAvailable = status; }

void Book::display() const
{
    cout << "ID: " << id << " | Title: " << title << " | Author: " << author << " | Available: " << (isAvailable ? "Yes" : "No") << std::endl;
}
