#ifndef BIGHW_MENUAUTH_H
#define BIGHW_MENUAUTH_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "calcHash.h"

#define BUFFMAX 100
#define USERS_FILE "../source_files/users.csv"
#define BOOKS_FILE "../source_files/books.csv"
#define STUDENTS_FILE "../source_files/students.csv"
#define BORROWS_FILE "../source_files/student_books.csv"
#define LOGS_FILE "../source_files/library.log"

typedef struct user {
    char *login;
    char *passHash;
    bool studentsRights;
    bool booksRights;
} User_t;

typedef struct userDB {
    int usersNumber;
    User_t *usersDatabase;
} DBUser_t;

/////////////////////////

typedef struct book {
    int ISBN;
    int maxAmount;
    int currAmount;
    char *author;
    char *bookName;
} Book_t;

typedef struct bookDB {
    int booksNumber;
    Book_t *booksDatabase;
} DBBook_t;

/////////////////////////

typedef struct student {
    char *cardNumber;
    char *firstName;
    char *surName;
    char *faculty;
    char *speciality;
} Student_t;

typedef struct studentDB {
    int studentsNumber;
    Student_t *studentsDatabase;
} DBStudent_t;

/////////////////////////

typedef struct borrow {
    int ISBN;
    char *cardNumber;
    char *returnTime;
} Borrow_t;

typedef struct borrowDB {
    int borrowsNumber;
    Borrow_t *borrowsDatabase;
} DBBorrow_t;

/////////////////////////

typedef struct adminDB {
    DBBook_t book_db;
    DBStudent_t student_db;
    DBBorrow_t borrow_db;
} DBAdmin_t;

/////////////////////////

typedef struct authData {
    char inputLogin[BUFFMAX];
    char inputPassword[BUFFMAX];
} AuthData_t;

enum bossChoice {
    users,
    books,
    students,
    borrows
};

enum reg_log {
    sign_up = 1,
    log_in
};

int launcher();
void exitMenu(DBAdmin_t *allDatabases, DBUser_t *user_db, char *admin);

#endif //BIGHW_MENUAUTH_H
