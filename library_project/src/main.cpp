

#ifdef _WIN32
#include <windows.h>
#endif

#include "Library.h"
#include <iostream>
#include <limits>  



void displayMenu() {
    std::cout << "\n=== БИБЛИОТЕКА ===\n";
    std::cout << "1. Просмотреть все книги\n";
    std::cout << "2. Просмотреть всех пользователей\n";
    std::cout << "3. Добавить новую книгу\n";
    std::cout << "4. Зарегистрировать пользователя\n";
    std::cout << "5. Выдать книгу пользователю\n";
    std::cout << "6. Принять книгу от пользователя\n";
    std::cout << "7. Поиск книги по ISBN\n";
    std::cout << "8. Просмотреть профиль пользователя\n";
    std::cout << "9. Сохранить данные в файл\n";
    std::cout << "10. Выход\n";
    std::cout << "Ваш выбор: ";
}


int main() {
    
    //кодировки для Windows
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif



    Library library;

    while (true) {
            std::cout << "\n=== БИБЛИОТЕКА ===\n";
            std::cout << "1. Просмотреть все книги\n";
            std::cout << "2. Просмотреть всех пользователей\n";
            std::cout << "3. Добавить новую книгу\n";
            std::cout << "4. Зарегистрировать пользователя\n";
            std::cout << "5. Выдать книгу пользователю\n";
            std::cout << "6. Принять книгу от пользователя\n";
            std::cout << "7. Поиск книги по ISBN\n";
            std::cout << "8. Просмотреть профиль пользователя\n";
            std::cout << "9. Сохранить данные в файл\n";
            std::cout << "10. Выход\n";
            std::cout << "Ваш выбор: ";


            int c;
            std::cin >> c;
          
            if (std::cin.fail()) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Ошибка ввода! Пожалуйста, введите число от " << 1 << " до " << 10 << ": ";
            continue;
            }
            std::cin.ignore();
            switch (c) {
                 case 1:
                    library.displayAllBooks();
                    break;
                
                case 2:
                    library.displayAllUsers();
                    break;
                case 3: {
                    std::string title, author, isbn;
                    int year;
                        
                    std::cout << "Название книги: ";
                    std::getline(std::cin, title);

                    std::cout << "Автор: ";
                    std::getline(std::cin, author);

                    std::cout << "Год издания: ";
                    std::cin >> year;
                    // от ввода года остается \n в буфере
                    std::cin.ignore();

                    std::cout << "ISBN: ";
                    std::getline(std::cin, isbn);
                    
                    try {
                        Book book(title, author, year, isbn);
                        library.addBook(book);
                        std::cout << "Книга добавлена!\n";
                    } catch (std::exception& e) {
                        std::cout << "Ошибка: " << e.what() << "\n";
                    }
                    break;
                }case 4: {
                std::string name, userId;
                
                std::cout << "Имя пользователя: ";
                std::getline(std::cin, name);

                std::cout << "ID пользователя: ";
                std::getline(std::cin, userId);
                 
                try {
                    User user(name, userId);
                    library.addUser(user);

                    std::cout << "Пользователь добавлен!\n";
                } catch (std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << "\n";
                }
                break;
                }case 5:{
                std::string userName, isbn;
                
                std::cout << "Имя пользователя: ";
                std::getline(std::cin, userName);

                std::cout << "ISBN книги: ";
                std::getline(std::cin, isbn);
                
                try {
                    library.borrowBook(userName, isbn);
                    std::cout << "Книга выдана!\n";
                } catch (std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << "\n";
                }
                break;
                }case 6: {
                std::string isbn;
                
                std::cout << "ISBN книги: ";
                std::getline(std::cin, isbn);
                
                try {
                    library.returnBook(isbn);
                    std::cout << "Книга возвращена!\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << "\n";
                }
                break;
                }case 7:{
                std::string isbn;
                std::cout << "Введите ISBN: ";
                std::getline(std::cin, isbn);
                
                Book* book = library.findBookByISBN(isbn);
                if (book) {
                    book->displayInfo();
                } else {
                    std::cout << "Книга не найдена\n";
                }
                break;
                }case 8:{
                std::string name;  
                std::cout << "Введите имя пользователя: ";
                std::getline(std::cin, name);
                
                User* user = library.findUserByName(name);
                if (user) {
                    user->displayProfile();
                } else {
                    std::cout << "Пользователь не найден\n";
                }
                break;
            }case 9:{
                try {
                    library.saveToFile();

                    std::cout << "Данные сохранены!\n";

                } catch (const std::exception& e) {
                    std::cout << "Ошибка сохранения: " << e.what() << "\n";
                }
                break; 
                
            }case 10:
                std::cout << "Выход из программы.\n";
                return 0;
            default:
                std::cout << "Неверный ввод! Введите число от 1 до 10.\n";
        }
    }
    
    return 0;
}