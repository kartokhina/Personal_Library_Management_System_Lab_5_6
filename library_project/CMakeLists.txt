<<<<<<< HEAD
cmake_minimum_required(VERSION 3.10)
project(LibraryManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(library 
    src/main.cpp
    src/Book.cpp
    src/Library.cpp
    src/User.cpp
)

include_directories(src)
=======
cmake_minimum_required(VERSION 3.10)
project(LibraryManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(library 
    src/main.cpp
    src/Book.cpp
    src/Library.cpp
    src/User.cpp
)

include_directories(src)
>>>>>>> 8826c6b4c8089d55566704f1e82d1408834cbbe7
