#ifndef BIGHW_STUDENTSPROCESSING_H
#define BIGHW_STUDENTSPROCESSING_H
#include "menuAuth.h"


void addStudent(DBStudent_t *students_db, char *admin);
void deleteStudent(DBAdmin_t *allDatabases, char *admin);
void editStudentInfo(DBStudent_t *students_db, char *admin);
void showStudentByCardNumber(DBStudent_t *students_db, char *admin);
void showStudentBySurname(DBStudent_t *students_db, char *admin);
void showBorrowedBooks(DBAdmin_t *allDatabases, char *admin);


enum studentActions {
    finish_s,
    rtrn_s,
    add_s,
    del_s,
    edit_s,
    studentByCard_s,
    studentBySurname_s,
    borrowed_s
};


enum editStudentsChoice {
    first_name = 1,
    surname,
    faculty,
    specialty
};

#endif //BIGHW_STUDENTSPROCESSING_H
