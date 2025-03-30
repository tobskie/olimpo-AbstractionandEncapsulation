#include <iostream>
#include <cctype>
#include <limits>
#include <cstring>
using namespace std;

// Custom setw-like function for field width
const char* setFieldWidth(const char* str, int width) {
    static char buffer[100];
    int len = strlen(str);
    if (len >= width) {
        return str;
    }
    
    strcpy(buffer, str);
    for (int i = len; i < width; i++) {
        buffer[i] = ' ';
    }
    buffer[width] = '\0';
    return buffer;
}

class Book {
private:
    char id[20], isbn[20], title[50], author[50], edition[20], publication[50], category[20];

public:
    Book() {}
    Book(const char *id, const char *isbn, const char *title, const char *author, const char *edition, const char *publication, const char *category) {
        strcpy(this->id, id);
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        strcpy(this->edition, edition);
        strcpy(this->publication, publication);
        strcpy(this->category, category);
    }

    const char* getId() { return id; }
    const char* getCategory() { return category; }
    void editBook(const char *isbn, const char *title, const char *author, const char *edition, const char *publication) {
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        strcpy(this->edition, edition);
        strcpy(this->publication, publication);
    }
    void displayBook() {
        cout << setFieldWidth(id, 10) << " " 
             << setFieldWidth(isbn, 15) << " " 
             << setFieldWidth(title, 25) << " " 
             << setFieldWidth(author, 20) << " " 
             << setFieldWidth(edition, 10) << " " 
             << setFieldWidth(publication, 20) << " " 
             << setFieldWidth(category, 15) << endl;
    }
};

class Library {
private:
    Book books[100];
    int bookCount;

public:
    Library() { bookCount = 0; }

    void toLowerCase(char *str) {
        for (int i = 0; str[i] != '\0'; i++) {
            str[i] = tolower(str[i]);
        }
    }

    bool isValidCategory(const char* category) {
        char temp[20];
        strcpy(temp, category);
        toLowerCase(temp);
        return (strcmp(temp, "fiction") == 0 || strcmp(temp, "non-fiction") == 0);
    }
    bool isDuplicateID(const char *id) {
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                return true;
            }
        }
        return false;
    }
    bool isAlphanumeric(const char *str) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (!isalnum(str[i])) return false;
        }
        return true;
    }
    void addBook() {
        char id[20], isbn[20], title[50], author[50], edition[20], publication[50], category[20];
        bool validID = false;
        while (!validID) {
            cout << "Enter Book ID (alphanumeric): ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Title: "; cin.getline(title, 50);
        cout << "Enter Author: "; cin.getline(author, 50);
        cout << "Enter Edition: "; cin.getline(edition, 20);
        cout << "Enter Publication: "; cin.getline(publication, 50);
        
        // Modified category input with validation loop
        bool validCategory = false;
        while (!validCategory) {
            cout << "Enter Category (Fiction/Non-fiction): ";
            cin.getline(category, 20);
            toLowerCase(category);
            
            if (isValidCategory(category)) {
                validCategory = true;
            } else {
                cout << "Invalid Category! Please enter either 'Fiction' or 'Non-fiction'." << endl;
            }
        }

        books[bookCount++] = Book(id, isbn, title, author, edition, publication, category);
        cout << "Book added successfully!" << endl;
    }
    void editBook() {
        char id[20];
        cout << "Enter Book ID to edit: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                char isbn[20], title[50], author[50], edition[20], publication[50];
                cout << "Enter new ISBN: "; cin >> isbn;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter new Title: "; cin.getline(title, 50);
                cout << "Enter new Author: "; cin.getline(author, 50);
                cout << "Enter new Edition: "; cin.getline(edition, 20);
                cout << "Enter new Publication: "; cin.getline(publication, 50);
                books[i].editBook(isbn, title, author, edition, publication);
                cout << "Book edited successfully!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
    void searchBook() {
        char id[20];
        cout << "Enter Book ID to search: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                displayHeader();
                books[i].displayBook();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
    void deleteBook() {
        char id[20];
        cout << "Enter Book ID to delete: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }
                bookCount--;
                cout << "Book deleted successfully!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
    void displayHeader() {
        cout << setFieldWidth("ID", 10) << " " 
             << setFieldWidth("ISBN", 15) << " " 
             << setFieldWidth("Title", 25) << " " 
             << setFieldWidth("Author", 20) << " " 
             << setFieldWidth("Edition", 10) << " " 
             << setFieldWidth("Publication", 20) << " " 
             << setFieldWidth("Category", 15) << endl;
        
        cout << "---------- --------------- ------------------------- -------------------- --------- ------------------- ---------------" << endl;
    }
    void viewBooksByCategory() {
        char category[20];
        cout << "Enter Category (Fiction/Non-fiction): ";
        cin >> category;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        toLowerCase(category);

        if (!isValidCategory(category)) {
            cout << "Invalid category!" << endl;
            return;
        }

        displayHeader();
        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getCategory(), category) == 0) {
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
        displayHeader();
        for (int i = 0; i < bookCount; i++) {
            books[i].displayBook();
        }
    }

    int getMenuChoice() {
        int choice;
        while (true) {
            cout << "\nLibrary Management System" << endl;
            cout << "1 - Add Book" << endl;
            cout << "2 - Edit Book" << endl;
            cout << "3 - Search Book" << endl;
            cout << "4 - Delete Book" << endl;
            cout << "5 - View Books by Category" << endl;
            cout << "6 - View All Books" << endl;
            cout << "7 - Exit" << endl;
            cout << "Enter choice: ";

            string input;
            getline(cin, input);

            // Check for empty input
            if (input.empty()) {
                cout << "Invalid input! Please enter a single-digit integer between 1 and 7." << endl;
                continue;
            }

            if (input.length() == 1 && isdigit(input[0])) {
                choice = input[0] - '0';
                if (choice >= 1 && choice <= 7) {
                    return choice;
                }
            }
            
            cout << "Invalid input! Please enter a single-digit integer between 1 and 7." << endl;
        }
    }
};

int main() {
    Library library;
    bool running = true;
    while (running) {
        int choice = library.getMenuChoice();

        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.editBook(); break;
            case 3: library.searchBook(); break;
            case 4: library.deleteBook(); break;
            case 5: library.viewBooksByCategory(); break;
            case 6: library.viewAllBooks(); break;
            case 7: running = false; break;
            default: cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}