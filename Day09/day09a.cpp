#include <iostream>
#include <vector>

struct Map {
    int w, h;
    int **p;

    Map(int w, int h);
    ~Map();
    std::vector<int> neighbours(int x, int y);
    int solve();
    bool is_low_point(int x, int y);
};

Map::Map(int w, int h) {
    this->w = w;
    this->h = h;

    this->p = new int*[w];
    for(int i = 0; i < w; i++) {
        this->p[i] = new int[h];
    }
}

Map::~Map() {
    for(int i = 0; i < w; i++) {
        delete this->p[i];
    }

    delete this->p;
}

int is_in_range(int x, int bottom, int top) {
    return bottom <= x && x < top;
}

std::vector<int> Map::neighbours(int x, int y) {
    std::vector<int> ret;

    const int mov[4][2] = {
        {-1, 0},
        {1, 0},
        {0, 1},
        {0, -1},
    };

    for(int i = 0; i < 4; i++) {
        int px = mov[i][0];
        int py = mov[i][1];

        if(is_in_range(x + px, 0, w) && is_in_range(y + py, 0, h))
            ret.push_back(p[x + px][y + py]);
    }

    return ret;
}

bool Map::is_low_point(int x, int y) {
    std::vector<int> ngh = neighbours(x,y);

    int sum = 0;
    for(auto a : ngh) {
        sum += (a > p[x][y]);
    }

    return sum == ngh.size();
}

int Map::solve() {
    int total = 0;

    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
            total += is_low_point(i, j) ? p[i][j] + 1 : 0;

    return total;
}

int main() {
    std::vector<std::string> input;

    std::string in;
    while(std::getline(std::cin, in)) {
        input.push_back(in);
    }

    Map m(input[0].length(), input.size());
    
    for(int i = 0; i < input.size(); i++)
        for(int j = 0; j < input[i].size(); j++)
            m.p[j][i] = (int)(input[i][j] - '0');

    std::cout << m.solve() << std::endl;
}
