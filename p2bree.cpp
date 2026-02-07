#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::getline;
using std::transform;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::ios;

struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;
};

void SortMenu       (Book books[], int count);
void SortByTitle    (Book books[], int count);
void SortByAuthor   (Book books[], int count);
void Update         (Book books[], int &count);
void Delete         (Book books[], int &count);
void Search         (Book books[], int count);
void LoadBooks      (Book books[], int &count);
void Show           (Book books[], int count);
void Add            (Book books[], int &count);
void BorrowBook     (Book books[], int count);
void ReturnBook     (Book books[], int count);
void Check          (int &x);

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


int main(){
    int option;
    int count = 0;
    Book books[500];

    LoadBooks(books, count);

    do {
        cout << CYAN;
        cout << "=====================================\n";
        cout << "        LIBRARY MANAGEMENT SYSTEM     \n";
        cout << "=====================================\n";
        cout << RESET;

        cout << GREEN   << " [1] " << WHITE << "Add Book\n";
        cout << YELLOW  << " [2] " << WHITE << "Update Book\n";
        cout << RED     << " [3] " << WHITE << "Delete Book\n\n";

        cout << MAGENTA << " [4] " << WHITE << "List Books\n";
        cout << CYAN    << " [5] " << WHITE << "Search Book\n\n";

        cout << BLUE    << " [6] " << WHITE << "Sort Books\n";
        cout << GREEN   << " [7] " << WHITE << "Borrow / Return Book\n\n";

        cout << RED     << " [0] Exit\n";
        cout << RESET;

        cout << CYAN << "-------------------------------------\n" << RESET;
        cout << YELLOW << "Choose an option: " << RESET;
        cin >> option;

        switch (option) {
            case 1: Add(books, count); break;
            case 2: Update(books, count); break;
            case 3: Delete(books, count); break;
            case 4: Show(books, count); break;
            case 5: Search(books, count); break;
            case 6: SortMenu(books, count); break;
            case 7: {
                int br;
                cout << CYAN << "\n[1] Borrow Book" << MAGENTA << "\n[2] Return Book" << RED << "\n[0] Back" << RESET << "\nChoose: ";
                cin >> br;
                if (br == 1) BorrowBook(books, count);
                else if (br == 2) ReturnBook(books, count);
                break;
            }
            default:
                break;
        }

    }while (option != 0);

    return 0;
}
void Add(Book books[], int &count){
    string available;
    bool exists;
    int num;
    int howmany;
    cout << GREEN << "How many books do you want to add: ";
    Check(howmany);

    ofstream file("books.txt", ios::app); 

    if(howmany + count >= 100){
        cout << RED << "You cant add this much books\n";
        return;
    }
    else{
        for(int i = 0; i < howmany; i++){
            do{
                exists = false;
                num = rand() % 500 + 1;
                for(int j = 0; j < count; j++){
                    if(books[j].id == num){
                        exists = true;
                        break;
                    }
                }
            }while(exists);
            books[count].id = num;

            cout << GREEN << "What is the title of the book number " << i + 1 << ": \n";
            getline(cin, books[count].title);

            cout << GREEN << "Who is the author of the book number " << i + 1 << ": \n";
            getline(cin, books[count].author);

            cout << GREEN << "Is the book number " << i + 1 << " available (write available or not available): ";
            getline(cin, available);

            transform(available.begin(), available.end(), available.begin(), ::tolower);

            if(available == "available"){
                books[count].isAvailable = true;
                }
            else if(available == "not available"){
                books[count].isAvailable = false;
                }
            else{
                cout << RED << "Please write available or not available\n";
                cout << RESET;
                return;
                }

        file << books[count].id << "|"
             << books[count].title << "|"
             << books[count].author << "|"
             << books[count].isAvailable << endl;

        count ++;
            }
        }
    file.close();
    cout << "\nBooks added successfully.\n";
}
void Show(Book books[], int count){

    string availablecheck;

    for(int i = 0; i < count; i++){

        if(books[i].isAvailable){
            availablecheck = "available";
        }
        else{
            availablecheck = "not available";
        }
        cout << BLUE;
        cout << '\n' << "Book id is: " << books[i].id << '\n';
        cout << "The book title is: " << books[i].title << '\n';
        cout << "The book authors is: " << books[i].author << '\n';
        cout << "The book is " << availablecheck << '\n';
    }
}
void LoadBooks(Book books[],int &count){
    
    ifstream file("books.txt");
    if (!file) return;

    string title;
    string author;
    string id;
    string line;
    string isAvailable;
    bool available;

    while(getline(file, line)){
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, isAvailable);

        if(isAvailable == "1"){
            available = true;
        }
        else{
            available = false;
        }

        books[count].id = stoi(id);
        books[count].title = title;
        books[count].author = author;
        books[count].isAvailable = available;

        count ++;
        if(count >= 100){
            break;
        }
    }
    file.close();
}
void Search(Book books[], int count){
    string SearchTitle;
    int k = -1;
    string Check;

    cin.ignore();
    cout << CYAN << "Please enter the title: ";
    getline(cin, SearchTitle);

    for(int i = 0; i < count; i++){
        if(books[i].title == SearchTitle){
            k = i;
            break;
    }
    }
    
    if(k == -1){
        cout << RED << "We couldn't find the book!\n";
        cout << RESET;
        return;
    }
    else {
        if(books[k].isAvailable){
            Check = "available";
        }
        else{
            Check = "not available";
        }
        cout << '\n' << "Book's " << " id is: " << books[k].id << '\n';
        cout << "Book's " << " title is: " << books[k].title << '\n';
        cout << "Book's " << " author is: " << books[k].author << '\n';
        cout << "Book is " << Check << '\n';
    }
}
void Delete(Book books[], int &count){
    int SearchId;
    int k = -1;

    cout << RED << "Please enter the id: ";
    Check(SearchId);

    for(int i = 0; i < count; i++){
        if(books[i].id == SearchId){
            k = i;
            break;
        }
    }
    if(k == -1){
        cout << RED << "We couldn't find the book!\n";
        cout << RESET;
        return;
    }

    else{
        for(int i = k; i < count - 1; i++){
            books[i] = books[i + 1];
        }
        count--;

        ofstream file("books.txt", ios::out | ios::trunc);
            
        for(int i = 0; i < count; i++){
            file << books[i].id << "|"
                << books[i].title << "|"
                << books[i].author << "|"
                << books[i].isAvailable << endl;
            } 
        cout << GREEN << "The book deleted succesfully :D \n";
    }
}
void Update(Book books[], int &count){
    int SearchId;
    int k = -1;
    string available;

    cout << CYAN << "Please enter the id: ";
    Check(SearchId);

    for(int i = 0; i < count; i++){
        if(books[i].id == SearchId){
            k = i;
            break;
        }
    }
    if(k == -1){
        cout << RED << "We couldn't find the book!\n";
        cout << RESET;
        return;
    }


    else{
        cout << YELLOW << "Please write the name of book: \n";
        getline(cin, books[k].title);

        cout << "Who is the author of the book: \n";
        getline(cin, books[k].author);
        
        cout << "Is the book available (write available or not available): \n";
        getline(cin, available);
        transform(available.begin(), available.end(), available.begin(), ::tolower);

            if(available == "available"){
                books[k].isAvailable = true;
            }
            else if(available == "not available"){
                books[k].isAvailable = false;
            }
        
        ofstream file("books.txt", ios::out | ios::trunc );

        for(int i = 0; i < count; i++){
        file << books[i].id << "|"
             << books[i].title << "|"
             << books[i].author << "|"
             << books[i].isAvailable << endl;
        } 
        cout << GREEN << "Book updated succesfully :D \n";
    }
}    
void SortByAuthor(Book books[], int count){

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            string author1 = books[j].author;
            string author2 = books[j + 1].author;
            transform(author1.begin(), author1.end(), author1.begin(), ::tolower);
            transform(author2.begin(), author2.end(), author2.begin(), ::tolower);
            
            if (author1 > author2) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}
void SortByTitle(Book books[], int count){

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            string title1 = books[j].title;
            string title2 = books[j + 1].title;
            transform(title1.begin(), title1.end(), title1.begin(), ::tolower);
            transform(title2.begin(), title2.end(), title2.begin(), ::tolower);
            
            if (title1 > title2) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}
void SortMenu(Book books[], int count){
    int choice;
    cout << BLUE << "\nSORT BOOKS\n";
    cout << MAGENTA << "[1] Sort by Title (A-Z)\n";
    cout << CYAN << "[2] Sort by Author (A-Z)\n";
    cout << RED << "[0] Back\n";
    cout << YELLOW << "Choose: ";
    cin >> choice;

    switch (choice) {
        case 1: SortByTitle(books, count); break;
        case 2: SortByAuthor(books, count); break;
        default: break;
    }
    if(choice == 1 || choice == 2){
        cout << GREEN << "Sorting applied.\n" << RESET;
    }
    else{
        
    }
}
void BorrowBook(Book books[], int count){
    int SearchId;
    int k = -1;
    string Check;

    cout << CYAN << "Please enter the id: \n";
    cin >> SearchId;

    for(int i = 0; i < count; i++){
        if(books[i].id == SearchId){
            k = i;
            break;
    }
    }
    if(k == -1){
        cout << RED << "We couldn't find the book!\n";
        cout << RESET;
        return;
    }
    else{
    if(books[k].isAvailable){
        cout << GREEN << "You borrowed the book now! \n";
        cout << RESET;
        books[k].isAvailable = false;
        ofstream file("books.txt", ios::out | ios::trunc );

        for(int i = 0; i < count; i++){
        file << books[i].id << "|"
             << books[i].title << "|"
             << books[i].author << "|"
             << books[i].isAvailable << endl;
        } 
    }
    else{
        cout << "The book is borrowed :( \n";
    }
}
}
void ReturnBook(Book books[], int count){
     int SearchId;
    int k = -1;
    string Check;

    cout << CYAN << "Please enter the id: \n";
    cin >> SearchId;

    for(int i = 0; i < count; i++){
        if(books[i].id == SearchId){
            k = i;
            break;
    }
    }
    if(k == -1){
        cout << RED << "We couldn't find the book!\n";
        cout << RESET;
        return;
    }
    else{
    if(books[k].isAvailable){
        cout << CYAN << "The book is already returned \n";
        cout << RESET;
    }
    else{
        cout << GREEN << "Thank you for returning the book :) \n";
        cout << RESET;
        books[k].isAvailable = true;
    
    ofstream file("books.txt", ios::out | ios::trunc );

        for(int i = 0; i < count; i++){
        file << books[i].id << "|"
             << books[i].title << "|"
             << books[i].author << "|"
             << books[i].isAvailable << endl;
        } 
    }
  }
}
void Check(int &x){
    while(true){
        cin >> x;
        
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << RED << "Invalid input! Please enter a number: ";
            cout << RESET;
        }
        else{
            cin.ignore(1000, '\n');
            break;
        }
    }
}