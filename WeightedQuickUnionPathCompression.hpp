#ifndef WQUPC_H_
#define WQUPC_H_

#include <vector>

class WeightedQuickUnionPathCompression
{
public:
  WeightedQuickUnionPathCompression(int n);
  int count() {return count_;};
  int find(int p);
  bool connected(int p, int q);
  void union2(int p, int q);

private:
  int count_;
  std::vector<int> id_;
};

#endif
