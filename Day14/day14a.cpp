#include <iostream>
#include <vector>
#include <limits>

struct PolymerRule {
    char left, right, result;

    PolymerRule(std::string l);
};

PolymerRule::PolymerRule(std::string s) {
    left = s[0];
    right = s[1];
    result = s[6];
}

struct Polymer {
    std::string state;
    std::vector<PolymerRule> rules;

    Polymer(std::string p_template, std::vector<PolymerRule> rules);
    void iterate();
    char find_insertion(char left, char right);
};

char Polymer::find_insertion(char left, char right) {
    for(auto r : rules)
        if(r.left == left && r.right == right)
            return r.result;

    return ' '; 
}

void Polymer::iterate() {
    for(int i = 0; i < state.size() - 1; i++) {
        char ins = find_insertion(state[i], state[i+1]);
        if(ins != ' ') {
            state.insert(state.begin() + i + 1, ins);
            i++;
        }
    }
}

Polymer::Polymer(std::string p_template, std::vector<PolymerRule> rules) {
    this->state = p_template;
    this->rules = rules;
}

int main() {
    std::string in_template;
    std::vector<PolymerRule> rules;

    std::cin >> in_template;

    // skip empty lines
    for(int i = 0; i < 2; i++)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string temp;
    while(std::getline(std::cin, temp))
        rules.push_back(PolymerRule(temp));

    Polymer p(in_template, rules);

    for(int i = 0; i < 10; i++)
        p.iterate();

    int counter['Z' - 'A' + 1] = {0};
    for(char c : p.state)
        counter[c - 'A']++;

    int max_i = 0;
    for(int i = 1; i < ('Z' - 'A' + 1); i++)
        max_i = counter[i] > counter[max_i] ? i : max_i;

    int min_i = max_i;
    for(int i = 0; i < ('Z' - 'A' + 1); i++)
        min_i = (counter[i] < counter[min_i] && counter[i] != 0) ? i : min_i;

    std::cout << counter[max_i] - counter[min_i] << std::endl;
}
