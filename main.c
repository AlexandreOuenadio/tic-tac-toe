#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//GLOBAL VARIABLE
char board[3][3]; //3x3 board
const char PLAYER = 'X';
const char COMPUTER = 'O';
int clearInputBuffer;

//SIGNATURES
void resetBoard();
void printBoard();
int  checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);




int main(){

    char winner = ' ';
    char response;

    do{
        printf("----- GAME STARTS! -----\n");
        //RESET BOARD & WINNER
        winner = ' ';
        resetBoard();

        while(winner == ' ' && checkFreeSpaces() != 0){
            printBoard();
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0){
                break;
            }
            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0){
                break;
            }   
        }

        printBoard();
        printWinner(winner);
        do{
            printf("Do you want to play again? (Y/N)\n");
            
            scanf("%c", &response);
            response = toupper(response);
            printf("Your answer: %c\n", response);

            if (response != 'Y' && response != 'N' ){
                printf("Invalid answer!\n");
            }


        }while(response != 'Y' && response != 'N');
        
        
    }while(response == 'Y');

    printf("GOODBYE...\n");
    

    return 0;
}


void resetBoard(){

    for (int row = 0; row < 3; row++){
        for (int column = 0; column < 3; column++){
            board[row][column] = ' ';
        }
    }

}

void printBoard(){

    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");

} 

int  checkFreeSpaces(){

    int freeSpaces = 9;

    for (int row = 0; row < 3; row++){
        for (int column = 0; column < 3; column++){
            if (board[row][column] != ' '){
                freeSpaces--;
            }
        }
    }
    return freeSpaces;

}

void playerMove(){

    int x, y;

    do{

        printf("Enter row #(1-3): \n");
        scanf("%d", &x);
        x--; //get index

        // ---- CLEAR INPUT BUFFER TO PREVENT \n FROM SKIPPING USER ANSWER ---- 
        while ( (clearInputBuffer = getchar()) != '\n' && clearInputBuffer != EOF ) { }
        // -----

        printf("Enter column #(1-3): \n");
        scanf("%d", &y);
        y--;

        // ---- CLEAR INPUT BUFFER TO PREVENT \n FROM SKIPPING USER ANSWER ---- 
        while ( (clearInputBuffer = getchar()) != '\n' && clearInputBuffer != EOF ) { }
        // -----

        if (!(x <= 2 && x >= 0) || !(y <= 2 && y >= 0)){
            printf("Invalid coordinates!\n");
            continue;
        }

        if (board[x][y] != ' '){
            printf("Invalid move!\n");
        }else{
            board[x][y] = PLAYER;
            break;
        }

    }while(!(x <= 2 && x >= 0) || !(y <= 2 && y >= 0) || board[x][y] != ' ');

}    

    
void computerMove(){
 
    
    int x, y;
    
    srand(time(0));

    if (checkFreeSpaces() > 0){
        do{
            x = rand() % 3;
            y = rand() % 3;

        }while(board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }else{
        printWinner(' ');
    }

}
char checkWinner(){

    //check rows
    for (int row = 0; row < 3; row++){
        if (board[row][0] == board[row][1] && board[row][0] == board[row][2]){
            return board[row][0];
        }
    }
    //check columns
    for (int column = 0; column < 3; column++){
        if (board[0][column] == board[1][column] && board[0][column] == board[2][column]){
            return board[0][column];
        }
    }

    //check diagonal
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }
    //check antidiagonal
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[0][2];
    }

    return ' ';

}


void printWinner(char winner){

    if (winner == PLAYER){
        printf("YOU WIN!\n");
    }else if (winner == COMPUTER){
        printf("YOU LOSE!\n");
    }else{
        printf("IT'S A DRAW!\n");
    }

}