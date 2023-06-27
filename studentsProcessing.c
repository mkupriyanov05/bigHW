#include "studentsProcessing.h"
#include "parseFreeRewrite.h"
#include "borrowedProcessing.h"
#include "logs.h"


void addStudent(DBStudent_t *students_db, char *admin) {
    recordLog(func_addStudent_log, admin);

    char buffString[BUFFMAX];
    printf("Enter card number:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';

    for (int i = 0; i < students_db->studentsNumber; i++) {
        if (strcmp(buffString, students_db->studentsDatabase[i].cardNumber) == 0) {
            printf("Sorry, this card number is already taken by another student\n");
            recordLog(student_AddError_log, admin);
            return;
        }
    }

    Student_t *temp;
    temp = realloc(students_db->studentsDatabase, sizeof(Student_t) * (students_db->studentsNumber + 1));
    if (temp != NULL)
        students_db->studentsDatabase = temp;
    else {
        printf("Sorry, this programmer is talentless\n");
        recordLog(memory_ReallocError_log, admin);
        return;
    }

    students_db->studentsDatabase[students_db->studentsNumber].cardNumber = calloc(strlen(buffString), sizeof(char));
    strcpy(students_db->studentsDatabase[students_db->studentsNumber].cardNumber, buffString);

    printf("Enter first name:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';
    students_db->studentsDatabase[students_db->studentsNumber].firstName = calloc(strlen(buffString), sizeof(char));
    strcpy(students_db->studentsDatabase[students_db->studentsNumber].firstName, buffString);

    printf("Enter surname:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';
    students_db->studentsDatabase[students_db->studentsNumber].surName = calloc(strlen(buffString), sizeof(char));
    strcpy(students_db->studentsDatabase[students_db->studentsNumber].surName, buffString);

    printf("Enter faculty:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';
    students_db->studentsDatabase[students_db->studentsNumber].faculty = calloc(strlen(buffString), sizeof(char));
    strcpy(students_db->studentsDatabase[students_db->studentsNumber].faculty, buffString);

    printf("Enter speciality:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';
    students_db->studentsDatabase[students_db->studentsNumber].speciality = calloc(strlen(buffString), sizeof(char));
    strcpy(students_db->studentsDatabase[students_db->studentsNumber].speciality, buffString);

    students_db->studentsNumber++;
    printf("Student added successfully\n");
    recordLog(student_AddSuccess_log, admin);
}


void deleteStudent(DBAdmin_t *allDatabases, char *admin) {
    recordLog(func_deleteStudent_log, admin);

    char cardNumber[BUFFMAX];
    printf("Enter card number to delete student from database:\n");
    fgets(cardNumber, BUFFMAX, stdin);
    cardNumber[strlen(cardNumber) - 1] = '\0';

    for (int i = 0; i < allDatabases->student_db.studentsNumber; i++) {
        if (strcmp(cardNumber, allDatabases->student_db.studentsDatabase[i].cardNumber) == 0) {
            if (ifStudentHasBooks(&allDatabases->borrow_db, allDatabases->student_db.studentsDatabase[i])) {
                printf("Cannot delete student that borrows books\n");
                recordLog(student_DeleteBorrows_log, admin);
                return;
            }
            freeOneStudent(&allDatabases->student_db.studentsDatabase[i]);
            for (int j = i; j < allDatabases->student_db.studentsNumber - 1; j++)
                allDatabases->student_db.studentsDatabase[j] = allDatabases->student_db.studentsDatabase[j + 1];
            allDatabases->student_db.studentsNumber--;

            printf("Student successfully deleted!\n");
            recordLog(student_DeleteSuccess_log, admin);
            return;
        }
    }
    printf("Sorry, you're trying to delete imaginary student\n");
    recordLog(student_DeleteSuccess_log, admin);
}


void editStudentInfo(DBStudent_t *students_db, char *admin) {
    recordLog(func_editStudentInfo_log, admin);

    char buffString[BUFFMAX];
    printf("Enter student's card number or '0' to exit editor:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';

    if (strcmp(buffString, "0") == 0)
        return;

    int i = 0;
    for (; i < students_db->studentsNumber; i++) {
        if (strcmp(buffString, students_db->studentsDatabase[i].cardNumber) == 0)
            break;
    }

    if (i == students_db->studentsNumber) {
        printf("Sorry, you're trying to edit imaginary student's info\n");
        recordLog(student_EditNotFound_log, admin);
        return;
    }

    printf("Choose which info you want to edit:\n");
    printf("0 - Exit editor\n");
    printf("1 - First Name\n");
    printf("2 - Surname\n");
    printf("3 - Faculty\n");
    printf("4 - Specialty\n");

    int choice;
    fgets(buffString, BUFFMAX, stdin);
    choice = strtol(buffString, NULL, 10);

    switch (choice) {
        case 0:
            return;

        case first_name:
            printf("Enter new first name:\n");
            fgets(buffString, BUFFMAX, stdin);
            buffString[strlen(buffString) - 1] = '\0';

            strcpy(students_db->studentsDatabase[i].firstName, buffString);
            strcpy(buffString, "");

            printf("Data successfully edited!\n");
            recordLog(student_EditSuccess_log, admin);
            break;

        case surname:
            printf("Enter new surname:\n");
            fgets(buffString, BUFFMAX, stdin);
            buffString[strlen(buffString) - 1] = '\0';

            strcpy(students_db->studentsDatabase[i].surName, buffString);
            strcpy(buffString, "");

            printf("Data successfully edited!\n");
            recordLog(student_EditSuccess_log, admin);
            break;

        case faculty:
            printf("Enter new faculty:\n");
            fgets(buffString, BUFFMAX, stdin);
            buffString[strlen(buffString) - 1] = '\0';

            strcpy(students_db->studentsDatabase[i].faculty, buffString);
            strcpy(buffString, "");

            printf("Data successfully edited!\n");
            recordLog(student_EditSuccess_log, admin);
            break;

        case specialty:
            printf("Enter new specialty:\n");
            fgets(buffString, BUFFMAX, stdin);
            buffString[strlen(buffString) - 1] = '\0';

            strcpy(students_db->studentsDatabase[i].speciality, buffString);
            strcpy(buffString, "");

            printf("Data successfully edited!\n");
            recordLog(student_EditSuccess_log, admin);
            break;

        default:
            printf("Wrong info field is chosen. Try again\n");
            recordLog(student_EditWrongChoice_log, admin);
            break;
    }
    editStudentInfo(students_db, admin);
}


void showStudentByCardNumber(DBStudent_t *students_db, char *admin) {
    recordLog(func_showStudentByCardNumber_log, admin);

    char buffString[BUFFMAX];
    printf("Enter card number to see student info:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';

    for (int i = 0; i < students_db->studentsNumber; ++i) {
        if (strcmp(students_db->studentsDatabase[i].cardNumber, buffString) == 0) {
            printf("Student: card number -> %s, first name -> %s, surname -> %s, faculty -> %s, speciality -> %s\n",
                   students_db->studentsDatabase[i].cardNumber, students_db->studentsDatabase[i].firstName,
                   students_db->studentsDatabase[i].surName, students_db->studentsDatabase[i].faculty,
                   students_db->studentsDatabase[i].speciality);
            return;
        }
    }

    printf("Sorry, no student with this card number\n");
    recordLog(student_ShowByCardNotFound_log, admin);
}

void showStudentBySurname(DBStudent_t *students_db, char *admin) {
    recordLog(func_showStudentBySurname_log, admin);

    char buffString[BUFFMAX];
    bool studentFound = false;
    printf("Enter surname to see student info:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';

    printf("Card number \t First name \t Surname \t Faculty \t Speciality\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < students_db->studentsNumber; ++i) {
        if (strcmp(buffString, students_db->studentsDatabase[i].surName) == 0) {
            printf("%s \t %s \t %s \t %s \t %s\n",
                   students_db->studentsDatabase[i].cardNumber, students_db->studentsDatabase[i].firstName,
                   students_db->studentsDatabase[i].surName, students_db->studentsDatabase[i].faculty,
                   students_db->studentsDatabase[i].speciality);
            studentFound = true;
            printf("-------------------------------------------------------------\n");
        }
    }

    if (!studentFound) {
        printf("Sorry, no student with this surname\n");
        recordLog(student_ShowBySurnameNotFound_log, admin);
    }
}

void showBorrowedBooks(DBAdmin_t *allDatabases, char *admin) {
    recordLog(func_showBorrowedBooks_log, admin);

    char buffString[BUFFMAX];
    printf("Enter student's card number:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';

    for (int i = 0; i < allDatabases->borrow_db.borrowsNumber; ++i) {
        if (strcmp(allDatabases->borrow_db.borrowsDatabase[i].cardNumber, buffString) == 0) {
            for (int j = 0; j < allDatabases->book_db.booksNumber; ++j) {
                if (allDatabases->book_db.booksDatabase[j].ISBN == allDatabases->borrow_db.borrowsDatabase[i].ISBN) {
                    printf("Book: ISBN -> %d, author name -> %s, book's name -> %s, max amount -> %d, curr amount -> %d. ",
                           allDatabases->book_db.booksDatabase[j].ISBN,
                           allDatabases->book_db.booksDatabase[j].author,
                           allDatabases->book_db.booksDatabase[j].bookName,
                           allDatabases->book_db.booksDatabase[j].maxAmount,
                           allDatabases->book_db.booksDatabase[j].currAmount);
                    printf("Return time: %s\n",
                           allDatabases->borrow_db.borrowsDatabase[i].returnTime);
                    return;
                }
            }
        }
    }
    printf("No student with this card number or they don't have any books\n");
    recordLog(student_ShowBorrowedNotFound_log, admin);
}
