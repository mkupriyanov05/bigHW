#ifndef BIGHW_PARSEFREEREWRITE_H
#define BIGHW_PARSEFREEREWRITE_H

#include "menuAuth.h"

void parseFile(void **database, int *itemsNumber, char *filename, size_t structSize, int parseType);

void freeUsersDatabase(DBUser_t *users_db);
void freeBooksDatabase(DBBook_t *books_db);
void freeOneBook(Book_t *book);
void freeStudentsDatabase(DBStudent_t *students_db);
void freeOneStudent(Student_t *student);
void freeBorrowsDatabase(DBBorrow_t *books_db);
void freeOneBorrow(Borrow_t *borrow);
void rewriteUsersFile(DBUser_t user_db);
void rewriteBooksFile(DBBook_t books_db);
void rewriteStudentsFile(DBStudent_t students_db);
void rewriteBorrowsFile(DBBorrow_t borrows_db);

#endif //BIGHW_PARSEFREEREWRITE_H
