#pragma once
#include <string>
#include "Date.h"

using namespace std;

class Book
{
private:
    string id;
    string title;
    string author;
    bool isAvailable;

public:
    Book();
    Book(const string &bookId, const string &bookTitle, const string &bookAuthor);

    string getId() const;
    string getTitle() const;
    string getAuthor() const;
    bool available() const;
    void setAvailability(bool status);

    void display() const;
};
