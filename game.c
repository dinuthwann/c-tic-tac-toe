//tix tac toe

#include <stdio.h>
#include <stdlib.h> // For system() and rand()
#include <string.h>
#include <time.h>   // For srand()

// Declare a 3x3 array for the game board
char board[3][3];

// Player names
char player1Name[30];
char player2Name[30];

// Score tracking variables
int player1Wins = 0;
int player2Wins = 0;
int draws = 0;

// Game Mode: 1 = Two Players (Human vs Human), 2 = Single Player (Human vs Computer)
int gameMode = 1;

// Reset the board array back to numbers '1' through '9'
void resetBoard() {
    char count = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = count++;
        }
    }
}

// Function to clear the screen and display the game board with scoreboard
void printBoard() {
    // Clear screen based on Operating System
    #ifdef _WIN32
        system("cls");   // Windows
    #else
        system("clear"); // Linux/Mac
    #endif

    printf("=====================================================\n");
    printf("              TIC TAC TOE (XOXO) GAME                \n");
    printf("=====================================================\n");
    // Display updated scoreboard with player names
    printf(" SCORE: %s (X): %d | %s (O): %d | Draws: %d\n", player1Name, player1Wins, player2Name, player2Wins, draws);
    printf("=====================================================\n\n");

    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// Check if the selected position is valid and available
int isValidMove(int choice) {
    if (choice < 1 || choice > 9) return 0; // Return invalid if choice is outside range 1-9
    
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    
    // Check if position is not already marked by 'X' or 'O'
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        return 1; // Valid Move
    }
    return 0; // Invalid Move (position already taken)
}

// Update board array with current player's symbol
void makeMove(int choice, char symbol) {
    int row = (choice - 1) / 3; // Calculate row index
    int col = (choice - 1) % 3; // Calculate column index
    
    board[row][col] = symbol;   // Place 'X' or 'O'
}

// Generate a random valid move for the Computer opponent
int getComputerMove() {
    int choice;
    do {
        choice = (rand() % 9) + 1; // Generate random number between 1 and 9
    } while (!isValidMove(choice));
    return choice;
}

// Check whether the current move results in a win
int checkWin() {
    // 1. Check rows for matching symbols
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
    }
    // 2. Check columns for matching symbols
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    // 3. Check both diagonals for matching symbols
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0; // No winner yet
}

int main() {
    char playAgain;
    srand(time(NULL)); // Initialize random seed for computer moves

    // Prompt user to select game mode
    printf("Select Game Mode:\n");
    printf("1. Two Players (Human vs Human)\n");
    printf("2. Single Player (Human vs Computer)\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &gameMode);

    // Set player names based on selected mode
    if (gameMode == 2) {
        printf("Enter Your Name (X): ");
        scanf("%29s", player1Name);
        strcpy(player2Name, "Computer");
    } else {
        printf("Enter Player 1 Name (X): ");
        scanf("%29s", player1Name);
        printf("Enter Player 2 Name (O): ");
        scanf("%29s", player2Name);
    }

    // Main game loop allowing repeated rounds
    do {
        resetBoard(); // Reset board array for new round
        
        int choice;
        int player = 1;     // 1 = Player 1 ('X'), 2 = Player 2 ('O')
        int totalMoves = 0; // Count valid moves played
        int gameWon = 0;    // Status flag for win condition
        char symbol;
        char *currentTurnName;

        // Loop until a player wins or 9 moves are completed
        while (totalMoves < 9 && !gameWon) {
            printBoard();

            symbol = (player == 1) ? 'X' : 'O';
            currentTurnName = (player == 1) ? player1Name : player2Name;

            // Handle turn execution for Human vs Computer logic
            if (player == 2 && gameMode == 2) {
                printf("Computer is making a move...\n");
                choice = getComputerMove();
            } else {
                printf("%s (%c), enter a position (1-9): ", currentTurnName, symbol);
                scanf("%d", &choice);

                // Prompt until valid move position is entered
                while (!isValidMove(choice)) {
                    printf("Invalid move! Try again (1-9): ");
                    scanf("%d", &choice);
                }
            }

            makeMove(choice, symbol);
            totalMoves++;

            // Evaluate win condition
            if (checkWin()) {
                gameWon = 1;
                
                // Update persistent score tracking
                if (player == 1) player1Wins++;
                else player2Wins++;

                printBoard();
                printf("🎉 Congratulations! %s (%c) Wins!\n", currentTurnName, symbol);
                break;
            }

            // Switch current player turn
            player = (player == 1) ? 2 : 1;
        }

        // Handle game draw state
        if (!gameWon && totalMoves == 9) {
            draws++; // Increment draw count
            printBoard();
            printf(" Game Draw! Better luck next time.\n");
        }

        // Prompt user for replay option
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    // Display final score summary on exit
    printf("\nFinal Scores:\n");
    printf("%s Wins: %d | %s Wins: %d | Draws: %d\n", player1Name, player1Wins, player2Name, player2Wins, draws);
    printf("Thanks for playing! Goodbye \n");
    
    return 0;
}