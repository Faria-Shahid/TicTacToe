#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
char currentPlayer = 'X';

void displayBoard() {
    cout << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i * 3 + j] << " ";
            if (j < 2) cout << "| ";
        }
        cout << endl;
        if (i < 2) cout << "----------" << endl;
    }
    cout << endl;
}

bool checkWin(char player) {
    int winConditions[8][3] = {
            {0,1,2}, {3,4,5}, {6,7,8},
            {0,3,6}, {1,4,7}, {2,5,8},
            {0,4,8}, {2,4,6}
    };
    for (auto &condition : winConditions) {
        if (board[condition[0]] == player &&
            board[condition[1]] == player &&
            board[condition[2]] == player) {
            return true;
        }
    }
    return false;
}

vector<int> getAvailableMoves() {
    vector<int> moves;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') moves.push_back(i);
    }
    return moves;
}

bool isGameOver() {
    return checkWin('X') || checkWin('O') || getAvailableMoves().empty();
}

int minimax(int depth, bool isMaximizing) {
    if (checkWin('O')) return 10 - depth;
    if (checkWin('X')) return depth - 10;
    if (getAvailableMoves().empty()) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int move : getAvailableMoves()) {
            board[move] = 'O';
            int score = minimax(depth + 1, false);
            board[move] = ' ';
            bestScore = max(bestScore, score);
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int move : getAvailableMoves()) {
            board[move] = 'X';
            int score = minimax(depth + 1, true);
            board[move] = ' ';
            bestScore = min(bestScore, score);
        }
        return bestScore;
    }
}

int minimaxAlphaBeta(int depth, bool isMaximizing, int alpha, int beta) {
    if (checkWin('O')) return 10 - depth;
    if (checkWin('X')) return depth - 10;
    if (getAvailableMoves().empty()) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int move : getAvailableMoves()) {
            board[move] = 'O';
            int score = minimaxAlphaBeta(depth + 1, false, alpha, beta);
            board[move] = ' ';
            bestScore = max(bestScore, score);
            alpha = max(alpha, bestScore);
            if (beta <= alpha) break;
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int move : getAvailableMoves()) {
            board[move] = 'X';
            int score = minimaxAlphaBeta(depth + 1, true, alpha, beta);
            board[move] = ' ';
            bestScore = min(bestScore, score);
            beta = min(beta, bestScore);
            if (beta <= alpha) break;
        }
        return bestScore;
    }
}

int getBestMoveMinimax() {
    int bestScore = 1000;
    int move = -1;
    for (int m : getAvailableMoves()) {
        board[m] = 'X';
        int score = minimax(0, true);
        board[m] = ' ';
        if (score < bestScore) {
            bestScore = score;
            move = m;
        }
    }
    return move;
}

int getBestMoveAlphaBeta() {
    int bestScore = -1000;
    int move = -1;
    for (int m : getAvailableMoves()) {
        board[m] = 'O';
        int score = minimaxAlphaBeta(0, false, -1000, 1000);
        board[m] = ' ';
        if (score > bestScore) {
            bestScore = score;
            move = m;
        }
    }
    return move;
}

void playerMove() {
    int move;
    cout << "Enter your move (1-9): ";
    cin >> move;
    move -= 1;
    if (move < 0 || move > 8 || board[move] != ' ') {
        cout << "Invalid move. Try again." << endl;
        playerMove();
    } else {
        board[move] = 'X';
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    displayBoard();

    while (!isGameOver()) {
        if (currentPlayer == 'X') {
            playerMove();
            currentPlayer = 'O';
        } else {
            int move = getBestMoveAlphaBeta();
            if (move != -1) board[move] = 'O';
            currentPlayer = 'X';
        }

        displayBoard();

        if (isGameOver()) {
            if (checkWin('X')) {
                cout << "X (Player) Wins!" << endl;
            } else if (checkWin('O')) {
                cout << "O (AI) Wins!" << endl;
            } else {
                cout << "It's a Draw!" << endl;
            }
        }
    }

    return 0;
}
