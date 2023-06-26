#ifndef BIGHW_BOOKSPROCESSING_H
#define BIGHW_BOOKSPROCESSING_H

#include "menuFile.h"


enum bookActions {
    finish_b,
    rtrn_b,
    add_b,
    del_b,
    edit_b,
    oneBook_b,
    allBooks_b,
    give_b,
    take_b,
    borrowers_b
};

enum editBookChoice {
    author = 1,
    book_name,
    max_amount,
};


void addBook(DBBook_t *books_db, char *admin);
void deleteBook(DBAdmin_t *allDatabases, char *admin);
void editBookInfo(DBBook_t *books_db, char *admin);
void showOneBook(DBBook_t *books_db, char *admin);
void showAllBooks(DBBook_t *books_db, char *admin);
void giveBook(DBAdmin_t *allDatabases, char *admin);
void takeBook(DBAdmin_t *allDatabases, char *admin);
void showLoaners(DBAdmin_t *allDatabases, char *admin);


#endif //BIGHW_BOOKSPROCESSING_H
