// Library Management System - C++ version
// Build: g++ -std=c++17 -Wall -o library library.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

class Book {
public:
    Book(int id, std::string title, std::string author, bool issued = false)
        : id_(id), title_(std::move(title)), author_(std::move(author)), issued_(issued) {}

    int id() const { return id_; }
    const std::string& title() const { return title_; }
    const std::string& author() const { return author_; }
    bool isIssued() const { return issued_; }
    void issue() { issued_ = true; }
    void giveBack() { issued_ = false; }

    void print() const {
        std::cout << id_ << " | " << title_ << " | " << author_
                  << " | " << (issued_ ? "Issued" : "Available") << "\n";
    }

    // One line per book: id|title|author|issued
    std::string serialize() const {
        return std::to_string(id_) + "|" + title_ + "|" + author_ + "|" + (issued_ ? "1" : "0");
    }

private:
    int id_;
    std::string title_;
    std::string author_;
    bool issued_;
};

class Library {
public:
    explicit Library(std::string file) : file_(std::move(file)) { load(); }
    ~Library() { save(); }

    void addBook(const std::string& title, const std::string& author) {
        books_.emplace_back(nextId_++, title, author);
        std::cout << "Book added.\n";
    }

    void listBooks() const {
        if (books_.empty()) { std::cout << "No books.\n"; return; }
        for (const auto& b : books_) b.print();
    }

    void search(const std::string& keyword) const {
        bool found = false;
        for (const auto& b : books_) {
            if (b.title().find(keyword) != std::string::npos ||
                b.author().find(keyword) != std::string::npos) {
                b.print();
                found = true;
            }
        }
        if (!found) std::cout << "No match.\n";
    }

    void issueBook(int id) {
        Book* b = find(id);
        if (!b)              std::cout << "Book not found.\n";
        else if (b->isIssued()) std::cout << "Already issued.\n";
        else { b->issue(); std::cout << "Book issued.\n"; }
    }

    void returnBook(int id) {
        Book* b = find(id);
        if (!b)               std::cout << "Book not found.\n";
        else if (!b->isIssued()) std::cout << "Book was not issued.\n";
        else { b->giveBack(); std::cout << "Book returned.\n"; }
    }

    void deleteBook(int id) {
        auto it = std::remove_if(books_.begin(), books_.end(),
                                 [id](const Book& b) { return b.id() == id; });
        if (it == books_.end()) std::cout << "Book not found.\n";
        else { books_.erase(it, books_.end()); std::cout << "Book deleted.\n"; }
    }

private:
    Book* find(int id) {
        for (auto& b : books_) if (b.id() == id) return &b;
        return nullptr;
    }

    void load() {
        std::ifstream in(file_);
        std::string line;
        while (std::getline(in, line)) {
            std::stringstream ss(line);
            std::string id, title, author, issued;
            if (std::getline(ss, id, '|') && std::getline(ss, title, '|') &&
                std::getline(ss, author, '|') && std::getline(ss, issued, '|')) {
                int n = std::stoi(id);
                books_.emplace_back(n, title, author, issued == "1");
                nextId_ = std::max(nextId_, n + 1);
            }
        }
    }

    void save() const {
        std::ofstream out(file_);
        for (const auto& b : books_) out << b.serialize() << "\n";
    }

    std::vector<Book> books_;
    std::string file_;
    int nextId_ = 1;
};

static int readInt(const std::string& prompt) {
    int v;
    std::cout << prompt;
    while (!(std::cin >> v)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return v;
}

static std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

int main() {
    Library lib("books.txt");
    int choice;
    do {
        std::cout << "\n--- Library Menu ---\n"
                  << "1. Add book\n2. List books\n3. Search\n"
                  << "4. Issue book\n5. Return book\n6. Delete book\n0. Exit\n";
        choice = readInt("Choice: ");
        switch (choice) {
            case 1: { auto t = readLine("Title: "); auto a = readLine("Author: "); lib.addBook(t, a); break; }
            case 2: lib.listBooks(); break;
            case 3: lib.search(readLine("Keyword: ")); break;
            case 4: lib.issueBook(readInt("Book ID: ")); break;
            case 5: lib.returnBook(readInt("Book ID: ")); break;
            case 6: lib.deleteBook(readInt("Book ID: ")); break;
            case 0: std::cout << "Saved. Bye!\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
