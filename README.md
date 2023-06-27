# bigHW

/*  Here's how database structure looks like:
 *
 *                      __________________
 *                     |    DBAdmin      |
 *                     ------------------
 *                    |         |       \
 *                 |            |        \
 *               v              v         v
 *      ________          ___________     __________            ________
 *     | DBBook |        | DBStudent |   | DBBorrow |          | DBUser |
 *     --------          ------------    -----------           --------
 *     |      |           |         |     |         |            |     |
 *    |        |         |          |    |          |           |       |
 *   V          V       V           V    V          V          V        V
*   _______  ________
*  |Number| |Database|      SAME            SAME                SAME
*  -------- ----------
 *               |
 *              |
 *             V
 *         ___________
 *        |properties|
 *        -----------
 *
 *  Check "menuFile.h" for better understanding
 *
 * */

//  Login: boss
//  Password: qwerty
//
//  Login: books
//  Password: Book12345
//
//  Login: students
//  Password: Student12345
