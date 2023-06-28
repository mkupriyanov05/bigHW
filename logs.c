#include "logs.h"


void recordLog(void (*logInterior)(char*), char *adminName) {
    FILE *log_f = fopen(LOGS_FILE, "a");

    time_t currTime = time(NULL);
    struct tm *local = localtime(&currTime);
    char timeString[BUFFMAX];
    strcpy(timeString, asctime(local));
    timeString[strlen(timeString) - 1] = '\0';

    char message[BUFFMAX];
    logInterior(message);

    fprintf(log_f, "%s,%s,%s\n", timeString, adminName, message);

    fclose(log_f);
}


void func_signUp_log(char *message) {
    strcpy(message, "signUp");
}

void func_logIn_log(char *message) {
    strcpy(message, "logIn");
}

void func_authentication_log(char *message) {
    strcpy(message, "authentication");
}

void func_upperMenu_log(char *message) {
    strcpy(message, "upperMenu");
}

void func_booksMenu_log(char *message) {
    strcpy(message, "booksMenu");
}

void func_studentsMenu_log(char *message) {
    strcpy(message, "studentsMenu");
}

void func_exitMenu_log(char *message) {
    strcpy(message, "exitMenu");
}

void func_addBook_log(char *message) {
    strcpy(message, "addBook");
}

void func_deleteBook_log(char *message) {
    strcpy(message, "deleteBook");
}

void func_editBookInfo_log(char *message) {
    strcpy(message, "editBookInfo");
}

void func_showOneBook_log(char *message) {
    strcpy(message, "showOneBook");
}

void func_showAllBooks_log(char *message) {
    strcpy(message, "showAllBooks");
}

void func_giveBook_log(char *message) {
    strcpy(message, "giveBook");
}

void func_takeBook_log(char *message) {
    strcpy(message, "takeBook");
}

void func_showLoaners_log(char *message) {
    strcpy(message, "showLoaners");
}

void func_addStudent_log(char *message) {
    strcpy(message, "addStudent");
}

void func_deleteStudent_log(char *message) {
    strcpy(message, "deleteStudent");
}

void func_editStudentInfo_log(char *message) {
    strcpy(message, "editStudentInfo");
}

void func_showStudentByCardNumber_log(char *message) {
    strcpy(message, "showStudentByCardNumber");
}

void func_showStudentBySurname_log(char *message) {
    strcpy(message, "showStudentBySurname");
}

void func_showBorrowedBooks_log(char *message) {
    strcpy(message, "showBorrowedBooks");
}


void logIn_Success_log(char *message) {
    strcpy(message, "Authentication succeed");
}

void logIn_Error_log(char *message) {
    strcpy(message, "Authentication error");
}

void logIn_NoRights_log(char *message) {
    strcpy(message, "You have no rights (woman moment)");
}

void signUp_Success_log(char *message) {
    strcpy(message, "User successfully added");
}

void menu_WrongChoice_log(char *message) {
    strcpy(message, "Wrong menu choice");
}

void menu_NoReturnPermission_log(char *message) {
    strcpy(message, "No permission to return to upper menu");
}

void memory_ReallocError_log(char *message) {
    strcpy(message, "Memory reallocation error");
}

void exit_Success_log(char *message) {
    strcpy(message, "Program finished");
}


void book_AddError_log(char *message) {
    strcpy(message, "ISBN is already taken");
}

void book_AddSuccess_log(char *message) {
    strcpy(message, "Book successfully added");
}

void book_DeleteBorrowed_log(char *message) {
    strcpy(message, "Book cannot be deleted (borrowed)");
}

void book_DeleteNotFound_log(char *message) {
    strcpy(message, "Book cannot be deleted (not found)");
}

void book_DeleteSuccess_log(char *message) {
    strcpy(message, "Book successfully deleted");
}

void book_EditNotFound_log(char *message) {
    strcpy(message, "Book cannot be edited (not found)");
}

void book_EditSuccess_log(char *message) {
    strcpy(message, "Book data successfully edited");
}

void book_EditWrongChoice_log(char *message) {
    strcpy(message, "Wrong info field");
}

void book_ShowOneNotFound_log(char *message) {
    strcpy(message, "Book cannot be shown (not found)");
}

void book_GiveStudentNotFound_log(char *message) {
    strcpy(message, "Book cannot be borrowed (student not found)");
}

void book_GiveNoBooksAvailable_log(char *message) {
    strcpy(message, "Book cannot be borrowed (none available)");
}

void book_GiveBookNotFound_log(char *message) {
    strcpy(message, "Book cannot be borrowed (book not found)");
}

void book_GiveSuccess_log(char *message) {
    strcpy(message, "Book given");
}

void book_TakeStudentNotFound_log(char *message) {
    strcpy(message, "Book cannot be returned (student not found)");
}

void book_TakeBookNotFound_log(char *message) {
    strcpy(message, "Book cannot be returned (book not found)");
}

void book_TakeAllBooksBack_log(char *message) {
    strcpy(message, "Book cannot be returned (all are back)");
}

void book_TakeSuccess_log(char *message) {
    strcpy(message, "Book returned");
}

void book_LoanersNotFound_log(char *message) {
    strcpy(message, "No loaned books with this ISBN");
}

void student_AddSuccess_log(char *message) {
    strcpy(message, "Student added successfully");
}

void student_AddError_log(char *message) {
    strcpy(message, "Card number is already taken");
}

void student_DeleteBorrows_log(char *message) {
    strcpy(message, "Student cannot be deleted (borrows)");
}

void student_DeleteSuccess_log(char *message) {
    strcpy(message, "Student deleted successfully");
}

void student_DeleteNotFound_log(char *message) {
    strcpy(message, "Student cannot be deleted (not found)");
}

void student_EditNotFound_log(char *message) {
    strcpy(message, "Student cannot be edited (not found)");
}

void student_EditSuccess_log(char *message) {
    strcpy(message, "Student data successfully edited");
}

void student_EditWrongChoice_log(char *message) {
    strcpy(message, "Wrong info field");
}

void student_ShowByCardNotFound_log(char *message) {
    strcpy(message, "Student cannot be shown (not found)");
}

void student_ShowBySurnameNotFound_log(char *message) {
    strcpy(message, "No students with this surname");
}

void student_ShowBorrowedNotFound_log(char *message) {
    strcpy(message, "No loaning students with this card number");
}