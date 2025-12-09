#include "User.h"

#include <iostream>
// для find
#include <algorithm>

User::User(const std::string &name, const std::string &userId, int maxBooks): name(name), userId(userId), maxBooksAllowed(maxBooks){}

std::string User::getName() const {return name;}
std::string User::getUserId() const {return userId;}
std::vector<std::string> User::getBorrowedBooks() const {return borrowedBooks;}
int User::getMaxBooksAllowed() const {return maxBooksAllowed;}


bool User::canBorrowMore(){
    // borrowedBooks.size() возвращает тип size_t
    return borrowedBooks.size() < static_cast<size_t>(maxBooksAllowed);
}
void User::addBook(const std::string& isbn){
    if (!canBorrowMore()){
        throw std::logic_error("Пользователь достиг лимита книг.");
    }
    if(std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn) != borrowedBooks.end()){
        throw std::invalid_argument("Книга уже добавлена.");
    }
    borrowedBooks.push_back(isbn);
}
void User::removeBook(const std::string& isbn){
    size_t index = 0;
    for(; index != borrowedBooks.size(); ++index){
        if (borrowedBooks[index] == isbn) {
            break;
        }
    }
    if (index == borrowedBooks.size()){
        throw std::invalid_argument("Книга не найдена.");

    }
    // erase принимает итератор
    borrowedBooks.erase(borrowedBooks.begin() + index);
}
void User::displayProfile(){
    std::cout << "Пользователь\n";
    std::cout << "Имя: " << name << "\n";
    std::cout << "ID: " << userId << "\n";
    std::cout << "Максимум книг, которые может взять пользователь: " << maxBooksAllowed << "\n";
    
    std::cout << "Взято книг: " << borrowedBooks.size() 
              << " из " << maxBooksAllowed << "\n";
    
    if (!borrowedBooks.empty()) {
        std::cout << "Список взятых книг:\n";
        for(size_t i = 0; i < borrowedBooks.size(); ++i) {
            std::cout << i << ". " << borrowedBooks[i] << "\n";
        }
    } else {
        std::cout << "Нет взятых книг\n";
    }
}
