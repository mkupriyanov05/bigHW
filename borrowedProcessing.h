#ifndef BIGHW_BORROWEDPROCESSING_H
#define BIGHW_BORROWEDPROCESSING_H

#include "menuAuth.h"


bool ifStudentHasBooks(DBBorrow_t *borrow_db, Student_t currStudent);
bool ifBookBelongsToStudent(DBBorrow_t *borrow_db, Book_t currBook);
void registerLoan(DBBorrow_t *borrows_db, int ISBN, char *cardNumber, char *admin);
void registerReturn(DBBorrow_t *borrows_db, int ISBN);


#endif //BIGHW_BORROWEDPROCESSING_H
