#include "menuFile.h"
#include "parseFreeRewrite.h"
#include "booksProcessing.h"
#include "studentsProcessing.h"
#include "borrowedProcessing.h"


bool authentication(DBUser_t *user_db, AuthData_t *authData, DBAdmin_t *allDatabases);
void upperMenu(DBAdmin_t *allDatabases, DBUser_t *user_db);
void booksMenu(bool returnPermission, DBAdmin_t *allDatabases, DBUser_t *user_db);
void studentsMenu(bool returnPermission, DBAdmin_t *allDatabases, DBUser_t *user_db);

int launcher() {
    DBAdmin_t allDatabases;
    DBUser_t user_db;

    user_db.usersNumber = 0;
    user_db.usersDatabase = (User_t*)malloc(sizeof(User_t));

    allDatabases.student_db.studentsNumber = 0;
    allDatabases.student_db.studentsDatabase = (Student_t*)malloc(sizeof(Student_t));

    allDatabases.book_db.booksNumber = 0;
    allDatabases.book_db.booksDatabase = (Book_t*)malloc(sizeof(Book_t));

    allDatabases.borrow_db.borrowsNumber = 0;
    allDatabases.borrow_db.borrowsDatabase = (Borrow_t*)malloc(sizeof(Borrow_t));


    parseFile((void**)&(user_db.usersDatabase), &user_db.usersNumber, USERS_FILE, sizeof(User_t), users);
    parseFile((void**)&(allDatabases.student_db.studentsDatabase), &allDatabases.student_db.studentsNumber,
              STUDENTS_FILE, sizeof(Student_t), students);
    parseFile((void**)&(allDatabases.book_db.booksDatabase), &allDatabases.book_db.booksNumber,
              BOOKS_FILE, sizeof(Student_t), books);
    parseFile((void**)&(allDatabases.borrow_db.borrowsDatabase), &allDatabases.borrow_db.borrowsNumber,
              BORROWS_FILE, sizeof(Student_t), borrows);

    AuthData_t authData;

    //Using "scanf" function here due to incorrect hash calculation
    //"fgets" (for strings), "fgets" + "sscanf" (for integers) is used everywhere else

    printf("Enter login:\n");
    scanf("%s", authData.inputLogin);

    printf("Enter password:\n");
    scanf("%s", authData.inputPassword);
    calculateHash(authData.inputPassword);

    char c;
    scanf("%c", &c); //skip trailing newline

    if (!authentication(&user_db, &authData, &allDatabases))
        printf("No such user\n");

    exitMenu(&allDatabases, &user_db);

    return 0;
}


bool authentication(DBUser_t *user_db, AuthData_t *authData, DBAdmin_t *allDatabases) {
    for (int i = 0; i < user_db->usersNumber; ++i) {
        if (strcmp(user_db->usersDatabase[i].login, authData->inputLogin) == 0
            && strcmp(user_db->usersDatabase[i].passHash, authData->inputPassword) == 0) {

            strcpy(authData->inputPassword, "");
            printf("Authentication succeed. Hello, %s!\n", user_db->usersDatabase[i].login);

            if (user_db->usersDatabase[i].studentsRights && user_db->usersDatabase[i].booksRights)
                upperMenu(allDatabases, user_db);

            else if (user_db->usersDatabase[i].studentsRights && !user_db->usersDatabase[i].booksRights)
                studentsMenu(false, allDatabases, user_db);

            else if (!user_db->usersDatabase[i].studentsRights && user_db->usersDatabase[i].booksRights)
                booksMenu(false, allDatabases, user_db);

            else
                printf("You have no rights (woman moment)\n");

            return true;
        }
    }
    strcpy(authData->inputPassword, "");
    printf("Wrong login or password\n");

    return false;
}


void upperMenu(DBAdmin_t *allDatabases, DBUser_t *user_db) {
    char buffString[BUFFMAX];
    int menuChoice;

    printf("Choose menu to work with.\n");
    printf("0 - finish the program\n");
    printf("1 - bookz\n");
    printf("2 - studentz\n");
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &menuChoice);

    switch (menuChoice) {
        case 0:
            exitMenu(allDatabases, user_db);
            break;
        case books:
            booksMenu(true, allDatabases, user_db);
            break;
        case students:
            studentsMenu(true, allDatabases, user_db);
            break;
        default:
            printf("Try again\n");
            break;
    }
    upperMenu(allDatabases, user_db);
}


void booksMenu(bool returnPermission, DBAdmin_t *allDatabases, DBUser_t *user_db) {
    printf("Choose watcha wanna do with book database:\n");
    printf("0 - Finish the program\n");
    printf("1 - Return to the menu of the menus\n");
    printf("2 - Add book\n");
    printf("3 - Delete book\n");
    printf("4 - Edit book info\n");
    printf("5 - See one book info\n");
    printf("6 - See all books info (sorted by ISBN)\n");
    printf("7 - Register a loan\n");
    printf("8 - Register a return\n");
    printf("9 - See all borrowers of certain book\n");

    char buffString[BUFFMAX];
    int choice;
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &choice);

    switch (choice) {
        case finish_b:
            exitMenu(allDatabases, user_db);
            break;
        case rtrn_b:
            if (returnPermission) {
                upperMenu(allDatabases, user_db);
                break;
            } else {
                printf("Sorry, you have no permission to return to upper menu\n");
                break;
            }
        case add_b:
            addBook(&allDatabases->book_db);
            break;
        case del_b:
            deleteBook(allDatabases);
            break;
        case edit_b:
            editBookInfo(&allDatabases->book_db);
            break;
        case oneBook_b:
            showOneBook(&allDatabases->book_db);
            break;
        case allBooks_b:
            showAllBooks(&allDatabases->book_db);
            break;
        case give_b:
            giveBook(allDatabases);
            break;
        case take_b:
            takeBook(allDatabases);
            break;
        case borrowers_b:
            showLoaners(allDatabases);
            break;
        default:
            printf("Try again\n");
            break;
    }
    booksMenu(returnPermission, allDatabases, user_db);
}


void studentsMenu(bool returnPermission, DBAdmin_t *allDatabases, DBUser_t *user_db) {
    printf("Choose watcha wanna do with student database:\n");
    printf("0 - Finish the program\n");
    printf("1 - Return to the menu of the menus\n");
    printf("2 - Add student\n");
    printf("3 - Delete student\n");
    printf("4 - Edit student info\n");
    printf("5 - See student by card number\n");
    printf("6 - See student by surname\n");
    printf("7 - See books borrowed by certain student\n");

    char buffString[BUFFMAX];
    int choice;
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &choice);

    switch (choice) {
        case finish_s:
            exitMenu(allDatabases, user_db);
            break;
        case rtrn_s:
        if (returnPermission) {
            upperMenu(allDatabases, user_db);
            break;
        } else {
            printf("Sorry, you have no permission to return to upper menu");
            break;
        }
        case add_s:
            addStudent(&allDatabases->student_db);
            break;
        case del_s:
            deleteStudent(allDatabases);
            break;
        case edit_s:
            editStudentInfo(&allDatabases->student_db);
            break;
        case studentByCard_s:
            showStudentByCardNumber(&allDatabases->student_db);
            break;
        case studentBySurname_s:
            showStudentBySurname(&allDatabases->student_db);
            break;
        case borrowed_s:
            showBorrowedBooks(allDatabases);
            break;
        default:
            printf("Try again\n");
            break;
    }
    studentsMenu(returnPermission, allDatabases, user_db);
}

void exitMenu(DBAdmin_t *allDatabases, DBUser_t *user_db) {
    rewriteBooksFile(allDatabases->book_db);
    rewriteStudentsFile(allDatabases->student_db);
    rewriteBorrowsFile(allDatabases->borrow_db);

    freeUsersDatabase(user_db);
    freeBooksDatabase(&allDatabases->book_db);
    freeStudentsDatabase(&allDatabases->student_db);
    freeBorrowsDatabase(&allDatabases->borrow_db);

    printf("Program successfully finished!\n");
    exit(0);
}
