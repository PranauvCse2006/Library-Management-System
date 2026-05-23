#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Book
{
public:
    int id;
    string title;
    string author;
    bool issued;
};

vector<Book> books;

void saveToFile(){
    ofstream file("books.txt");
    for(Book b: books)
    {
        file << b.id << endl;
        file << b.title << endl;
        file << b.author << endl;
        file << b.issued << endl;
    }
    file.close();
}

void loadFromFile()
{
    ifstream file("books.txt");

    Book b;

    while(file >>b.id)
    {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);

        file >>b.issued;
        file.ignore();
        books.push_back(b);
    }
    file.close();
}


void addBook()
{
    Book b;

    cout << "\nEnter Book ID: ";
    cin >> b.id;

    cin.ignore();

    cout << "Enter the title of the book: ";
    getline(cin, b.title);

    cout << "Enter the author's name: ";
    getline(cin, b.author);

    b.issued = false;

    books.push_back(b);

    saveToFile();

    cout << "\nBook added successfully!\n";
}

void displayBooks()
{
    if (books.empty())
    {
        cout << "\nNo books available.\n";
        return;
    }

    cout << "\n===== BOOK LIST =====\n";

    for (Book b : books)
    {
        cout << "\nBook ID : " << b.id << endl;
        cout << "Title   : " << b.title << endl;
        cout << "Author  : " << b.author << endl;

        if (b.issued)
        {
            cout << "Status  : Issued\n";
        }
        else
        {
            cout << "Status  : Available\n";
        }
    }
}
void searchBook(){
    string searchTitle;
    cin.ignore();
    cout<<"\nEnter book title to search: ";
    getline(cin,searchTitle);
    bool found=false;
    for(Book b: books){
        if(b.title == searchTitle)
        {
            cout<<"\n===== BOOK FOUND =====\n";
            cout<<"Book ID : "<<b.id<<endl;
            cout<<"Title   : "<<b.title<<endl;
            cout<<"Author  : "<<b.author<<endl;
            if(b.issued){
                cout <<"Status :Issued\n";
            }else{
                cout<<"Status : Available\n";
            }
            found=true;
        }
    }
    if(!found){
        cout<<"\nBook not found.\n";
    }
}
void issueBook(){
    int bookId;
    cout<<"\n Enter Book ID to issue: ";
    cin>>bookId;
    bool found =false;
    for(Book &b : books){
        if(b.id==bookId)
        {
            if(b.issued)
            {
                cout<<"\nBook is already issued.\n";
            }
            else{
                b.issued=true;
                saveToFile();
                cout<<"\nBook issued successfully\n";
            }

            found=true;
        }
    }
    if(!found){
        cout<<"\nBook not found.\n";
    }
}
void returnBook()
{
    int bookId;
    cout<<"\nEnter Book ID to return: ";
    cin>>bookId;
    bool found =false;
    for(Book &b: books)
    {
        if(b.id==bookId){
            if(!b.issued)
            {
                cout<<"\nBook is alredy available.\n";
            }
            else{
                b.issued=false;
                saveToFile();
                cout<<"\nBook is returned sucessfully .\n";
            }
            found=true;
        }
    }
    if(!found)
        {
            cout<<"Book not found.\n";
        }

}


int main()
{
    int choice;
    
    loadFromFile();

    while (true)
    {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";


        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;
        
        case 3:
            searchBook();
            break;
        
        case 4:
            issueBook();
            break;
        
        case 5:
            returnBook();
            break;

        case 6:
            cout << "\nExiting the program. Goodbye!\n";
            return 0;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}