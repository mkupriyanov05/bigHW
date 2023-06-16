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
    curr_amount
};


void addBook(DBBook_t *books_db);
void deleteBook(DBAdmin_t *allDatabases);
void rewriteBooksFile(DBBook_t books_db);
void editBookInfo(DBBook_t *books_db);
void showOneBook(DBBook_t *books_db);
void showAllBooks(DBBook_t *books_db);
void giveBook(DBAdmin_t *allDatabases);
void takeBook(DBAdmin_t *allDatabases);
void showLoaners(DBAdmin_t *allDatabases);


#endif //BIGHW_BOOKSPROCESSING_H
