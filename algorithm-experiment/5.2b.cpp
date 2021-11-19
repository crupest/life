#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
  std::vector<long long> votes;

  long long v;
  while (std::cin >> v) {
    votes.push_back(v);
  }

  std::unordered_map<long long, long long> counts;
  for (auto v : votes) {
    counts[v]++;
  }

  // Get ids with votes greater than half of the total votes.
  long long half_votes = votes.size() / 2;

  for (auto it = counts.begin(); it != counts.end(); ++it) {
    if (it->second > half_votes) {
      std::cout << it->first << std::endl;
    }
  }

  return 0;
}
