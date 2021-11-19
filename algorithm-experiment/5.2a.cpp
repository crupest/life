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

  long long max_count = 0;
  long long max_id = 0;

  for (auto it = counts.begin(); it != counts.end(); ++it) {
    if (it->second > max_count) {
      max_count = it->second;
      max_id = it->first;
    }
  }

  std::cout << max_id << std::endl;

  return 0;
}