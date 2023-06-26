#ifndef BIGHW_LOGS_H
#define BIGHW_LOGS_H

#include "menuFile.h"
#include "time.h"

void recordLog(void (*logInterior)(char*), char *adminName);

void func_authentication_log(char *message);
void func_upperMenu_log(char *message);
void func_booksMenu_log(char *message);
void func_studentsMenu_log(char *message);
void func_exitMenu_log(char *message);
void func_addBook_log(char *message);
void func_deleteBook_log(char *message);
void func_editBookInfo_log(char *message);
void func_showOneBook_log(char *message);
void func_showAllBooks_log(char *message);
void func_giveBook_log(char *message);
void func_takeBook_log(char *message);
void func_showLoaners_log(char *message);
void func_addStudent_log(char *message);
void func_deleteStudent_log(char *message);
void func_editStudentInfo_log(char *message);
void func_showStudentByCardNumber_log(char *message);
void func_showStudentBySurname_log(char *message);
void func_showBorrowedBooks_log(char *message);
void logIn_Success_log(char *message);
void logIn_Error_log(char *message);
void logIn_NoRights_log(char *message);
void menu_WrongChoice_log(char *message);
void menu_NoReturnPermission_log(char *message);
void memory_ReallocError_log(char *message);
void exit_Success_log(char *message);
void book_AddError_log(char *message);
void book_AddSuccess_log(char *message);
void book_DeleteBorrowed_log(char *message);
void book_DeleteNotFound_log(char *message);
void book_DeleteSuccess_log(char *message);
void book_EditNotFound_log(char *message);
void book_EditSuccess_log(char *message);
void book_EditWrongChoice_log(char *message);
void book_ShowOneNotFound_log(char *message);
void book_GiveStudentNotFound_log(char *message);
void book_GiveNoBooksAvailable_log(char *message);
void book_GiveBookNotFound_log(char *message);
void book_GiveSuccess_log(char *message);
void book_TakeStudentNotFound_log(char *message);
void book_TakeBookNotFound_log(char *message);
void book_TakeAllBooksBack_log(char *message);
void book_TakeSuccess_log(char *message);
void book_LoanersNotFound_log(char *message);
void student_AddSuccess_log(char *message);
void student_AddError_log(char *message);
void student_DeleteBorrows_log(char *message);
void student_DeleteSuccess_log(char *message);
void student_DeleteNotFound_log(char *message);
void student_EditNotFound_log(char *message);
void student_EditSuccess_log(char *message);
void student_EditWrongChoice_log(char *message);
void student_ShowByCardNotFound_log(char *message);
void student_ShowBySurnameNotFound_log(char *message);
void student_ShowBorrowedNotFound_log(char *message);


#endif //BIGHW_LOGS_H
