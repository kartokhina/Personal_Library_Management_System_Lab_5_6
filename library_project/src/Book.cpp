#include "Book.h"

#include <iostream>
#include <stdexcept>

Book::Book(const std::string& title, const std::string& author, int year, const std::string& isbn): title(title), author(author), year(year), isbn(isbn), 
      isAvailable(true), borrowedBy(""){
        if (year < 1450 || year > 2025){
            throw std::invalid_argument("Некорректный год.");
        }
        if (isbn.empty()){
            throw std::invalid_argument("ISBN не может быть пустым");
        }
} 

std::string Book::getTitle() const {return title;}
std::string Book::getAuthor() const {return author;}
int Book::getYear() const {return year;}
std::string Book::getISBN() const {return isbn;}
bool Book::getIsAvailable() const {return isAvailable;}
std::string Book::getBorrowedBy() const {return borrowedBy;}


void Book::borrowBook(const std::string& userName){
    if (!isAvailable){
        throw std::logic_error("Книга уже выдана.");
    }
    isAvailable = false;
    borrowedBy = userName;
}
void Book::returnBook(){
    if (isAvailable){
        throw std::logic_error("Книга уже есть в библиотеке.");
    }
    isAvailable = true;
    borrowedBy = "";
}
void Book::displayInfo(){
    std::cout << "Книга\n";
    std::cout << "Название: " << title << "\n";
    std::cout << "Автор: " << author << "\n";
    std::cout << "Год издания: " << year << "\n";
    std::cout << "ISBN: " << isbn << "\n";
    std::cout << "Статус: " << (isAvailable ? "Доступна" : "Выдана " + borrowedBy) << "\n\n";
}