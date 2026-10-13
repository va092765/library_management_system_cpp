# Library Management System (C++)

A console-based Library Management System written in C++17. It is the C++ rewrite of my earlier C project, using classes, the STL and file handling instead of structs and fixed-size arrays.

## Features
- Add new books
- List all books with their status (Available / Issued)
- Search books by title or author
- Issue and return books
- Delete books
- Data saved automatically to `books.txt`

## Concepts Used
- Classes and encapsulation (`Book`, `Library`)
- `std::vector` for dynamic storage
- `std::string` instead of `char[]`
- File I/O with `ifstream` / `ofstream`
- Constructor / destructor (load on start, save on exit)
- Lambdas with `std::remove_if`
- Input validation

## Build and Run
```bash
vi project.cpp
c++ project.cpp
./a.out
```

## Menu
```
1. Add book
2. List books
3. Search
4. Issue book
5. Return book
6. Delete book
0. Exit
```

## Data Format
Books are stored one per line in `books.txt`:
```

## Future Improvements
- Member management with due dates and fines
- Split into header and source files
- Replace the text file with SQLite

