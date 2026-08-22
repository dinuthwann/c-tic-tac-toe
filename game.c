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
// check the avilability
int isValidMove(int choice) {
    if (choice < 1 || choice > 9) return 0; // 1-9 valid otherwise Invalid
    
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        return 1; // Valid Move
    }
    return 0; // Invalid Move (කලින් දාපු එකක්)
}
void makeMove(int choice, char symbol) {
    int row = (choice - 1) / 3; // Search the row through the number
    int col = (choice - 1) % 3; // Search the Column through the number
    
    board[row][col] = symbol;   // Add the  'X' or 'O' 
}
  
// Check whether the player has won or not
int checkWin() {
    // 1. check rows 
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
    }
    // 2. Check columns 
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    // 3. Check the diagonals 
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0; 
}

int main() {
    int choice;
    int player = 1; // 1 = Player 1 ('X'), 2 = Player 2 ('O')
    int totalMoves = 0; 
    int gameWon = 0;    
    char symbol;

    // simply test the 5 times
    for (int turn = 0; turn < 5; turn++) {
        printBoard();

        symbol = (player == 1) ? 'X' : 'O';
        printf("Player %d (%c), enter a position (1-9): ", player, symbol);
        scanf("%d", &choice);

        // Loop until a valid move is provided
        while (!isValidMove(choice)) {
            printf("Invalid move! Try again (1-9): ");
            scanf("%d", &choice);
        }

        makeMove(choice, symbol);
        totalMoves++;

        if (checkWin()) {
            gameWon = 1;
            printBoard();
            printf(" Congratulations! Player %d (%c) Wins!\n", player, symbol);
            break;
        }

        // change the player 
        player = (player == 1) ? 2 : 1;
    }

    // If no one can win, it's a draw
    if (!gameWon && totalMoves == 9) {
        printBoard();
        printf(" Game Draw! Better luck next time.\n");
    }

    return 0;
}