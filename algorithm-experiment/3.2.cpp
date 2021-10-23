#include <dlib/string.h>
#include <dlib/string/string.h>
#include <iostream>
#include <istream>
#include <map>
#include <queue>
#include <set>
#include <string>

std::map<std::string, std::vector<std::string>> graph;
std::map<std::string, std::vector<std::string>> reverse_graph;

int max_depth;
std::string conflict;
std::string conflict_parent;

std::vector<std::string> list;

void DFS(const std::string &current) {
  for (auto i = list.cbegin(); i != list.cend(); ++i) {
    if (*i == current) {
      conflict_parent = current;
      conflict = list.back();
      return;
    }
  }

  list.push_back(current);

  if (list.size() > max_depth) {
    max_depth = list.size();
  }

  if (list.size() == 18) {
    for (const auto &s : list) {
      std::cout << s << "->";
    }
    std::cout << "The End!!!" << std::endl;
  }

  for (const auto &s : graph[current]) {
    DFS(s);
  }

  list.pop_back();
}

void DFS() {
  for (const auto &[k, v] : reverse_graph) {
    if (v.empty()) {
      list.clear();
      DFS(k);
    }
  }
}

std::vector<std::string> SplitBySpace(const std::string &s) {
  std::vector<std::string> result;
  int current_pos = 0;

  while (true) {
    auto p = s.find_first_of(" ", current_pos);
    if (p == std::string::npos) {
      result.push_back(std::string(s.cbegin() + current_pos, s.cend()));
      break;
    } else {
      result.push_back(std::string(s.cbegin() + current_pos, s.cbegin() + p));
      current_pos = p + 1;
    }
  }

  return result;
}

int main() {
  std::string s;
  while (std::getline(std::cin, s)) {
    auto result = SplitBySpace(s);

    std::string parent = result.front();

    graph[parent];
    reverse_graph[parent];

    for (auto i = result.cbegin() + 1; i != result.cend(); i++) {
      graph[parent].push_back(*i);
      reverse_graph[*i].push_back(parent);
    }
  }

  std::cout << "We have " << graph.size() << " items.\n";
  std::cout << "We have " << reverse_graph.size() << " parent items.\n";

  DFS();

  std::cout << conflict << "->" << conflict_parent << '\n';
  std::cout << "Max depth: " << max_depth << '\n';

  return 0;
}
