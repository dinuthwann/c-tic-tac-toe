#include <stdio.h>

// Declare a 3x3 array for the game board
char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Function to print the game board
void printBoard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}
void makeMove(int choice, char symbol) {
    int row = (choice - 1) / 3; // Search the row through the number
    int col = (choice - 1) % 3; // Search the Column through the number
    
    board[row][col] = symbol;   // Add the  'X' or 'O' 
}
int main() {
    int choice;
    printf("--- TIC TAC TOE (XOXO) GAME ---\n");
    printBoard();
    
    // Get the input from the player and change the board
    printf("Player 1, enter a position (1-9): ");
    scanf("%d", &choice);

    makeMove(choice, 'X');
    // Display the board
    printBoard();

    return 0;
}