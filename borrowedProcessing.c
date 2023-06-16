#include "borrowedProcessing.h"
#include "parseFreeRewrite.h"


bool ifStudentHasBooks(DBBorrow_t *borrow_db, Student_t currStudent) {
    for (int i = 0; i < borrow_db->borrowsNumber; ++i) {
        if (strcmp(borrow_db->borrowsDatabase[i].cardNumber, currStudent.cardNumber) == 0)
            return true;
    }
    return false;
}


bool ifBookBelongsToStudent(DBBorrow_t *borrow_db, Book_t currBook) {
    for (int i = 0; i < borrow_db->borrowsNumber; ++i) {
        if (borrow_db->borrowsDatabase[i].ISBN == currBook.ISBN)
            return true;
    }
    return false;
}

void addBorrowToFile(Borrow_t *newBorrow, char mode[]) {
    FILE *borrows_f = fopen(BORROWS_FILE, mode);

    if (borrows_f == NULL) {
        puts("file opening error");
        exit(1);
    }

    if (strcmp(mode, "w") != 0)
        fprintf(borrows_f, "\n");

    fprintf(borrows_f, "%d,%s,%s",
            newBorrow->ISBN, newBorrow->cardNumber, newBorrow->returnTime);

    fclose(borrows_f);
}

void registerLoan(DBBorrow_t *borrows_db, int ISBN, char cardNumber[]) {
    Borrow_t *temp;
    temp = realloc(borrows_db->borrowsDatabase, sizeof(Borrow_t) * (borrows_db->borrowsNumber + 1));
    if (temp != NULL)
        borrows_db->borrowsDatabase = temp;
    else {
        puts("Sorry, this programmer is talentless");
        return;
    }

    borrows_db->borrowsDatabase[borrows_db->borrowsNumber].ISBN = ISBN;

    borrows_db->borrowsDatabase[borrows_db->borrowsNumber].cardNumber = malloc(strlen(cardNumber) * sizeof(char));
    strcpy(borrows_db->borrowsDatabase[borrows_db->borrowsNumber].cardNumber, cardNumber);

    char returnTime[BUFFMAX];

    do {
        printf("Enter return time without \",\" character (use DD.MM.YYYY format):\n");
        fgets(returnTime, BUFFMAX, stdin);
    } while (strchr(returnTime, ',') != NULL);

    borrows_db->borrowsDatabase[borrows_db->borrowsNumber].returnTime = malloc(strlen(returnTime) * sizeof(char));
    strcpy(borrows_db->borrowsDatabase[borrows_db->borrowsNumber].returnTime, returnTime);

    borrows_db->borrowsNumber++;
}


void registerReturn(DBBorrow_t *borrows_db, int ISBN) {
    for (int i = 0; i < borrows_db->borrowsNumber; ++i) {
        if (borrows_db->borrowsDatabase[i].ISBN == ISBN) {
            freeOneBorrow(&borrows_db->borrowsDatabase[i]);
            for (int j = i; j < borrows_db->borrowsNumber - 1; j++)
                borrows_db->borrowsDatabase[j] = borrows_db->borrowsDatabase[j + 1];
            borrows_db->borrowsNumber--;
            return;
        }
    }
}
