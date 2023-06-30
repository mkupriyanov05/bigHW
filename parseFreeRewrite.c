#include "parseFreeRewrite.h"
#include "menuAuth.h"


void parseFile(void **database, int *itemsNumber, char *filename,
               size_t structSize, void (*structFill)(void**, int, char*)) {
    FILE *parse_f = fopen(filename, "r");

    if (parse_f == NULL) {
        printf("Sorry, file opening error\n");
        exit(1);
    }

    fseek(parse_f, 0, SEEK_END);
    int length = ftell(parse_f);
    fseek(parse_f, 0, SEEK_SET);
    char *buffer = (char*)calloc(length, sizeof(char));
    if (buffer)
        fread(buffer, 1, length, parse_f);

    char *strToken, *fileRest;
    const char strDelimiter[] = "\n";

    strToken = strtok_r(buffer, strDelimiter, &fileRest);
    void **temp;

    while (strToken) {
        temp = realloc(*database, ((*itemsNumber) + 1) * structSize);
        if (temp != NULL)
            *database = temp;
        else {
            printf("Sorry, this programmer is talentless\n");
            exit(1);
        }

//        if (parseType == users)
//            structUserFill((User_t**)database, *itemsNumber, strToken);
//        else if (parseType == books)
//            structBookFill((Book_t**)database, *itemsNumber, strToken);
//        else if (parseType == students)
//            structStudentFill((Student_t**)database, *itemsNumber, strToken);
//        else if (parseType == borrows)
//            structBorrowFill((Borrow_t**)database, *itemsNumber, strToken);

        structFill(database, *itemsNumber, strToken);

        strToken = strtok_r(fileRest, strDelimiter, &fileRest);
        (*itemsNumber)++;
    }
    free(buffer);
    fclose(parse_f);
}


void structUserFill(void **database, int usersNumber, char *strToken) {
    User_t **usersDatabase = (User_t**)database;
    char *lilToken;
    const char lilDelimiter[] = ",";

    lilToken = strtok(strToken, lilDelimiter);
    (*usersDatabase)[usersNumber].login = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*usersDatabase)[usersNumber].login, lilToken);

    lilToken = strtok(NULL, lilDelimiter);
    (*usersDatabase)[usersNumber].passHash = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*usersDatabase)[usersNumber].passHash, lilToken);

    strcpy(lilToken, "");

    (*usersDatabase)[usersNumber].studentsRights = (bool)atoi(strtok(NULL, lilDelimiter));

    (*usersDatabase)[usersNumber].booksRights = (bool)atoi(strtok(NULL, lilDelimiter));
}

void structBookFill(void **database, int booksNumber, char *strToken) {
    Book_t **booksDatabase = (Book_t**)database;
    char *lilToken;
    const char lilDelimiter[] = ",";

    (*booksDatabase)[booksNumber].ISBN = atoi(strtok(strToken, lilDelimiter));

    lilToken = strtok(NULL, lilDelimiter);
    (*booksDatabase)[booksNumber].author = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*booksDatabase)[booksNumber].author, lilToken);

    lilToken = strtok(NULL, lilDelimiter);
    (*booksDatabase)[booksNumber].bookName = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*booksDatabase)[booksNumber].bookName, lilToken);

    (*booksDatabase)[booksNumber].maxAmount = atoi(strtok(NULL, lilDelimiter));

    (*booksDatabase)[booksNumber].currAmount = atoi(strtok(NULL, lilDelimiter));

    strcpy(lilToken, "");
}

void structStudentFill(void **database, int studentsNumber, char *strToken) {
    Student_t **studentsDatabase = (Student_t**)database;
    char *lilToken;
    const char lilDelimiter[] = ",";

    lilToken = strtok(strToken, lilDelimiter);
    (*studentsDatabase)[studentsNumber].cardNumber = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*studentsDatabase)[studentsNumber].cardNumber, lilToken);

    lilToken = strtok(NULL, lilDelimiter);
    (*studentsDatabase)[studentsNumber].firstName = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*studentsDatabase)[studentsNumber].firstName, lilToken);

    lilToken = strtok(NULL, lilDelimiter);
    (*studentsDatabase)[studentsNumber].surName = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*studentsDatabase)[studentsNumber].surName, lilToken);

    lilToken = strtok(NULL, lilDelimiter);
    (*studentsDatabase)[studentsNumber].faculty = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*studentsDatabase)[studentsNumber].faculty, lilToken);

    lilToken = strtok(NULL, lilDelimiter);
    (*studentsDatabase)[studentsNumber].speciality = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*studentsDatabase)[studentsNumber].speciality, lilToken);

    strcpy(lilToken, "");
}

void structBorrowFill(void **database, int borrowNumber, char *strToken) {
    Borrow_t **borrowDatabase = (Borrow_t**)database;
    char *lilToken;
    const char lilDelimiter[] = ",";

    (*borrowDatabase)[borrowNumber].ISBN = atoi(strtok(strToken, lilDelimiter));

    lilToken = strtok(NULL, lilDelimiter);
    (*borrowDatabase)[borrowNumber].cardNumber = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*borrowDatabase)[borrowNumber].cardNumber, lilToken);

    lilToken = strtok(NULL, lilDelimiter);
    (*borrowDatabase)[borrowNumber].returnTime = (char*)malloc(strlen(lilToken) * sizeof(char));
    strcpy((*borrowDatabase)[borrowNumber].returnTime, lilToken);

    strcpy(lilToken, "");
}


void freeOneUser(User_t *user) {
    free(user->login);
    free(user->passHash);
}

void freeUsersDatabase(DBUser_t *users_db) {
    for (int i = 0; i < users_db->usersNumber; ++i)
        freeOneUser(&users_db->usersDatabase[i]);
    free(users_db->usersDatabase);
}

void freeOneBook(Book_t *book) {
    free(book->author);
    free(book->bookName);
}

void freeBooksDatabase(DBBook_t *books_db) {
    for (int i = 0; i < books_db->booksNumber; ++i)
        freeOneBook(&books_db->booksDatabase[i]);
    free(books_db->booksDatabase);
}

void freeOneStudent(Student_t *student) {
    free(student->cardNumber);
    free(student->surName);
    free(student->firstName);
    free(student->faculty);
    free(student->speciality);
}

void freeStudentsDatabase(DBStudent_t *students_db) {
    for (int i = 0; i < students_db->studentsNumber; ++i)
        freeOneStudent(&students_db->studentsDatabase[i]);
    free(students_db->studentsDatabase);
}

void freeOneBorrow(Borrow_t *borrow) {
    free(borrow->cardNumber);
    free(borrow->returnTime);
}

void freeBorrowsDatabase(DBBorrow_t *books_db) {
    for (int i = 0; i < books_db->borrowsNumber; ++i)
        freeOneBorrow(&books_db->borrowsDatabase[i]);
    free(books_db->borrowsDatabase);
}


void rewriteUsersFile(DBUser_t user_db) {
    FILE *users_f = fopen(USERS_FILE, "w");

    for (int j = 0; j < user_db.usersNumber; ++j) {
        fprintf(users_f, "%s,%s,%d,%d",
                user_db.usersDatabase[j].login,
                user_db.usersDatabase[j].passHash,
                user_db.usersDatabase[j].booksRights,
                user_db.usersDatabase[j].studentsRights);
        if (j != user_db.usersNumber - 1)
            fprintf(users_f, "\n");
    }
    fclose(users_f);
}

void rewriteStudentsFile(DBStudent_t students_db) {
    FILE *students_f = fopen(STUDENTS_FILE, "w");

    for (int j = 0; j < students_db.studentsNumber; ++j) {
        fprintf(students_f, "%s,%s,%s,%s,%s",
                students_db.studentsDatabase[j].cardNumber,
                students_db.studentsDatabase[j].firstName,
                students_db.studentsDatabase[j].surName,
                students_db.studentsDatabase[j].faculty,
                students_db.studentsDatabase[j].speciality);
        if (j != students_db.studentsNumber - 1)
            fprintf(students_f, "\n");
    }
    fclose(students_f);
}


void rewriteBooksFile(DBBook_t books_db) {
    FILE *books_f = fopen(BOOKS_FILE, "w");

    for (int j = 0; j < books_db.booksNumber; ++j) {
        fprintf(books_f, "%d,%s,%s,%d,%d",
                books_db.booksDatabase[j].ISBN,
                books_db.booksDatabase[j].author,
                books_db.booksDatabase[j].bookName,
                books_db.booksDatabase[j].maxAmount,
                books_db.booksDatabase[j].currAmount);
        if (j != books_db.booksNumber - 1)
            fprintf(books_f, "\n");
    }
    fclose(books_f);
}

void rewriteBorrowsFile(DBBorrow_t borrows_db) {
    FILE *borrows_f = fopen(BORROWS_FILE, "w");

    for (int j = 0; j < borrows_db.borrowsNumber; ++j) {
        fprintf(borrows_f, "%d,%s,%s",
                borrows_db.borrowsDatabase[j].ISBN,
                borrows_db.borrowsDatabase[j].cardNumber,
                borrows_db.borrowsDatabase[j].returnTime);
        if (j != borrows_db.borrowsNumber - 1)
            fprintf(borrows_f, "\n");
    }
    fclose(borrows_f);
}
