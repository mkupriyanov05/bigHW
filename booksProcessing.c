#include "booksProcessing.h"
#include "parseFreeRewrite.h"
#include "borrowedProcessing.h"
#include "sortAlgorithm.h"
#include "logs.h"


void addBook(DBBook_t *books_db, char *admin) {
    recordLog(func_addBook_log, admin);

    char buffString[BUFFMAX];
    int ISBN;

    printf("Enter ISBN:\n");
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &ISBN);

    for (int i = 0; i < books_db->booksNumber; i++) {
        if (ISBN == books_db->booksDatabase[i].ISBN) {
            printf("Sorry, this ISBN is already taken by another book\n");
            recordLog(book_AddError_log, admin);
            return;
        }
    }

    Book_t *temp;
    temp = realloc(books_db->booksDatabase, sizeof(Book_t) * (books_db->booksNumber + 1));
    if (temp != NULL)
        books_db->booksDatabase = temp;
    else {
        printf("Sorry, this programmer is talentless\n");
        recordLog(memory_ReallocError_log, admin);
        return;
    }

    books_db->booksDatabase[books_db->booksNumber].ISBN = ISBN;

    printf("Enter author:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';
    books_db->booksDatabase[books_db->booksNumber].author = calloc(strlen(buffString), sizeof(char));
    strcpy(books_db->booksDatabase[books_db->booksNumber].author, buffString);

    printf("Enter book name:\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';
    books_db->booksDatabase[books_db->booksNumber].bookName = calloc(strlen(buffString), sizeof(char));
    strcpy(books_db->booksDatabase[books_db->booksNumber].bookName, buffString);

    printf("Enter max amount of books (amount of available books fills up automatically):\n");
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &books_db->booksDatabase[books_db->booksNumber].maxAmount);
    books_db->booksDatabase[books_db->booksNumber].currAmount =
            books_db->booksDatabase[books_db->booksNumber].maxAmount;

    books_db->booksNumber++;
    printf("Book successfully added!\n");
    recordLog(book_AddSuccess_log, admin);
}


void deleteBook(DBAdmin_t *allDatabases, char *admin) {
    recordLog(func_deleteBook_log, admin);

    char buffString[BUFFMAX];
    int ISBN;
    printf("Enter book ISBN to delete from database:\n");
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &ISBN);

    for (int i = 0; i < allDatabases->book_db.booksNumber; i++) {
        if (ISBN == allDatabases->book_db.booksDatabase[i].ISBN) {
            if (ifBookBelongsToStudent(&allDatabases->borrow_db, allDatabases->book_db.booksDatabase[i])) {
                printf("Cannot delete book that is borrowed by a student\n");
                recordLog(book_DeleteBorrowed_log, admin);
                return;
            }
            freeOneBook(&allDatabases->book_db.booksDatabase[i]);
            for (int j = i; j < allDatabases->book_db.booksNumber - 1; j++)
                allDatabases->book_db.booksDatabase[j] = allDatabases->book_db.booksDatabase[j + 1];
            allDatabases->book_db.booksNumber--;

            printf("Book successfully deleted!\n");
            recordLog(book_DeleteSuccess_log, admin);
            return;
        }
    }
    printf("Sorry, you're trying to delete imaginary book\n");
    recordLog(book_DeleteNotFound_log, admin);
}

void editBookInfo(DBBook_t *books_db, char *admin) {
    recordLog(func_editBookInfo_log, admin);

    char buffString[BUFFMAX];
    int currISBN;
    printf("Enter book's ISBN or '0' to exit editor:\n");
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &currISBN);

    if (currISBN == 0)
        return;

    int i = 0;
    for (; i < books_db->booksNumber; i++) {
        if (currISBN == books_db->booksDatabase[i].ISBN)
            break;
    }

    if (i == books_db->booksNumber) {
        printf("Sorry, you're trying to edit imaginary book's info\n");
        recordLog(book_EditNotFound_log, admin);
        return;
    }

    printf("Choose which info you want to edit:\n");
    printf("0 - Exit editor\n");
    printf("1 - Author\n");
    printf("2 - Book's name\n");
    printf("3 - Max amount\n");
    printf("%s;%s\n", books_db->booksDatabase[i].author, books_db->booksDatabase[i].bookName);

    int choice;
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &choice);
    printf("%s;%s\n", books_db->booksDatabase[i].author, books_db->booksDatabase[i].bookName);

    char newInfo[BUFFMAX];
    int prevMaxAmount = books_db->booksDatabase[i].maxAmount;

    switch (choice) {
        case 0:
            return;

        case author:
            printf("Enter new author:\n");
            fgets(newInfo, BUFFMAX, stdin);
            newInfo[strlen(newInfo) - 1] = '\0';

            strcpy(books_db->booksDatabase[i].author, newInfo);
            strcpy(newInfo, "");

            printf("Data successfully edited!\n");
            recordLog(book_EditSuccess_log, admin);
            break;

        case book_name:
            printf("Enter new book name:\n");
            fgets(newInfo, BUFFMAX, stdin);
            newInfo[strlen(newInfo) - 1] = '\0';

            strcpy(books_db->booksDatabase[i].bookName, newInfo);
            strcpy(newInfo, "");

            printf("Data successfully edited!\n");
            recordLog(book_EditSuccess_log, admin);
            break;

        case max_amount:
            do {
                printf("Enter new max amount (max amount cannot be less than amount of borrowed books):\n");
                fgets(newInfo, BUFFMAX, stdin);
                sscanf(newInfo, "%d", &books_db->booksDatabase[i].maxAmount);
            } while (books_db->booksDatabase[i].maxAmount < (prevMaxAmount - books_db->booksDatabase[i].currAmount));

            books_db->booksDatabase[i].currAmount += (books_db->booksDatabase[i].maxAmount - prevMaxAmount);

            printf("Data successfully edited!\n");
            recordLog(book_EditSuccess_log, admin);
            break;

        default:
            printf("Wrong info field is chosen. Try again\n");
            recordLog(book_EditWrongChoice_log, admin);
            break;
    }
    editBookInfo(books_db, admin);
}

void showOneBook(DBBook_t *books_db, char *admin) {
    recordLog(func_showOneBook_log, admin);

    char buffString[BUFFMAX];
    int currISBN;
    printf("Enter ISBN to watch book info:\n");
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &currISBN);

    for (int i = 0; i < books_db->booksNumber; ++i) {
        if (books_db->booksDatabase[i].ISBN == currISBN) {
            printf("Book: ISBN -> %d, author name -> %s, book's name -> %s, max amount -> %d, curr amount -> %d\n",
                   books_db->booksDatabase[i].ISBN, books_db->booksDatabase[i].author,
                   books_db->booksDatabase[i].bookName, books_db->booksDatabase[i].maxAmount,
                   books_db->booksDatabase[i].currAmount);
            return;
        }
    }

    printf("Sorry, no book with this ISBN\n");
    recordLog(book_ShowOneNotFound_log, admin);
}


void showAllBooks(DBBook_t *books_db, char *admin) {
    recordLog(func_showAllBooks_log, admin);

    quickSort(books_db->booksDatabase, 0, books_db->booksNumber - 1, compareIntegers, offsetof(Book_t, ISBN));

    printf("ISBN \t Author \t Book Name \t Max Amount \t Curr Amount\n");
    for (int i = 0; i < books_db->booksNumber; ++i) {
        printf("%d \t %s \t %s \t %d \t %d\n",
               books_db->booksDatabase[i].ISBN, books_db->booksDatabase[i].author,
               books_db->booksDatabase[i].bookName, books_db->booksDatabase[i].maxAmount,
               books_db->booksDatabase[i].currAmount);
    }
}

void giveBook(DBAdmin_t *allDatabases, char *admin) {
    recordLog(func_giveBook_log, admin);

    char buffString[BUFFMAX];
    int ISBN;

    printf("Enter ISBN of the book you want to take:\n");
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &ISBN);

    printf("Enter student's card number\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';

    bool studentFound = false;

    int j = 0;
    for (; j < allDatabases->student_db.studentsNumber; ++j) {
        if (strcmp(allDatabases->student_db.studentsDatabase[j].cardNumber, buffString) == 0) {
            studentFound = true;
            break;
        }
    }

    if (!studentFound) {
        printf("Sorry, student not found\n");
        recordLog(book_GiveStudentNotFound_log, admin);
        return;
    }

    for (int i = 0; i < allDatabases->book_db.booksNumber; ++i) {
        if (allDatabases->book_db.booksDatabase[i].ISBN == ISBN) {
            if (allDatabases->book_db.booksDatabase[i].currAmount == 0) {
                printf("No books with ISBN %d available(\n",
                       allDatabases->book_db.booksDatabase[i].ISBN);
                recordLog(book_GiveNoBooksAvailable_log, admin);
                return;
            }
            allDatabases->book_db.booksDatabase[i].currAmount--;
            registerLoan(&allDatabases->borrow_db, ISBN, buffString, admin);
            printf("Loan registered!\n");
            recordLog(book_GiveSuccess_log, admin);
            return;
        }
    }
    printf("Sorry, book haven't been found\n");
    recordLog(book_GiveBookNotFound_log, admin);
}

static bool amountProcessing(DBBook_t *books_db, int ISBN) {
    for (int i = 0; i < books_db->booksNumber; ++i) {
        if (books_db->booksDatabase[i].ISBN == ISBN) {
            if (books_db->booksDatabase[i].currAmount == books_db->booksDatabase[i].maxAmount) {
                printf("All books were given back before. Cannot take back book with %d ISBN\n",
                       books_db->booksDatabase[i].ISBN);
                return true;
            }
            books_db->booksDatabase[i].currAmount++;
            return false;
        }
    }
    return true;
}

void takeBook(DBAdmin_t *allDatabases, char *admin) {
    recordLog(func_takeBook_log, admin);

    char buffString[BUFFMAX];
    int ISBN;
    printf("Enter ISBN of the book you want to give back:\n");
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &ISBN);

    printf("Enter student's card number\n");
    fgets(buffString, BUFFMAX, stdin);
    buffString[strlen(buffString) - 1] = '\0';

    bool studentFound = false;
    bool bookFound = false;

    for (int j = 0; j < allDatabases->borrow_db.borrowsNumber; ++j) {
        if (strcmp(allDatabases->borrow_db.borrowsDatabase[j].cardNumber, buffString) == 0)
            studentFound = true;
        if (allDatabases->borrow_db.borrowsDatabase[j].ISBN == ISBN)
            bookFound = true;
        if (studentFound && bookFound)
            break;
    }

    if (!studentFound) {
        printf("Sorry, student not found\n");
        recordLog(book_TakeStudentNotFound_log, admin);
        return;
    }
    if (!bookFound) {
        printf("Sorry, book not found\n");
        recordLog(book_TakeBookNotFound_log, admin);
        return;
    }

    if (amountProcessing(&allDatabases->book_db, ISBN)) {
        recordLog(book_TakeAllBooksBack_log, admin);
        return;
    }

    registerReturn(&allDatabases->borrow_db, ISBN);
    printf("Book returned!\n");
    recordLog(book_TakeSuccess_log, admin);
}

void showLoaners(DBAdmin_t *allDatabases, char *admin) {
    recordLog(func_showLoaners_log, admin);

    char buffString[BUFFMAX];
    int ISBN;
    printf("Enter book's ISBN:\n");
    fgets(buffString, BUFFMAX, stdin);
    sscanf(buffString, "%d", &ISBN);

    for (int i = 0; i < allDatabases->borrow_db.borrowsNumber; ++i) {
        if (allDatabases->borrow_db.borrowsDatabase[i].ISBN == ISBN) {
            for (int j = 0; j < allDatabases->student_db.studentsNumber; ++j) {
                if (strcmp(allDatabases->student_db.studentsDatabase[j].cardNumber,
                           allDatabases->borrow_db.borrowsDatabase[i].cardNumber) == 0) {
                    printf("Student: card number -> %s, first name -> %s, surname -> %s, faculty -> %s, speciality -> %s. ",
                           allDatabases->student_db.studentsDatabase[j].cardNumber,
                           allDatabases->student_db.studentsDatabase[j].firstName,
                           allDatabases->student_db.studentsDatabase[j].surName,
                           allDatabases->student_db.studentsDatabase[j].faculty,
                           allDatabases->student_db.studentsDatabase[j].speciality);
                    printf("Return time: %s\n",
                           allDatabases->borrow_db.borrowsDatabase[i].returnTime);
                    return;
                }
            }
        }
    }
    printf("No book with this ISBN or there aren't loaned books with this ISBN\n");
    recordLog(book_LoanersNotFound_log, admin);
}
