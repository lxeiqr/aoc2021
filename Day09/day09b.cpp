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
    bool checked = false;

    Field() {}
    Field(int v) { value = v; };
};

struct Map {
    int w, h;
    Field **p;

    Map(int w, int h);
    ~Map();

    std::vector<Point> neighbours(int x, int y);
    int solve();

    bool is_low_point(int x, int y);
    bool is_flow_down(int x, int y);
    std::vector<Point> find_low_points();

    int calculate_basin_size(Point a);
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
            ret.push_back(Point(x + px, y + py));
    }

    return ret;
}

bool Map::is_low_point(int x, int y) {
    std::vector<Point> ngh = neighbours(x,y);

    int sum = 0;
    for(auto a : ngh) {
        sum += (p[a.x][a.y].value > p[x][y].value);
    }

    return sum == ngh.size();
}

std::vector<Point> Map::find_low_points() {
    std::vector<Point> r;

    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
            if(is_low_point(i, j))
                r.push_back(Point(i, j));

    return r;
}

bool Map::is_flow_down(int x, int y) {
    return p[x][y].value != 9;
}

// BFS
int Map::calculate_basin_size(Point a) {
    std::queue<Point> to_visit;
    to_visit.push(a);

    int sum = 0;

    while(!to_visit.empty()) {
        Point cur = to_visit.front();
        to_visit.pop();
        Field& cur_field = p[cur.x][cur.y];

        if(cur_field.checked)
            continue;
        
        cur_field.checked = true;
        
        if(cur_field.value == 9) 
            continue;

        sum++;

        for(auto n : neighbours(cur.x, cur.y))
            to_visit.push(n);

    }

    return sum;
}

int Map::solve() {
    std::vector<Point> low_points = find_low_points();
    std::vector<int> sums;

    for(auto a : low_points)
        sums.push_back(calculate_basin_size(a));

    std::sort(sums.begin(), sums.end());

    size_t sl = sums.size();
    return sums[sl - 1] * sums[sl - 2] * sums[sl - 3];
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
