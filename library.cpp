#include <iostream>
#include <cctype>
#include <cstring>
#include <limits>
#include <algorithm>
using namespace std;

class Book {
private:
    string id, isbn, title, author, edition, publication, category;

public:
    Book() {}
    Book(string id, string isbn, string title, string author, string edition, string publication, string category) {
        this->id = id;
        this->isbn = isbn;
        this->title = title;
        this->author = author;
        this->edition = edition;
        this->publication = publication;
        this->category = category;
    }

    string getId() { return id; }
    string getCategory() { return category; }
    void editBook(string isbn, string title, string author, string edition, string publication) {
        this->isbn = isbn;
        this->title = title;
        this->author = author;
        this->edition = edition;
        this->publication = publication;
    }
    void displayBook() {
        cout << id << "\t" << isbn << "\t" << title << "\t" << author << "\t" << edition << "\t" << publication << "\t" << category << endl;
    }
};

class Library {
private:
    Book books[100];
    int bookCount;

public:
    Library() { bookCount = 0; }

    bool isValidCategory(string category) {
        transform(category.begin(), category.end(), category.begin(), ::tolower);
        return category == "fiction" || category == "non-fiction";
    }
    bool isDuplicateID(string id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == id) {
                return true;
            }
        }
        return false;
    }
    bool isAlphanumeric(const string &str) {
        for (char ch : str) {
            if (!isalnum(ch)) return false;
        }
        return true;
    }
    void addBook() {
        string category;
        bool validCategory = false;
        while (!validCategory) {
            cout << "Enter Category (Fiction/Non-fiction): ";
            cin >> category;
            transform(category.begin(), category.end(), category.begin(), ::tolower);
            if (category == "fiction" || category == "non-fiction") {
                validCategory = true;
            } else {
                cout << "Category not found! Please enter Fiction or Non-fiction." << endl;
            }
        }
        string id, isbn, title, author, edition, publication;
        bool validID = false;
        while (!validID) {
            cout << "Enter Book ID (alphanumeric): ";
            cin >> id;
            if (!isAlphanumeric(id)) {
                cout << "Invalid ID! It must be alphanumeric." << endl;
                continue;
            }
            if (!isDuplicateID(id)) {
                validID = true;
            } else {
                cout << "Duplicate ID! Enter a unique ID." << endl;
            }
        }
        cout << "Enter ISBN: "; cin >> isbn;
        cout << "Enter Title: "; cin.ignore(); getline(cin, title);
        cout << "Enter Author: "; getline(cin, author);
        cout << "Enter Edition: "; getline(cin, edition);
        cout << "Enter Publication: "; getline(cin, publication);
        books[bookCount++] = Book(id, isbn, title, author, edition, publication, category);
        cout << "Book added successfully!" << endl;
    }
    void editBook() {
        string id;
        cout << "Enter Book ID to edit: ";
        cin >> id;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == id) {
                string isbn, title, author, edition, publication;
                cout << "Enter new ISBN: "; cin >> isbn;
                cout << "Enter new Title: "; cin.ignore(); getline(cin, title);
                cout << "Enter new Author: "; getline(cin, author);
                cout << "Enter new Edition: "; getline(cin, edition);
                cout << "Enter new Publication: "; getline(cin, publication);
                books[i].editBook(isbn, title, author, edition, publication);
                cout << "Book edited successfully!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
    void searchBook() {
        string id;
        cout << "Enter Book ID to search: ";
        cin >> id;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == id) {
                books[i].displayBook();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
    void deleteBook() {
        string id;
        cout << "Enter Book ID to delete: ";
        cin >> id;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == id) {
                books[i].displayBook();
                cout << "Do you want to delete this book? (yes/no): ";
                string confirm;
                cin >> confirm;
                if (confirm == "yes") {
                    for (int j = i; j < bookCount - 1; j++) {
                        books[j] = books[j + 1];
                    }
                    bookCount--;
                    cout << "Book deleted successfully!" << endl;
                }
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
    void viewBooksByCategory() {
        string category;
        bool validCategory = false;
        while (!validCategory) {
            cout << "Enter Category (Fiction/Non-fiction): ";
            cin >> category;
            transform(category.begin(), category.end(), category.begin(), ::tolower);
            if (category == "fiction" || category == "non-fiction") {
                validCategory = true;
            } else {
                cout << "Category not found! Please enter Fiction or Non-fiction." << endl;
            }
        }
        cout << "ID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory" << endl;
        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getCategory() == category) {
                books[i].displayBook();
                found = true;
            }
        }
        if (!found) {
            cout << "No books found in this category." << endl;
        }
    }
    void viewAllBooks() {
        if (bookCount == 0) {
            cout << "No books available." << endl;
            return;
        }
        cout << "ID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory" << endl;
        for (int i = 0; i < bookCount; i++) {
            books[i].displayBook();
        }
    }
};

int main() {
    Library library;
    bool running = true;
    while (running) {
        string input;
        int choice;
        cout << "\nLibrary Management System" << endl;
        cout << "1 - Add Book" << endl;
        cout << "2 - Edit Book" << endl;
        cout << "3 - Search Book" << endl;
        cout << "4 - Delete Book" << endl;
        cout << "5 - View Books by Category" << endl;
        cout << "6 - View All Books" << endl;
        cout << "7 - Exit" << endl;
        cout << "Enter choice: ";
        cin >> input;

        if (input.length() != 1 || !isdigit(input[0]) || input[0] < '1' || input[0] > '7' || cin.peek() != '\n') {
            cout << "Invalid input! Please enter a single valid menu number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        choice = input[0] - '0';
        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.editBook(); break;
            case 3: library.searchBook(); break;
            case 4: library.deleteBook(); break;
            case 5: library.viewBooksByCategory(); break;
            case 6: library.viewAllBooks(); break;
            case 7: running = false; break;
        }
    }
    return 0;
}