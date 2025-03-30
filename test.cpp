#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdio>

using namespace std;

#define MAX_BOOKS 100
#define MAX_LENGTH 100

#ifndef _WIN32
#include <strings.h> // for strcasecmp
#else
// Windows equivalent of strcasecmp
int strcasecmp(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        int diff = tolower(*s1) - tolower(*s2);
        if (diff != 0) return diff;
        s1++;
        s2++;
    }
    return tolower(*s1) - tolower(*s2);
}
#endif

class Book {
private:
    char id[MAX_LENGTH];
    char isbn[MAX_LENGTH];
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    char edition[MAX_LENGTH];
    char publication[MAX_LENGTH];
    char category[MAX_LENGTH];

public:
    void setBook(const char* id, const char* isbn, const char* title,
                const char* author, const char* edition,
                const char* publication, const char* category) {
        strncpy(this->id, id, MAX_LENGTH);
        strncpy(this->isbn, isbn, MAX_LENGTH);
        strncpy(this->title, title, MAX_LENGTH);
        strncpy(this->author, author, MAX_LENGTH);
        strncpy(this->edition, edition, MAX_LENGTH);
        strncpy(this->publication, publication, MAX_LENGTH);
        strncpy(this->category, category, MAX_LENGTH);
    }

    const char* getId() const { return id; }
    const char* getIsbn() const { return isbn; }
    const char* getTitle() const { return title; }
    const char* getAuthor() const { return author; }
    const char* getEdition() const { return edition; }
    const char* getPublication() const { return publication; }
    const char* getCategory() const { return category; }

    void displayBook() const {
        printf("| %-8s | %-13s | %-20s | %-20s | %-8s | %-15s | %-11s |\n",
               id, isbn, title, author, edition, publication, category);
    }

    void editBook(const char* isbn, const char* title, const char* author,
                 const char* edition, const char* publication, const char* category) {
        if (isbn[0] != '\0') strncpy(this->isbn, isbn, MAX_LENGTH);
        if (title[0] != '\0') strncpy(this->title, title, MAX_LENGTH);
        if (author[0] != '\0') strncpy(this->author, author, MAX_LENGTH);
        if (edition[0] != '\0') strncpy(this->edition, edition, MAX_LENGTH);
        if (publication[0] != '\0') strncpy(this->publication, publication, MAX_LENGTH);
        if (category[0] != '\0') strncpy(this->category, category, MAX_LENGTH);
    }
};

class Library {
private:
    Book books[MAX_BOOKS];
    int count;

    void displayHeader() const {
        cout << "+----------+---------------+---------------+----------------------+----------+-----------------+-------------+\n";
        cout << "| ID       | ISBN          | Title         | Author               | Edition  | Publication     | Category    |\n";
        cout << "+----------+---------------+---------------+----------------------+----------+-----------------+-------------+\n";
    }

    void displayFooter() const {
        cout << "+----------+---------------+---------------+----------------------+----------+-----------------+-------------+\n";
    }

    bool isDuplicateId(const char* id) const {
        for (int i = 0; i < count; i++) {
            if (strcasecmp(books[i].getId(), id) == 0) return true;
        }
        return false;
    }

    bool isValidId(const char* id) const {
        for (int i = 0; id[i] != '\0'; i++) {
            if (!isalnum(id[i])) return false;
        }
        return true;
    }

    int findBookById(const char* id) const {
        for (int i = 0; i < count; i++) {
            if (strcasecmp(books[i].getId(), id) == 0) return i;
        }
        return -1;
    }

    void toLowerCase(char* str) const {
        for (int i = 0; str[i]; i++) {
            str[i] = tolower(str[i]);
        }
    }

    bool validateCategory(const char* input, char* output) const {
        char temp[MAX_LENGTH];
        strncpy(temp, input, MAX_LENGTH);
        toLowerCase(temp);

        if (strcmp(temp, "fiction") == 0) {
            strncpy(output, "Fiction", MAX_LENGTH);
            return true;
        }
        if (strcmp(temp, "non-fiction") == 0) {
            strncpy(output, "Non-fiction", MAX_LENGTH);
            return true;
        }
        return false;
    }

    void getInput(const char* prompt, char* buffer, bool required = true) {
        do {
            cout << prompt;
            cin.getline(buffer, MAX_LENGTH);
            if (required && buffer[0] == '\0') {
                cout << "This field is required!\n";
            } else {
                break;
            }
        } while (true);
    }

    void getInputWithDefault(const char* defaultText, const char* fieldName, char* buffer) {
        char prompt[MAX_LENGTH * 2];
        snprintf(prompt, sizeof(prompt), "%s [%s]: ", fieldName, defaultText);
        getInput(prompt, buffer, false);
    }

    bool containsCaseInsensitive(const char* haystack, const char* needle) const {
        if (!haystack || !needle) return false;
        
        while (*haystack) {
            const char* h = haystack;
            const char* n = needle;
            
            while (*h && *n && tolower(*h) == tolower(*n)) {
                h++;
                n++;
            }
            
            if (*n == '\0') return true;
            haystack++;
        }
        return false;
    }

public:
    Library() : count(0) {}

    void addBook() {
        if (count >= MAX_BOOKS) {
            cout << "Library is full!\n";
            return;
        }

        char id[MAX_LENGTH], isbn[MAX_LENGTH], title[MAX_LENGTH];
        char author[MAX_LENGTH], edition[MAX_LENGTH], publication[MAX_LENGTH];
        char category[MAX_LENGTH];

        // Get category with validation
        do {
            getInput("Enter Category (Fiction/Non-fiction): ", category);
            if (validateCategory(category, category)) break;
            cout << "Invalid category! Must be 'Fiction' or 'Non-fiction' (with hyphen).\n";
        } while (true);

        // Get ID with validation
        do {
            getInput("Enter Book ID (alphanumeric): ", id);
            if (!isValidId(id)) {
                cout << "Invalid ID! Only letters and numbers allowed.\n";
            } else if (isDuplicateId(id)) {
                cout << "ID already exists!\n";
            } else {
                break;
            }
        } while (true);

        // Get other fields
        getInput("Enter ISBN: ", isbn);
        getInput("Enter Title: ", title);
        getInput("Enter Author: ", author);
        getInput("Enter Edition: ", edition);
        getInput("Enter Publication: ", publication);

        books[count++].setBook(id, isbn, title, author, edition, publication, category);
        cout << "\nBook added successfully!\n";
    }

    void editBook() {
        if (count == 0) {
            cout << "No books to edit.\n";
            return;
        }

        char id[MAX_LENGTH];
        getInput("Enter Book ID to edit: ", id);

        int index = findBookById(id);
        if (index == -1) {
            cout << "Book not found!\n";
            return;
        }

        cout << "\nCurrent Book Details:\n";
        displayHeader();
        books[index].displayBook();
        displayFooter();

        cout << "\nLeave field blank to keep current value:\n";

        char isbn[MAX_LENGTH], title[MAX_LENGTH], author[MAX_LENGTH];
        char edition[MAX_LENGTH], publication[MAX_LENGTH], category[MAX_LENGTH];

        getInputWithDefault(books[index].getIsbn(), "ISBN", isbn);
        getInputWithDefault(books[index].getTitle(), "Title", title);
        getInputWithDefault(books[index].getAuthor(), "Author", author);
        getInputWithDefault(books[index].getEdition(), "Edition", edition);
        getInputWithDefault(books[index].getPublication(), "Publication", publication);

        // Category with validation
        do {
            getInputWithDefault(books[index].getCategory(), "Category", category);
            if (category[0] == '\0' || validateCategory(category, category)) break;
            cout << "Invalid category! Must be 'Fiction' or 'Non-fiction' (with hyphen).\n";
        } while (true);

        books[index].editBook(
            isbn[0] != '\0' ? isbn : books[index].getIsbn(),
            title[0] != '\0' ? title : books[index].getTitle(),
            author[0] != '\0' ? author : books[index].getAuthor(),
            edition[0] != '\0' ? edition : books[index].getEdition(),
            publication[0] != '\0' ? publication : books[index].getPublication(),
            category[0] != '\0' ? category : books[index].getCategory()
        );

        cout << "\nBook updated successfully!\n";
    }

    void searchBook() {
        if (count == 0) {
            cout << "No books to search.\n";
            return;
        }

        cout << "\nSearch by:\n1. ID\n2. Title\n3. Author\nEnter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        char term[MAX_LENGTH];
        bool found = false;

        switch (choice) {
            case 1: {
                getInput("Enter Book ID to search: ", term);
                displayHeader();
                for (int i = 0; i < count; i++) {
                    if (strcasecmp(books[i].getId(), term) == 0) {
                        books[i].displayBook();
                        found = true;
                    }
                }
                if (!found) {
                    cout << "No book found with ID: '" << term << "'\n";
                }
                break;
            }
            case 2:
                getInput("Enter Title: ", term);
                displayHeader();
                for (int i = 0; i < count; i++) {
                    if (containsCaseInsensitive(books[i].getTitle(), term)) {
                        books[i].displayBook();
                        found = true;
                    }
                }
                break;
            case 3:
                getInput("Enter Author: ", term);
                displayHeader();
                for (int i = 0; i < count; i++) {
                    if (containsCaseInsensitive(books[i].getAuthor(), term)) {
                        books[i].displayBook();
                        found = true;
                    }
                }
                break;
            default:
                cout << "Invalid choice!\n";
                return;
        }

        displayFooter();
        if (!found) cout << "No books found.\n";
    }

    void deleteBook() {
        if (count == 0) {
            cout << "No books to delete.\n";
            return;
        }

        char id[MAX_LENGTH];
        getInput("Enter Book ID to delete: ", id);

        int index = findBookById(id);
        if (index == -1) {
            cout << "Book not found!\n";
            return;
        }

        cout << "\nBook to delete:\n";
        displayHeader();
        books[index].displayBook();
        displayFooter();

        char confirm[MAX_LENGTH];
        do {
            cout << "Confirm deletion (y/n)? ";
            cin.getline(confirm, MAX_LENGTH);
            
            if (strlen(confirm) == 1 && (tolower(confirm[0]) == 'y' || tolower(confirm[0]) == 'n')) {
                break;
            }
            cout << "Invalid input! Please enter only 'y' or 'n'.\n";
        } while (true);

        if (tolower(confirm[0]) == 'y') {
            // Shift all books down
            for (int i = index; i < count - 1; i++) {
                books[i] = books[i + 1];
            }
            count--;
            cout << "Book deleted successfully!\n";
        } else {
            cout << "Deletion cancelled.\n";
        }
    }

    void viewByCategory() {
        if (count == 0) {
            cout << "No books to display.\n";
            return;
        }

        char category[MAX_LENGTH];
        do {
            getInput("Enter Category (Fiction/Non-fiction): ", category);
            char temp[MAX_LENGTH];
            if (validateCategory(category, temp)) {
                displayHeader();
                for (int i = 0; i < count; i++) {
                    if (strcmp(books[i].getCategory(), temp) == 0) {
                        books[i].displayBook();
                    }
                }
                displayFooter();
                break;
            }
            cout << "Invalid category! Must be 'Fiction' or 'Non-fiction' (with hyphen).\n";
        } while (true);
    }

    void viewAllBooks() {
        if (count == 0) {
            cout << "No books to display.\n";
            return;
        }

        cout << "\nAll Books (" << count << "):\n";
        displayHeader();
        for (int i = 0; i < count; i++) {
            books[i].displayBook();
        }
        displayFooter();
    }

    void menu() {
        while (true) {
            cout << "\nLibrary Management System\n";
            cout << "1. Add Book\n2. Edit Book\n3. Search Book\n";
            cout << "4. Delete Book\n5. View by Category\n6. View All Books\n7. Exit\n";
            cout << "Enter choice: ";

            char choiceStr[MAX_LENGTH];
            cin.getline(choiceStr, MAX_LENGTH);

            if (strlen(choiceStr) != 1 || !isdigit(choiceStr[0])) {
                cout << "Invalid input! Please enter 1-7.\n";
                continue;
            }

            int choice = choiceStr[0] - '0';

            switch (choice) {
                case 1: addBook(); break;
                case 2: editBook(); break;
                case 3: searchBook(); break;
                case 4: deleteBook(); break;
                case 5: viewByCategory(); break;
                case 6: viewAllBooks(); break;
                case 7: cout << "Exiting...\n"; return;
                default: cout << "Invalid choice! Please enter 1-7.\n";
            }
        }
    }
};

int main() {
    Library library;
    library.menu();
    return 0;
}