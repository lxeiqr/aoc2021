#include <iostream>
#include <map>
#include <vector>

struct Edge {
    std::string l, r;
};

struct Node {
    std::vector<std::string> ngh;
    bool is_small = false;
    bool checked = false;
};

typedef std::map<std::string, Node> Graph;

Edge parse_line(std::string s) {
    Edge e;
    int delim_pos = s.find('-');
    e.l = s.substr(0, delim_pos);
    e.r = s.substr(delim_pos + 1, s.length() - delim_pos);
    return e;
}

void dfs(Graph &graph, std::string path, std::string node_key, std::vector<std::string> &paths) {
    graph[node_key].checked = true;

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
        if(!(graph[ns].is_small && graph[ns].checked))
            dfs(graph, path, ns, paths);
    }

    graph[node_key].checked = false;
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
    dfs(graph, "", "start", paths);
    std::cout << paths.size() << std::endl;
}
