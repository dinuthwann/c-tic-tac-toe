#include <stdio.h>
#include <stdlib.h> // Clear screen (system) සඳහා

// Declare a 3x3 array for the game board
char board[3][3];

// Reset the board array back to numbers 1-9
void resetBoard() {
    char count = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = count++;
        }
    }
}

// Function to clear screen and print the game board
void printBoard() {
    // Clear screen based on OS
    #ifdef _WIN32
        system("cls");   // Windows
    #else
        system("clear"); // Linux/Mac
    #endif

    printf("--- TIC TAC TOE (XOXO) GAME ---\n\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// Check the availability of the move
int isValidMove(int choice) {
    if (choice < 1 || choice > 9) return 0; // 1-9 valid, otherwise invalid
    
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        return 1; // Valid Move
    }
    return 0; // Invalid Move (position already taken)
}

void makeMove(int choice, char symbol) {
    int row = (choice - 1) / 3; // Calculate row index
    int col = (choice - 1) % 3; // Calculate column index
    
    board[row][col] = symbol;   // Place 'X' or 'O'
}

// Check whether the player has won or not
int checkWin() {
    // 1. Check rows 
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
    }
    // 2. Check columns 
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    // 3. Check diagonals 
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0; 
}

int main() {
    char playAgain;

    // Do-while loop to repeat the entire game if players want
    do {
        resetBoard(); // Reset board to numbers 1-9 for every new game
        
        int choice;
        int player = 1;     // 1 = Player 1 ('X'), 2 = Player 2 ('O')
        int totalMoves = 0; // Tracks valid moves played
        int gameWon = 0;    // Flag to check if game is won
        char symbol;

        // Loop until someone wins or max 9 moves are played
        while (totalMoves < 9 && !gameWon) {
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

            // Check if current move resulted in a win
            if (checkWin()) {
                gameWon = 1;
                printBoard();
                printf("🎉 Congratulations! Player %d (%c) Wins!\n", player, symbol);
                break;
            }

            // Change player
            player = (player == 1) ? 2 : 1;
        }

        // If no one won and 9 moves played, it's a draw
        if (!gameWon && totalMoves == 9) {
            printBoard();
            printf("🤝 Game Draw! Better luck next time.\n");
        }

        // Ask if players want to restart the game
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\nThanks for playing! Goodbye 👋\n");
    return 0;
}