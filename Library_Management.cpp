#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book
{
private:
    int bookID;
    char title[50];
    char author[50];
    bool issued;

public:
    void addBook()
    {
        cout << "Enter Book ID: ";
        cin >> bookID;

        cin.ignore();

        cout << "Enter Book Title: ";
        cin.getline(title, 50);

        cout << "Enter Author Name: ";
        cin.getline(author, 50);

        issued = false;
    }

    void displayBook() const
    {
        cout << "\nBook ID : " << bookID;
        cout << "\nTitle   : " << title;
        cout << "\nAuthor  : " << author;
        cout << "\nStatus  : " << (issued ? "Issued" : "Available") << endl;
    }

    int getBookID() const
    {
        return bookID;
    }

    const char* getTitle() const
    {
        return title;
    }

    const char* getAuthor() const
    {
        return author;
    }

    void issueBook()
    {
        issued = true;
    }

    void returnBook()
    {
        issued = false;
    }

    bool isIssued() const
    {
        return issued;
    }
};

// Add Book
void addNewBook()
{
    Book book;

    ofstream file("library.dat", ios::binary | ios::app);

    book.addBook();

    file.write(reinterpret_cast<char*>(&book), sizeof(book));

    file.close();

    cout << "\nBook Added Successfully!\n";
}

// Display Books
void displayBooks()
{
    Book book;

    ifstream file("library.dat", ios::binary);

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book)))
    {
        book.displayBook();
    }

    file.close();
}

// Search by Title
void searchByTitle()
{
    Book book;
    char search[50];
    bool found = false;

    cin.ignore();
    cout << "Enter Book Title: ";
    cin.getline(search,50);

    ifstream file("library.dat", ios::binary);

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book)))
    {
        if(strcmp(book.getTitle(), search)==0)
        {
            book.displayBook();
            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "\nBook Not Found!\n";
}

// Search by Author
void searchByAuthor()
{
    Book book;
    char search[50];
    bool found = false;

    cin.ignore();
    cout << "Enter Author Name: ";
    cin.getline(search,50);

    ifstream file("library.dat", ios::binary);

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book)))
    {
        if(strcmp(book.getAuthor(), search)==0)
        {
            book.displayBook();
            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "\nBook Not Found!\n";
}

// Issue Book
void issueBook()
{
    int id;
    Book book;

    cout << "Enter Book ID: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book)))
    {
        if(book.getBookID()==id)
        {
            if(book.isIssued())
            {
                cout << "\nBook Already Issued!\n";
                file.close();
                return;
            }

            book.issueBook();

            int pos = file.tellg();
            file.seekp(pos-sizeof(book));

            file.write(reinterpret_cast<char*>(&book), sizeof(book));

            cout << "\nBook Issued Successfully!\n";
            file.close();
            return;
        }
    }

    cout << "\nBook Not Found!\n";
    file.close();
}

// Return Book
void returnBook()
{
    int id;
    Book book;

    cout << "Enter Book ID: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book)))
    {
        if(book.getBookID()==id)
        {
            if(!book.isIssued())
            {
                cout << "\nBook is Already Available!\n";
                file.close();
                return;
            }

            book.returnBook();

            int pos = file.tellg();
            file.seekp(pos-sizeof(book));

            file.write(reinterpret_cast<char*>(&book), sizeof(book));

            cout << "\nBook Returned Successfully!\n";
            file.close();
            return;
        }
    }

    cout << "\nBook Not Found!\n";
    file.close();
}

int main()
{
    int choice;

    do
    {
        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search by Title\n";
        cout << "4. Search by Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            addNewBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchByTitle();
            break;

        case 4:
            searchByAuthor();
            break;

        case 5:
            issueBook();
            break;

        case 6:
            returnBook();
            break;

        case 7:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    }while(choice!=7);

    return 0;
}
