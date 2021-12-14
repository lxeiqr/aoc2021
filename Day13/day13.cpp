#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Fold {
    enum FoldType {
        FOLD_X,
        FOLD_Y
    } type;

    int coord;
};

struct Map {
    int w, h;
    bool **p;

    int alloc_w;

    Map(int w, int h);
    ~Map();

    void fold(Fold f);
    void fold_point(Fold f, int x, int y);
    int count_marked();

    void draw();
};

void Map::draw() {
    for(int j = 0; j < h; j++) {
        for(int i = 0; i < w; i++) {
            std::cout << (p[i][j] == true ? (char)219 : ' ');
        }
        std::cout << std::endl;
    }
}

Map::Map(int w, int h) {
    this->w = w;
    this->h = h;
    this->alloc_w = w;

    this->p = new bool*[alloc_w];
    for(int i = 0; i < w; i++) {
        this->p[i] = new bool[h];
        
        for(int j = 0; j < h; j++)
            this->p[i][j] = false;
    }
}

Map::~Map() {
    for(int i = 0; i < alloc_w; i++) {
        delete this->p[i];
    }

    delete this->p;
}

int is_in_range(int x, int bottom, int top) {
    return bottom <= x && x < top;
}

std::pair<int, int> parse_coord(std::string l) {
    std::string left_s = l.substr(0, l.find(','));
    std::string right_s = l.substr(l.find(',') + 1, l.length()); 

    int left = std::stoi(left_s), right = std::stoi(right_s);

    return std::make_pair(left, right); 
}

Fold parse_fold(std::string l) {
    Fold r;

    char coord_char = l[11];
    if(coord_char == 'x')
        r.type = Fold::FOLD_X;
    else
        r.type = Fold::FOLD_Y;

    r.coord = std::stoi(l.substr(13, l.length()));

    return r;
}

void Map::fold_point(Fold f, int x, int y) {
    int mirror_coord = f.type == Fold::FOLD_Y ? 2 * f.coord - y : 2 * f.coord - x; 

    bool *pnt = &p[x][y];
    bool *pnt_mir;
    if(f.type == Fold::FOLD_X)
        pnt_mir = &p[mirror_coord][y];
    else
        pnt_mir = &p[x][mirror_coord];

    *pnt_mir |= *pnt;
    *pnt = false;
}

void Map::fold(Fold f) {
    if(f.type == Fold::FOLD_Y) {
        for(int i = 0; i < w; i++) {
            for(int j = f.coord+1; j < h; j++)
                fold_point(f, i, j);
        }

        h = f.coord;
    } else {
        for(int i = f.coord+1; i < w; i++) {
            for(int j = 0; j < h; j++)
                fold_point(f, i, j);
        }

        w = f.coord;
    }
}

int Map::count_marked() {
    int sum = 0;

    for(int i = 0; i < this->w; i++)
        for(int j = 0; j < this->h; j++)
            sum += (p[i][j] == true);

    return sum;
}

int main() {
    std::vector<std::string> input;
    std::vector<std::pair<int, int> > coords;
    std::vector<Fold> folds;

    std::string in;
    while(std::getline(std::cin, in))
        input.push_back(in);

    int i = 0;
    for(; !input[i].empty(); i++)
        coords.push_back(parse_coord(input[i]));

    i++;

    for(; i < input.size(); i++)
        folds.push_back(parse_fold(input[i]));

    // Get map size
    int x_max = 0, y_max = 0;
    for(auto p : coords) {
        x_max = std::max(x_max, p.first);
        y_max = std::max(y_max, p.second);
    }

    Map map(x_max + 1, y_max + 1);

    // Mark points
    for(auto p : coords)
        map.p[p.first][p.second] = true;


    map.fold(folds[0]);
    folds.erase(folds.begin());
    std::cout << "Part 1: " << map.count_marked() << std::endl;

    for(auto f : folds)
        map.fold(f);
    
    std::cout << "Part 2: " << std::endl;
    map.draw();
}
