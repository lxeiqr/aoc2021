#include <iostream>
#include <vector>

#define INUM_LEN 12

static int pow2(int a) {
    if(a > 0) return 2 << (a - 1);
    else return 1;
}

int binstr_to_value(std::string s) {
    int value = 0;

    for(int i = 0; i < s.length(); i++) {
        if(s[s.length() - i - 1] == '1')
            value += pow2(i);
    }

    return value;
}

struct SearchElem {
    std::string str;
    int pos = 0;
};

// type: 0 - oxy, 1 - co2
char find_criteria(std::vector<SearchElem> data, bool type) {
    int ones = 0;

    for(int i = 0; i < data.size(); i++)
        if(data[i].str[0] == '1')
            ones++;

    int zeroes = data.size() - ones;

    bool match = ones >= zeroes; // For oxy
    if(type == 1) // Reverse for CO2
        match = !match;

    return match ? '1' : '0';
}

// type: 0 - oxy, 1 - co2
int find_value(std::vector<std::string> data, bool type) {
    std::vector<SearchElem> search;

    for(int i = 0; i < data.size(); i++) {
        SearchElem elem = {
            .str = data[i],
            .pos = i
        };

        search.push_back(elem);
    }

    while(search.size() > 1) {
        char crit = find_criteria(search, type);
        
        for(int i = 0; i < search.size(); i++) {
            if(search[i].str[0] == crit) {
                search[i].str.erase(0,1);
            } else {
                search.erase(search.begin() + i);
                i--;
            }
        }
    }

    return binstr_to_value(data[search[0].pos]);
}

int main() {
    std::vector<std::string> data;

    std::string in;
    while(std::cin >> in)
        data.push_back(in);

    std::cout << find_value(data, 0) * find_value(data, 1) << std::endl;
}
