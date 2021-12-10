#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

struct Result {
    bool valid = true; // true - unfinished, false - invalid
    char first_invalid; // for invalid
    long long score = 0; // for valid

    Result();
    Result(char c); // invalid
    Result(long long score); // unfinished
};

Result::Result(){
    valid = true;
}

Result::Result(char c) {
    valid = false;
    first_invalid = c;
}

Result::Result(long long score) {
    this->valid = true;
    this->score = score;
}

char ending_to_opening(char c) {
    switch(c) {
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        case '>': return '<';
    }

    return '?';
}

int char_to_points(char c) {
    switch(c) {
        case '(': return 1;
        case '[': return 2;
        case '{': return 3;
        case '<': return 4;
        default:  return 0;
    }
}

Result check_line(std::string s) {
    std::stack<char> chunks;

    for(auto c : s)
        switch(c) {
            case '(':
            case '[':
            case '{':
            case '<':
                chunks.push(c);
                break;
            
            case ')':
            case ']':
            case '}':
            case '>':
                if(ending_to_opening(c) == chunks.top())
                    chunks.pop();
                else
                    return Result(c);
                break;
        }

    long long score = 0;
    while(!chunks.empty()) {
        char c = chunks.top();
        chunks.pop();
        score = score * 5 + char_to_points(c);
    }

    return Result(score);
}

int main() {
    std::vector<long long> points;

    std::string in;
    while(std::getline(std::cin, in)) {
        Result r = check_line(in);
        if(r.valid)
            points.push_back(r.score);
    }

    // Too lazy to implement quickselect
    std::sort(points.begin(), points.end());
    std::cout << points[points.size()/2] << std::endl;
}
