#include "Library.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>



Library::Library(const std::string& dataFilePath): dataFile(dataFilePath){
    loadFromFile();
 }


void Library::addBook(const Book& book){

    if (findBookByISBN(book.getISBN()) != nullptr){
        throw std::logic_error("Книга с таким ISBN уже существует.");
    }
    books.push_back(book);
}

void Library::addUser(const User& user){
    if (findUserByName(user.getName()) != nullptr){
        throw std::logic_error("Такой пользователь уже существует.");
    }
    users.push_back(user);
}

void Library::borrowBook(const std::string& userName, const std::string& isbn){
    User* user = findUserByName(userName);
    Book* book = findBookByISBN(isbn);
    if (!book) throw std::logic_error("Книга не найдена.");
    if (!user) throw std::logic_error("Пользователь не найден.");
    
    book->borrowBook(userName);
    user->addBook(isbn);
}   

void Library::returnBook(const std::string& isbn){
    Book* book = findBookByISBN(isbn);
    if (!book) throw std::logic_error("Книга не найдена.");
    
    std::string userName = book->getBorrowedBy();
    User* user = findUserByName(userName);

    book->returnBook();
    user->removeBook(isbn);

}

Book* Library::findBookByISBN(const std::string& isbn){
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            return &book;
        }
    }
    return nullptr;
}

User* Library::findUserByName(const std::string& name){
    for (auto& user : users) {
        if (user.getName() == name) {
            return &user;
        }
    }
    return nullptr;
}
void Library::displayAllBooks(){
    if (books.empty()){
        std::cout << "Библиотека пуста.\n";
        return;
    }
    
    std::cout << "Каталог книг:\n";
    for (auto& book : books) {
            book.displayInfo();
    }
}
void Library::displayAllUsers(){
    if (users.empty()) {
            std::cout << "Нет зарегистрированных пользователей.\n";
            return;
        }
        std::cout << "=== ПОЛЬЗОВАТЕЛИ ===\n";
        for (auto& user : users) {
            user.displayProfile();
        }
}
void Library::saveToFile() {

    std::ofstream file(dataFile);
    if (!file.is_open()) {
        throw std::logic_error("Не удалось открыть файл.");
    }
    for (const auto& book : books) {
        file << "BOOK\n";
        file << "Title: " << book.getTitle() << "\n";
        file << "Author: " << book.getAuthor() << "\n";
        file << "Year: " << book.getYear() << "\n";
        file << "ISBN: " << book.getISBN() << "\n";
        file << "Available: " << (book.getIsAvailable() ? "yes" : "no") << "\n";
        file << "BorrowedBy: " << book.getBorrowedBy() << "\n\n";
    }

    file << "---USERS---\n\n";
    for (const auto& user : users) {
        file << "USER\n";
        file << "Name: " << user.getName() << "\n";
        file << "UserID: " << user.getUserId() << "\n";
        
        std::vector<std::string> borrowed = user.getBorrowedBooks();
        file << "BorrowedBooks: ";
        for (size_t i = 0; i < borrowed.size(); ++i) {
            file << borrowed[i];
            if (i < borrowed.size() - 1) file << "|";
        }
        file << "\n";
        file << "MaxBooks: " << user.getMaxBooksAllowed() << "\n\n";
    }
    file.close();
    std::cout << "Данные сохранены в файл: " << dataFile << "\n";

}

void Library::loadFromFile(){
    //input file stream (поток ввода из файла)
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        std::cout << "Файл данных не найден.\n";

        std::ofstream createFile(dataFile);
        if (createFile.is_open()) {
            std::cout << "Файл успешно создан: " << dataFile << std::endl;
            createFile.close();}
        return;
    }

    std::string line;
    bool readingBooks = true;
    while(std::getline(file, line)){
        if (line == "---USERS---"){
            readingBooks = false;
            continue;
        }
        if(readingBooks && line == "BOOK"){
            std::string  title, author, isbn, borrowedBy;
            int year = 0;
            bool available = true;

            while (std::getline(file, line) && !line.empty()){
                if (line.find("Title: ") == 0){
                    title = line.substr(7);
                }else if (line.find("Author: ") == 0) {
                    author = line.substr(8);
                } else if (line.find("Year: ") == 0) {
                    year = std::stoi(line.substr(6));
                } else if (line.find("ISBN: ") == 0) {
                    isbn = line.substr(6);
                } else if (line.find("Available: ") == 0) {
                    available = (line.substr(11) == "yes");
                } else if (line.find("BorrowedBy: ") == 0) {
                    borrowedBy = line.substr(12);
                }
            }

            if (!title.empty() && !author.empty() && year != 0 && !isbn.empty()){
                Book book(title, author, year, isbn);
                if (!available){
                    book.borrowBook(borrowedBy);
                }
                books.push_back(book);
            }
        }
            
            /////////
            if (!readingBooks && line == "USER") {
                std::string name, userId;
                std::vector<std::string> borrowedBooks;
                int maxBooks = 3;

                while (std::getline(file, line) && !line.empty()) {
                    if (line.find("Name: ") == 0) {
                        name = line.substr(6);
                    } else if (line.find("UserID: ") == 0) {
                         userId = line.substr(8);
                    } else if (line.find("BorrowedBooks: ") == 0) {
                        std::string booksStr = line.substr(15);
                        if (!booksStr.empty()) {
                            //поток из строки. ss будет читать данные из строки booksStr 
                            std::stringstream ss(booksStr);
                            std::string isbn;

                            while (std::getline(ss, isbn, '|')){
                                borrowedBooks.push_back(isbn);
                            }

                        }
                    } else if(line.find("MaxBooks: ") == 0) {
                        maxBooks = std::stoi(line.substr(10));
                    }

                }
                if (!name.empty() && !userId.empty()){
                    User user(name, userId, maxBooks);

                    for(auto& isbn: borrowedBooks){
                        try{
                            user.addBook(isbn);
                        } catch(...) {}
                    }
                    users.push_back(user);

                }


            }

    }
    file.close();
}
