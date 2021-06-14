#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const int LOCK_START_INDEX = 10000;

struct Node {
  int id;
};

bool operator==(const Node &left, const Node &right) {
  return left.id == right.id;
}

template <> struct std::hash<Node> {
  std::size_t operator()(const Node &node) const {
    return std::hash<int>{}(node.id);
  }
};

std::ostream &operator<<(std::ostream &left, const Node &right) {
  left << (right.id > LOCK_START_INDEX ? "lock" : "process") << ' '
       << (right.id > LOCK_START_INDEX ? right.id - LOCK_START_INDEX
                                       : right.id);
  return left;
}

bool dfs(
    const Node *root,
    std::unordered_map<const Node *, std::unordered_set<const Node *>> &edges,
    std::unordered_map<const Node *, bool> &visited) {

  if (visited[root]) {
    std::cout << "Ohhhhhh, it is already visited!\n";
    return true;
  }

  visited[root] = true;
  auto r = edges.find(root);
  if (r != edges.cend())
    for (auto n : r->second) {
      std::cout << "from " << *root << " go to " << *n << "\n";
      if (dfs(n, edges, visited))
        return true;
      std::cout << "from " << *n << " back to " << *root << "\n";
    }

  edges.erase(root);
  return false;
}

// 1 10001 -> process 1 is waiting for lock 10001
// 10001 1 -> lock 10001 is owned by process 1

int main() {
  std::vector<int> ns;

  while (std::cin) {
    int n;
    std::cin >> n;
    if (std::cin)
      ns.push_back(n);
  }

  if (!std::cin.eof()) {
    std::cerr << "Failed to parse input.\n";
    return -1;
  }

  if (ns.size() % 2 != 0) {
    std::cerr << "Input integer number must be even.\n";
    return -1;
  }

  std::unordered_set<Node> nodes;
  std::unordered_map<const Node *, std::unordered_set<const Node *>> edges;

  for (int i = 0; i < ns.size(); i += 2) {
    int p = ns[i];
    int l = ns[i + 1];
    auto r1 = nodes.insert({p});
    auto r2 = nodes.insert({l});
    edges[&(*r1.first)].insert(&(*r2.first));
  }

  bool h = false;

  while (!edges.empty()) {
    auto n = edges.cbegin()->first;
    std::unordered_map<const Node *, bool> visited;
    std::cout << "Begin to detect child graph containing '" << *n << "'.\n";
    if (dfs(n, edges, visited)) {
      h = true;
      break;
    }
  }

  if (h) {
    std::cout << "Cycle, aka dead lock, detected.\n";
  } else {
    std::cout << "You are free of dead lock!!!\n";
  }

  return 0;
}
