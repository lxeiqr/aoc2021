#include <iostream>
#include <vector>

const int GRID_W = 5, GRID_H = 5;

struct Board {
    int grid[GRID_W][GRID_H];
    bool marked[GRID_W][GRID_H];
    bool winner = false;
};

std::vector<int> gen_randoms(std::string s) {
    std::vector<int> res;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(",")) != std::string::npos) {
        token = s.substr(0, pos);
        res.push_back(std::stoi(token));

        s.erase(0, pos + 1);
    }

    res.push_back(std::stoi(s));

    return res;
}

Board read_board() {
    Board r;

    for(int j = 0; j < GRID_H; j++) {
        for(int i = 0; i < GRID_W; i++) {
            std::cin >> r.grid[i][j];
            r.marked[i][j] = false;
        }
    }

    return r;
}

void set_marked_if_found(Board &board, int random, int x, int y) {
    if(board.grid[x][y] == random)
        board.marked[x][y] = true;
}

void mark_numbers_board(Board& board, int random) {
    for(int j = 0; j < GRID_H; j++)
        for(int i = 0; i < GRID_W; i++)
            set_marked_if_found(board, random, i, j);
}

void mark_numbers(std::vector<Board>& boards, int random) {
    for(int i = 0; i < boards.size(); i++) {
        mark_numbers_board(boards[i], random);
    }
}

bool check_board(Board board) {
    // Check rows
    for(int j = 0; j < GRID_H; j++) {
        bool check = true;

        for(int i = 0; i < GRID_W; i++) {
            if(!board.marked[i][j])
                check = false;
        }

        if(check)
            return true;
    }

    // Check columns 
    for(int i = 0; i < GRID_W; i++) {
        bool check = true;

        for(int j = 0; j < GRID_H; j++) {
            if(!board.marked[i][j])
                check = false;
        }

        if(check)
            return true;
    }

    return false;
}

// -1 if not found
int find_new_last_winner(std::vector<Board>& boards) {
    int last = -1;

    for(int i = 0; i < boards.size(); i++) {
        if(check_board(boards[i]) && !boards[i].winner) {
            boards[i].winner = true;
            last = i;
        }
    }

    return last;
}

int unmarked_sum(Board b) {
    int sum = 0;

    for(int j = 0; j < GRID_H; j++) {
        for(int i = 0; i < GRID_W; i++) {
            if(!b.marked[i][j])
                sum += b.grid[i][j];
        }
    }

    return sum;
}

int solve(std::vector<Board> boards, std::vector<int> randoms) {
    int last_winner_unmarked = -1;
    int last_winner_rand = 1;

    for(int i = 0; i < randoms.size(); i++) {
        mark_numbers(boards, randoms[i]);
        
        int new_winner = find_new_last_winner(boards);
        if(new_winner != -1) {
            last_winner_unmarked = unmarked_sum(boards[new_winner]);
            last_winner_rand = randoms[i];
        }
    }
            
    return last_winner_rand * last_winner_unmarked; 
}

int main() {
    std::vector<int> randoms;
    std::vector<Board> boards;

    std::string randoms_s;
    std::cin >> randoms_s;
    randoms = gen_randoms(randoms_s);

    while(!std::cin.eof()) {
        Board b = read_board();
        boards.push_back(b);
    }
    
    std::cout << solve(boards, randoms) << std::endl;
}
