#include <iostream>
#include <map>
#include <vector>
#include <unistd.h>

struct Edge {
    std::string l, r;
};

struct Node {
    std::vector<std::string> ngh;
    bool is_small = false;
    int checked = 0;
};

typedef std::map<std::string, Node> Graph;

Edge parse_line(std::string s) {
    Edge e;
    int delim_pos = s.find('-');
    e.l = s.substr(0, delim_pos);
    e.r = s.substr(delim_pos + 1, s.length() - delim_pos);
    return e;
}

void dfs(Graph &graph, std::string path, std::string node_key, std::vector<std::string> &paths, bool extra_cave) {
    graph[node_key].checked++;

    if(path.empty())
        path = node_key;
    else
        path += "," + node_key;

    if(node_key == "end") {
        paths.push_back(path);
        graph[node_key].checked = false;
        return;
    }

    for(std::string ns : graph[node_key].ngh) {
        if(ns == "start")
            continue;

        if(std::islower(ns[0]) == false)
            dfs(graph, path, ns, paths, extra_cave);
        else if(graph[ns].checked == 0)
            dfs(graph, path, ns, paths, extra_cave);
        else if(extra_cave)
            dfs(graph, path, ns, paths, false);

    }

    graph[node_key].checked--;
}

int main() {
    Graph graph;

    std::string l;
    while(std::cin >> l) {  
        Edge e = parse_line(l);
        graph[e.l].ngh.push_back(e.r);
        graph[e.l].is_small = std::islower(e.l[0]);

        graph[e.r].ngh.push_back(e.l);
        graph[e.r].is_small = std::islower(e.r[0]);
    }

    std::vector<std::string> paths;

    dfs(graph, "", "start", paths, false);
    std::cout << "A: " << paths.size() << std::endl;

    paths.clear();
    dfs(graph, "", "start", paths, true);
    std::cout << "B: " << paths.size() << std::endl;
}
