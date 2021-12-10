#include <iostream>
#include <stack>

struct Result {
    bool valid = true;
    char first_invalid;

    Result();
    Result(char c);
};

Result::Result(){
    valid = true;
}

Result::Result(char c) {
    valid = false;
    first_invalid = c;
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

    return Result();
}

int char_to_points(char c) {
    switch(c) {
        case ')': return 3;
        case ']': return 57;
        case '}': return 1197;
        case '>': return 25137;
        default:  return 0;
    }
}

int main() {
    int sum = 0;

    std::string in;
    while(std::getline(std::cin, in)) {
        Result r = check_line(in);
        if(!r.valid)
            sum += char_to_points(r.first_invalid);
    }

    std::cout << sum << std::endl;
}
