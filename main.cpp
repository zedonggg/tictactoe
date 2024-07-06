#include <iostream>
#include <vector>
#include <algorithm>

class Board {
    std::vector<std::vector<char>> playing_board = { 
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'} };
    
    bool check_char_won(char c) {
        int i;
        for (i = 0; i < 3; ++i) {
            if (playing_board[i][0] == c && playing_board[i][1] == c && playing_board[i][2] == c) return true;
            if (playing_board[0][i] == c && playing_board[1][i] == c && playing_board[2][i] == c) return true;
        }

        if (playing_board[0][0] == c && playing_board[1][1] == c && playing_board[2][2] == c) return true;
        if (playing_board[0][2] == c && playing_board[1][1] == c && playing_board[2][0] == c) return true;

        return false;
    };

    public:
        bool player_turn;

        bool check_player_won() {
            return check_char_won('X');
        };

        bool check_com_won() {
            return check_char_won('O');
        };

        bool check_full() {
            for (int i{ 0 }; i < 3; ++i) {
                for (int j{ 0 }; j < 3; ++j) {
                    if (playing_board[i][j] == '-') return false;
                }
            }

            return true;
        }

        Board(bool player_turn) {
            this->player_turn = player_turn;
        }

        friend std::ostream& operator<<(std::ostream& output, const Board& b) {
            for (int i {0}; i < 3; ++i) {
                for (int j {0} ; j < 3; ++j) {
                    output << b.playing_board[i][j];
                    if (j < 2) {
                        output << '|';
                    }
                }
                output << '\n';
                if (i < 2) {
                    output << '-' << '-' << '-' << '-' << '-' << '\n';
                }    
            }

            return output;
        }

        bool check_empty(int r, int c) {
        return playing_board[r][c] == '-';
    }

    void set_box(int r, int c) {
        char player {};
        if (player_turn) {
            player = 'X';
        } else {
            player = 'O';
        }

        playing_board[r][c] = player;
        player_turn = !player_turn;
    }

    void unset_box(int r, int c) {
        playing_board[r][c] = '-';
    }
};

int minimax(Board& board, bool is_max, int depth) {
    if (board.check_com_won()) { return 10 - depth; };
    if (board.check_player_won()) { return depth - 10; };
    if (board.check_full()) { return 0; };

    int score {};
    int score_tmp {};
    int i {};
    int j {};

    if (is_max) {
        score = -1000;
        for (i = 0; i < 3; ++i) {
            for (j = 0; j < 3; ++j) {
                if (board.check_empty(i, j)) {
                    board.set_box(i, j);
                    score_tmp = minimax(board, !is_max, depth + 1);
                    board.unset_box(i, j);
                    score = std::max(score, score_tmp);
                }
            }
        }
        return score;
    } else {
        score = 1000;
        for (i = 0; i < 3; ++i) {
            for (j = 0; j < 3; ++j) {
                if (board.check_empty(i, j)) {
                    board.set_box(i, j);
                    score_tmp = minimax(board, !is_max, depth + 1);
                    board.unset_box(i, j);
                    score = std::min(score, score_tmp);
                }
            }
        }
        return score;
    }
}

std::vector<int> find_move(Board& board) {
    int score { -1000 };
    int tmp_score {};
    std::vector<int> best_move;
    for (int i { 0 }; i < 3; ++i) {
        for (int j {0}; j < 3; ++j) {
            if (board.check_empty(i, j)) {
                board.set_box(i, j);
                tmp_score = minimax(board, false, 0);
                board.unset_box(i, j);
                if (tmp_score > score) {
                    score = tmp_score;
                    best_move = {i, j};
                }
            }
        }
    }
    return best_move;
}

int main() {
    bool start_state {};

    std::cout << "Are you playing first? (true / false)";
    std::cin >> start_state;

    while (start_state != true && start_state != false) {
        std::cout << "Are you playing first? (true / false)";
        std::cin >> start_state;
    }

    std::cout << start_state;
    Board b = Board(start_state);
    std::cout << "Starting board\n" << b;
    std::cout << b.player_turn;

    int r{ 5 };
    int c{ 5 };
    while (!b.check_full()) {
        if (b.player_turn) {
            std::cout << "Player turn\n";
            //while ((r < 0 || r > 2) && (c < 0 || c > 2)) {
                std::cout << "Enter the row and column separated by a space";
                std::cin >> r >> c;
            //}

            if (!b.check_empty(r, c)) {
                std::cout << "Box is already occupied!\n";
                std::cout << "Enter the row and column separated by a space";
                std::cin >> r >> c;
            }

            b.set_box(r, c);
            std::cout << b;
            if (b.check_player_won()) {
                std::cout << "Player won!";
                break;
            }
        } else {
            std::cout << "Computer turn\n";
            std::vector<int> best_move = find_move(b);
            b.set_box(best_move[0], best_move[1]);
            std::cout << b;
            if (b.check_com_won()) {
                std::cout << "Computer won!";
                break;
            }
        }
    }
    std::cout << "Draw!";
    return 0;
}
