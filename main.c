/*
 * File:        project_reversi.c
 * Author:      APS105H
 * Modified by: Eri Yoshida
 *
 * Date: 		Mar28 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// =========   Function declaration  ==========
/*
 * Function:  convertToNumber 
 * --------------------
 * converts alphabet into number, both of which are used for board coordinates
 */

int convertToNumber(char alphabet){
    //ascii of 'a' is 97
    int result = alphabet - 'a';
    return result;
}

// ========= Function implementation ==========
/*
 * Function:  printBoard 
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[][26], int n) {
    //print the first line
    printf("  ");
    char xAxis = 'a';
    for(int i = 0; i < n; i++){
        printf("%c", xAxis + i);
    }
    printf("\n");

    //print the y-axis and the board
    char yAxis = 'a';

    for(int r = 0; r < n; r++){
        printf("%c ", yAxis + r);
        for(int c = 0; c < n; c++){
            printf("%c", board[r][c]);
        }
        printf("\n");
    }
}

/*
 * Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col) {
    return (row >= 0 && col >= 0 && row < n && col < n);
}

/*
 * Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 */
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {

    //the move is legal if and only if the location is within bound
    //AND if the opposite colour is next to the location
    //AND opposite colour continues (must be withinbound)
    //UNTIL the same colour is in the same direction, which also has to be withinbound


    //if the input location is not in bound
    if(!positionInBounds(n, row, col)){
        return false;
    }
        //if the location is already occupied
    else if(board[row][col] != 'U'){
        return false;

        //if all above criteria are met
    }else{

        int r = row + deltaRow;
        int c = col + deltaCol;


        for(int iterations = 0; iterations < n; iterations++){

            //1. if the selected coordinate is not within bound, then false, invalid
            if(!positionInBounds(n, r, c)){
                return false;
            }
                //2. if the selected tile is vacant, then it is invalid
            else if(board[r][c] == 'U'){
                return false;
            }
                //3. if the colour in that location is the same as your colour
            else if(board[r][c] == colour){

                //if colour directly next to each other is the same, then false;, invalid
                if(iterations == 0){
                    return false;

                    //return true if it isn't a first iteration
                }else{
                    return true;
                }
            }

            //4. if the selected coordinate is the opponent colour, continue the for loop
            r += deltaRow;
            c += deltaCol;
        }
    }
    return true;

}

/*
 * Function:  updateBoard 
 * --------------------
 * updates the tile with given coordinate and the colour,
 * and also checks for additional changes due to the update.
 * Note, this function will be used for the initial configuration changes
 */

void updateBoard(char board[][26], int n, char colour, int row, int col){

    int checkRow = 0;
    int checkCol = 0;
    //checks for the valid direction
    for(int northSouth = -1; northSouth <= 1; northSouth++){
        for(int eastWest = -1; eastWest <= 1; eastWest++){

            //for the valid direction until hit the same coloured tile
            if(checkLegalInDirection(board, n, row, col, colour, northSouth, eastWest)){

                //resetting the test variable
                checkRow = row;
                checkCol = col;

                while(1){

                    //move onto the next tile in the same direction
                    checkRow = checkRow + northSouth;
                    checkCol = checkCol + eastWest;

                    //breaks the loop if the next tile is the same as the user colour
                    if(board[checkRow][checkCol] == colour){
                        break;
                    }

                    //assigns the new colour
                    board[checkRow][checkCol] = colour;
                }
            }
        }
    }board[row][col] = colour;
}

/*
 * Function:  checkIfValid 
 * --------------------
 * checks whether the move is valid in all direction
 * then return bool if any direction was valid
 */
bool checkIfValid(char board[][26], int n, int row, int col, char colour){

    int success = 0;
    //looping through all direction
    for(int northSouth = -1; northSouth <= 1; northSouth++){
        for(int eastWest = -1; eastWest <= 1; eastWest++){
            if(checkLegalInDirection(board, n, row, col, colour, northSouth, eastWest) == 1){
                success++;
            }
        }
    }

    if(success > 0){
        return true;
    }else return false;
}


/*
 * Function:  printAllAvailableMoves 
 * --------------------
 * using function checkIfValid(),
 * it scans the entire board for any valid move 
 */
void printAllAvailableMoves(char board[][26], int n, char colour){
    //looping through all tiles in the board
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(checkIfValid(board, n, row, col, colour)){
                printf("%c%c\n", row+'a', col+'a');
            }
        }
    }
}

/*
 * Function:  findOpponent 
 * --------------------
 * the function will return the opponent
 */
char findOpponent(char turn){
    if(turn == 'W'){
        return 'B';
    }else{
        return 'W';
    }
}

/*
 * Function:  moveAvailable 
 * --------------------
 * return bool whether more moves are available for the colour
 */
bool moveAvailable(char board[][26], int n, char colour){
    int available = 0;

    //looping through all tiles in the board
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(checkIfValid(board, n, row, col, colour)){
                available++;
            }
        }
    }

    if(available>0){
        return true;
    }else{
        return false;
    }
}

/*
 * Function:  numMovesAvailable 
 * --------------------
 * return the number of moves available for the colour
 */
int numMovesAvailable(char board[][26], int n, char colour){
    int available = 0;

    //looping through all tiles in the board
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(checkIfValid(board, n, row, col, colour)){
                available++;
            }
        }
    }

    return available;
}

/*
 * Function:  calculateScore 
 * --------------------
 * this function returns the total number of tiles flipped
 * according to the current board and the row/col configuration
 */
int calculateScore(char board[][26], int n, char colour, int row, int col){

    int score = 0;
    int checkRow = 0;
    int checkCol = 0;

    if(row == col && (row == 0 || col == n-1)){
        score += 10;
        //printf("adding score is 10\n");
        //top right or bottom left corner
    }else if((row == 0 && col == n-1) || (row == n-1 && col == 0)){
        score += 10;
        //printf("adding score is 10\n");
    }else if(row == 0 || col == 0 || row == n-1 || col == n-1){
        score += 5;
        //printf("adding score is 5\n");
    }else{
        score ++;
        //printf("adding score is 1\n");

    }

    //checks for the valid direction
    for(int northSouth = -1; northSouth <= 1; northSouth++){
        for(int eastWest = -1; eastWest <= 1; eastWest++){

            //for the valid direction until hit the same coloured tile
            if(checkLegalInDirection(board, n, row, col, colour, northSouth, eastWest)){

                //resetting the test variable
                checkRow = row;
                checkCol = col;

                while(1){

                    //move onto the next tile in the same direction
                    checkRow = checkRow + northSouth;
                    checkCol = checkCol + eastWest;

                    //breaks the loop if the next tile is the same as the user colour
                    if(board[checkRow][checkCol] == colour){
                        break;
                    }

                    //increment the score according to its respective weight
                    //top left or bottom right corner
                    if(checkRow == checkCol && (checkCol == 0 || checkCol == n-1)){
                        score += 10;
                        //printf("adding score is 10\n");
                        //top right or bottom left corner
                    }else if((checkRow == 0 && checkCol == n-1) || (checkRow == n-1 && checkCol == 0)){
                        score += 10;
                        //printf("adding score is 10\n");
                    }else if(checkRow == 0 || checkCol == 0 || checkRow == n-1 || checkCol == n-1){
                        score += 5;
                        //printf("adding score is 5\n");
                    }else{
                        score ++;
                        //printf("adding score is 1\n");

                    }
                }
            }
        }
    }

    score = score * (n*n - numMovesAvailable(board, n, findOpponent(colour)));

    return score;
}

/*
 * Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {

    int tempScore = 0;
    int score = 0;
    char tempBoard[26][26];

    //creating a copy of the current board
    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
            tempBoard[r][c] = board[r][c];
        }
    }

    //looping through all possible valid (row, col) configurations
    for(int checkRow = 0; checkRow < n; checkRow++){
        for(int checkCol = 0; checkCol < n; checkCol++){
            if(checkIfValid(tempBoard, n, checkRow, checkCol, turn)){

                tempScore = calculateScore(tempBoard, n, turn, checkRow, checkCol);

                //updating row, col if the tempScore is greater than the previous scores
                if(score < tempScore){
                    score = tempScore;
                    *row = checkRow;
                    *col = checkCol;
                }

                //printf("current configuration: %c%c, current score: %d, total score: %d\n", checkRow+'a', checkCol+'a', tempScore, score); //debug
            }
        }
    }
    return 0;
}

/*
 * Function:  printWinner
 * --------------------
 * this function is called at the end of the game by calculating the winner
 */
void printWinner(char board[][26], int n){
    int white = 0;
    int black = 0;

    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){

            //accumulating the black tiles
            if(board[r][c] == 'B'){
                black++;
            }

            //accumulating the white tiles
            if(board[r][c] == 'W'){
                white++;
            }
        }
    }

    if (white == black){
        printf("Draw!");
    }else{
        printf("%c player wins.", white>black ? 'W' : 'B');
    }
}



#ifndef COMPETE_MODE
int main(void) {

    int n = 0;
    char compColour = 'B';
    char turn = 'B';
    //char configuration[3];
    bool gameOver = false;


    //get initial inputs from user for presets of the game
    printf("Enter the board dimension: ");
    scanf("%d", &n);
    fflush(stdin);

    printf("Computer plays (B/W) : ");
    scanf(" %c", &compColour);
    fflush(stdin);


    //initialize the board using char array
    char board[26][26];
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            board[row][col] = 'U';
            if((row == (n-1)/2 && row == col) || (row == n/2 && row == col)){
                board[row][col] = 'W';
            }else if((row == (n-1)/2 && row == col - 1)|| (row == n/2 && row == col + 1)){
                board[row][col] = 'B';
            }

        }
    }


    char charRow = 'a';
    char charCol = 'a';
    char coordinate[3];
    int row = 0;
    int col = 0;

    printBoard(board, n);

    while(!gameOver){

        //computer's turn
        if(turn == compColour){

            //retrieve the best row/col configuration with the given algorithm
            //note, makeMove is only to change to valid row, col
            makeMove(board, n, turn, &row, &col);
            updateBoard(board, n, turn, row, col);

            printf("Computer places %c at %c%c.\n", turn, row + 'a', col + 'a');

            //human's turn
        }else{

            //receive the desired move configuration
            printf("Enter move for colour %c (RowCol): ", turn);
            scanf("%s", coordinate);

            charRow = coordinate[0];
            charCol = coordinate[1];


            //flip board if the input is valid
            row = convertToNumber(charRow);
            col = convertToNumber(charCol);

            //printf("row: %c, col: %c", charRow, charCol);

            if(checkIfValid(board, n, row, col, turn)){
                updateBoard(board, n, turn, row, col);

                //if input not valid, then terminate the game
            }else{
                printf("Invalid move.\n");
                printWinner(board, n);
                gameOver = true;

            }
        }

        //after the flip has been made, the switch turn or terminate
        if(!gameOver){
            //if the opponent has moved, then switch turns
            if(moveAvailable(board, n, findOpponent(turn))){
                turn = findOpponent(turn);
                printBoard(board, n);


                //if the opponent doesn't have more turn, and you do
            }else if(moveAvailable(board, n, turn)){
                printBoard(board, n);
                printf("%c player has no valid move.\n", findOpponent(turn));

                //if no one has more turns
            }else{
                printBoard(board, n);
                printWinner(board, n);
                gameOver = true;
            }
        }
    }

    return 0;
}
#endif