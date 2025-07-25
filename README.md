#  Library Management System

A simple Library Management System built in **C++** using concepts of **Object-Oriented Programming**, **STL**, and **File I/O**. This project helps manage books and users, enabling features like book borrowing, returning, registration, and saving/loading data without using any SQL database.

---

##  Features

-  Add new books to the library
-  Register new users
-  Borrow and return books
-  Persistent data storage using file I/O 
-  Due date calculation for borrowed books
-  Built-in Date class
-  Uses STL (`unordered_map`, `vector`)
-  Modular design using header and source files

---

##  Tech Stack

- **Language**: C++
- **Concepts**: OOP (Classes, Inheritance), STL, File I/O
- **Compiler**: `g++` with C++17 support

---


---

##  How to Compile and Run

###  Prerequisites

Make sure you have **g++** installed:

```bash
g++ --version
```
## Compile using the below command
```
  g++ src/*.cpp main.cpp -o library_app
```
## Run
```
  ./library_app
```

 Sample Book & User Data

books.txt
```
  B001
  Clean Code
  Robert C. Martin
  1
  B002
  The Pragmatic Programmer
  Andrew Hunt
  1
```
users.txt
```
  U001
  Sai Charan
  1
  B001
  25-07-2025
```



