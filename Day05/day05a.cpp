#include <iostream>
#include <string>
#include <vector>

struct Point {
    int x,y;
};
    
struct Line {
    Point p1, p2;
};

Point parse_point(std::string s) {
    std::string delimeter = ",";
    std::string xs = s.substr(0, s.find(delimeter));
    std::string ys = s.substr(s.find(delimeter) + delimeter.length());

    Point p = {std::stoi(xs), std::stoi(ys)};
    return p;
}

Line parse_line(std::string s) {
    std::string delimeter = " -> ";
    std::string p1_s = s.substr(0, s.find(delimeter));
    s.erase(0, s.find(delimeter) + delimeter.length());
    std::string p2_s = s;


    Point p1 = parse_point(p1_s);
    Point p2 = parse_point(p2_s);

    Line l = {p1, p2};

    return l;
}

bool is_diagonal(Line l) {
    return l.p1.x != l.p2.x && l.p1.y != l.p2.y;
}

Point field_size(std::vector<Line> ls) {
    int w = 0, h = 0;

    for(Line l : ls) {
        w = std::max(w, l.p1.x);
        w = std::max(w, l.p2.x);
        
        h = std::max(h, l.p1.y);
        h = std::max(h, l.p2.y);
    }

    Point p = {w + 1, h + 1};
    return p;
}

struct Field {
    int w, h;
    int *p;

    Field(int w, int h);
    ~Field();

    void mark_line(Line l);
private:
    void mark_horz(Line l);
    void mark_vert(Line l);
};

Field::Field(int w, int h) {
    this->w = w;
    this->h = h;

    p = new int[w * h];
    for(int i = 0; i < w * h; i++) {
        p[i] = 0;
    }
}

Field::~Field() {
    delete p;
}

void Field::mark_horz(Line l) {
    int x1 = std::min(l.p1.x, l.p2.x);
    int x2 = std::max(l.p1.x, l.p2.x);

    for(int i = x1; i <= x2; i++)
        p[i + l.p1.y * w]++;
}

void Field::mark_vert(Line l) {
    int y1 = std::min(l.p1.y, l.p2.y);
    int y2 = std::max(l.p1.y, l.p2.y);

    for(int i = y1; i <= y2; i++)
        p[l.p1.x + i * w]++;
}

// WARNING: Works only for horz and vert lines
void Field::mark_line(Line l) {
    bool is_horz = (l.p1.y == l.p2.y);
    if(is_horz)
        mark_horz(l);
    else
        mark_vert(l);
}

int solve(std::vector<Line> ls) {
    Point field_wh = field_size(ls);
    Field field(field_wh.x, field_wh.y);

    for(Line l : ls)
        field.mark_line(l);

    int overlaps = 0;
    for(int i = 0; i < field.w * field.h; i++)
        if(field.p[i] >= 2)
            overlaps++;

    return overlaps;
}

int main() {
    std::vector<Line> ls;

    std::string in;
    while(std::getline(std::cin, in)) {
        Line l = parse_line(in);
        ls.push_back(l);
    }

    /*
    for(Line l : ls) {
        std::cout << "(" << l.p1.x << "," << l.p1.y << ") -> (" << l.p2.x << "," << l.p2.y << ")" << std::endl; 
    }
    */

    // Filter out unused lines
    for(int i = 0; i < ls.size(); i++) {
        if(is_diagonal(ls[i])) {
            ls.erase(ls.begin() + i);
            i--;
        }
    }

    std::cout << "Solution: " << solve(ls) << std::endl;
}
