#include <stdio.h>
#include <stdlib.h> // For system() and rand()
#include <string.h>
#include <time.h>   // For time() and srand()

#ifdef _WIN32
    #include <windows.h> // Windows Beep sound
#endif

// Sound functions for moves and game win
void playMoveSound() {
    #ifdef _WIN32
        Beep(750, 100);
    #else
        printf("\a");
        fflush(stdout);
    #endif
}

void playWinSound() {
    #ifdef _WIN32
        Beep(1000, 200);
        Beep(1200, 300);
    #else
        printf("\a\a\a");
        fflush(stdout);
    #endif
}

// Declare a 3x3 array for the game board
char board[3][3];

// Player names
char player1Name[30];
char player2Name[30];

// Score tracking variables
int player1Wins = 0;
int player2Wins = 0;
int draws = 0;

// Game Settings
int gameMode = 1;   // 1 = Two Players, 2 = Single Player
int difficulty = 1; // 1 = Easy, 2 = Hard

// Save match summary to a text file
void saveGameHistory(const char *resultMessage) {
    FILE *file = fopen("game_history.txt", "a");
    if (file == NULL) {
        return; // Failed to open file
    }

    time_t now = time(NULL);
    char *timeStr = ctime(&now);
    timeStr[strlen(timeStr) - 1] = '\0'; // Remove newline character from time string

    fprintf(file, "[%s] Mode: %s | %s (%d) vs %s (%d) | Draws: %d | Result: %s\n",
            timeStr,
            (gameMode == 1) ? "2 Players" : (difficulty == 1 ? "vs AI (Easy)" : "vs AI (Hard)"),
            player1Name, player1Wins,
            player2Name, player2Wins,
            draws,
            resultMessage);

    fclose(file);
}

// Display past match history from text file
void viewGameHistory() {
    FILE *file = fopen("game_history.txt", "r");
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("=====================================================\n");
    printf("                 MATCH HISTORY LOG                   \n");
    printf("=====================================================\n\n");

    if (file == NULL) {
        printf("No match history found yet.\n");
    } else {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }

    printf("\nPress Enter to return to main menu...");
    getchar(); // Clear buffer
    getchar(); // Wait for user enter key
}

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
    #ifdef _WIN32
        system("cls");   // Windows
    #else
        system("clear"); // Linux/Mac
    #endif

    printf("=====================================================\n");
    printf("              TIC TAC TOE (XOXO) GAME                \n");
    printf("=====================================================\n");
    printf(" SCORE: %s (X): %d | %s (O): %d | Draws: %d\n", player1Name, player1Wins, player2Name, player2Wins, draws);
    printf("=====================================================\n\n");

    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[0][0], board[2][1], board[2][2]);
    printf("\n");
}

// Check if the selected position is valid and available
int isValidMove(int choice) {
    if (choice < 1 || choice > 9) return 0;
    
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        return 1;
    }
    return 0;
}

// Update board array with current player's symbol
void makeMove(int choice, char symbol) {
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    
    board[row][col] = symbol;
    playMoveSound();
}

// Check whether the current move results in a win
int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0;
}

// Easy Mode Random Move
int getRandomComputerMove() {
    int choice;
    do {
        choice = (rand() % 9) + 1;
    } while (!isValidMove(choice));
    return choice;
}

// Hard Mode Smart AI Move
int getSmartComputerMove() {
    // 1. Winning move check
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(i)) {
            makeMove(i, 'O');
            if (checkWin()) {
                int row = (i - 1) / 3;
                int col = (i - 1) % 3;
                board[row][col] = '1' + (i - 1);
                return i;
            }
            int row = (i - 1) / 3;
            int col = (i - 1) % 3;
            board[row][col] = '1' + (i - 1);
        }
    }

    // 2. Block human player move check
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(i)) {
            makeMove(i, 'X');
            if (checkWin()) {
                int row = (i - 1) / 3;
                int col = (i - 1) % 3;
                board[row][col] = '1' + (i - 1);
                return i;
            }
            int row = (i - 1) / 3;
            int col = (i - 1) % 3;
            board[row][col] = '1' + (i - 1);
        }
    }

    // 3. Take center if available
    if (isValidMove(5)) return 5;

    // 4. Fallback to random move
    return getRandomComputerMove();
}

int main() {
    char playAgain;
    int mainChoice;
    srand(time(NULL));

    while (1) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("=====================================================\n");
        printf("              TIC TAC TOE (XOXO) GAME                \n");
        printf("=====================================================\n");
        printf("1. Two Players (Human vs Human)\n");
        printf("2. Single Player (Human vs Computer)\n");
        printf("3. View Match History\n");
        printf("4. Exit\n");
        printf("Enter choice (1-4): ");
        scanf("%d", &mainChoice);

        if (mainChoice == 3) {
            viewGameHistory();
            continue;
        } else if (mainChoice == 4) {
            printf("Thanks for playing! Goodbye 👋\n");
            break;
        } else if (mainChoice != 1 && mainChoice != 2) {
            continue;
        }

        gameMode = mainChoice;

        // Reset wins count for a new session
        player1Wins = 0;
        player2Wins = 0;
        draws = 0;

        if (gameMode == 2) {
            printf("\nSelect AI Difficulty:\n");
            printf("1. Easy\n");
            printf("2. Hard (Smart AI)\n");
            printf("Enter choice (1 or 2): ");
            scanf("%d", &difficulty);

            printf("\nEnter Your Name (X): ");
            scanf("%29s", player1Name);
            strcpy(player2Name, "Computer");
        } else {
            printf("\nEnter Player 1 Name (X): ");
            scanf("%29s", player1Name);
            printf("Enter Player 2 Name (O): ");
            scanf("%29s", player2Name);
        }

        // Gameplay loop
        do {
            resetBoard();
            
            int choice;
            int player = 1;
            int totalMoves = 0;
            int gameWon = 0;
            char symbol;
            char *currentTurnName;
            char resultMsg[100];

            while (totalMoves < 9 && !gameWon) {
                printBoard();

                symbol = (player == 1) ? 'X' : 'O';
                currentTurnName = (player == 1) ? player1Name : player2Name;

                if (player == 2 && gameMode == 2) {
                    printf("Computer is thinking...\n");
                    if (difficulty == 2) {
                        choice = getSmartComputerMove();
                    } else {
                        choice = getRandomComputerMove();
                    }
                } else {
                    printf("%s (%c), enter a position (1-9): ", currentTurnName, symbol);
                    scanf("%d", &choice);

                    while (!isValidMove(choice)) {
                        printf("Invalid move! Try again (1-9): ");
                        scanf("%d", &choice);
                    }
                }

                makeMove(choice, symbol);
                totalMoves++;

                if (checkWin()) {
                    gameWon = 1;
                    playWinSound();
                    
                    if (player == 1) player1Wins++;
                    else player2Wins++;

                    printBoard();
                    printf("🎉 Congratulations! %s (%c) Wins!\n", currentTurnName, symbol);
                    
                    snprintf(resultMsg, sizeof(resultMsg), "%s Won", currentTurnName);
                    saveGameHistory(resultMsg);
                    break;
                }

                player = (player == 1) ? 2 : 1;
            }

            if (!gameWon && totalMoves == 9) {
                draws++;
                printBoard();
                printf("🤝 Game Draw! Better luck next time.\n");
                
                saveGameHistory("Draw");
            }

            printf("\nDo you want to play another round in this session? (y/n): ");
            scanf(" %c", &playAgain);

        } while (playAgain == 'y' || playAgain == 'Y');
    }

    return 0;
}