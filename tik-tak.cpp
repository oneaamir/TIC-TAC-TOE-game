#include <iostream>
#include <ctime>

void drawBoard(const char spaces[]);
void playerMove(char spaces[], char player);
void computerMove(char spaces[], char computer);
bool checkWinner(const char spaces[], char player, char computer);
bool checkTie(const char spaces[]);

int main() {
    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player = 'X';
    char computer = 'O';
    bool gameRunning = true;

    drawBoard(spaces);

    while (gameRunning) {
        playerMove(spaces, player);
        drawBoard(spaces);

        if (checkWinner(spaces, player, computer) || checkTie(spaces)) {
            gameRunning = false;
            break;
        }

        computerMove(spaces, computer);
        drawBoard(spaces);

        if (checkWinner(spaces, player, computer) || checkTie(spaces)) {
            gameRunning = false;
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}

void drawBoard(const char spaces[]) {
    std::cout << '\n';
    for (int i = 0; i < 9; i += 3) {
        std::cout << "     |     |     \n";
        std::cout << "  " << spaces[i] << "  |  " << spaces[i + 1] << "  |  " << spaces[i + 2] << "  \n";
        if (i < 6) std::cout << "_____|_____|_____\n";
    }
    std::cout << "     |     |     \n\n";
}

void playerMove(char spaces[], char player) {
    int move;
    do {
        std::cout << "Enter a spot to place a marker (1-9): ";
        std::cin >> move;
        move--;
        if (move >= 0 && move < 9 && spaces[move] == ' ') {
            spaces[move] = player;
            break;
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    } while (true);
}

void computerMove(char spaces[], char computer) {
    srand(static_cast<unsigned int>(time(0)));
    int move;
    while (true) {
        move = rand() % 9;
        if (spaces[move] == ' ') {
            spaces[move] = computer;
            break;
        }
    }
}

bool checkWinner(const char spaces[], char player, char computer) {
    const int winConditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };

    for (const auto& condition : winConditions) {
        if (spaces[condition[0]] != ' ' && spaces[condition[0]] == spaces[condition[1]] && spaces[condition[1]] == spaces[condition[2]]) {
            if (spaces[condition[0]] == player) {
                std::cout << "YOU WIN!\n";
            } else {
                std::cout << "YOU LOSE!\n";
            }
            return true;
        }
    }
    return false;
}

bool checkTie(const char spaces[]) {
    for (int i = 0; i < 9; ++i) {
        if (spaces[i] == ' ') return false;
    }
    std::cout << "IT'S A TIE!\n";
    return true;
}
