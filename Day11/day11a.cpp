#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Point {
    int x, y;
    Point(int x, int y);
};

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

struct Field {
    int value = 0;

    Field() {}
    Field(int v) { value = v; };
};

struct Map {
    int w, h;
    Field **p;

    Map(int w, int h);
    ~Map();

    std::vector<Point> neighbours(int x, int y);

    int step();
};

Map::Map(int w, int h) {
    this->w = w;
    this->h = h;

    this->p = new Field*[w];
    for(int i = 0; i < w; i++) {
        this->p[i] = new Field[h];
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

std::vector<Point> Map::neighbours(int x, int y) {
    std::vector<Point> ret;

    const int mov[8][2] = {
        {-1, 0},
        {1, 0},
        {0, 1},
        {0, -1},
        {-1, 1},
        {1, 1},
        {-1, -1},
        {1, -1},
    };

    for(int i = 0; i < 8; i++) {
        int px = mov[i][0];
        int py = mov[i][1];

        if(is_in_range(x + px, 0, w) && is_in_range(y + py, 0, h))
            ret.push_back(Point(x + px, y + py));
    }

    return ret;
}

int Map::step() {
    int flashes = 0;
    std::queue<Point> to_increment;

    // Increase all values
    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++) 
            to_increment.push(Point(i,j));

    while(!to_increment.empty()) {
        Point cur = to_increment.front();
        to_increment.pop();

        p[cur.x][cur.y].value++;

        if(p[cur.x][cur.y].value == 10) {
            for(auto q : neighbours(cur.x, cur.y))
                to_increment.push(q);

            flashes++;
        }
    }
    
    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
            p[i][j].value = (p[i][j].value >= 10) ? 0 : p[i][j].value;

    return flashes;
}

int main() {
    std::vector<std::string> input;

    std::string in;
    while(std::getline(std::cin, in)) {
        input.push_back(in);
    }

    Map m(10, 10);
    
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            m.p[j][i] = (int)(input[i][j] - '0');

    int flashes = 0;
    for(int i = 0; i < 100; i++)
        //std::cout << i << ": " << m.step() << std::endl;
        flashes += m.step();

    std::cout << flashes << std::endl;
}
