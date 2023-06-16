#include "menuFile.h"
#include "calcHash.h"

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

int main() {


    launcher();

    return 0;
}
