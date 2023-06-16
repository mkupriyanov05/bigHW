#ifndef BIGHW_STUDENTSPROCESSING_H
#define BIGHW_STUDENTSPROCESSING_H
#include "menuFile.h"


void addStudent(DBStudent_t *students_db);
void deleteStudent(DBAdmin_t *allDatabases);
void rewriteStudentsFile(DBStudent_t students_db);
void editStudentInfo(DBStudent_t *students_db);
void showStudentByCardNumber(DBStudent_t *students_db);
void showStudentBySurname(DBStudent_t *students_db);
void showBorrowedBooks(DBAdmin_t *allDatabases);


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
