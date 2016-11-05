#include "WeightedQuickUnionPathCompression.hpp"


WeightedQuickUnionPathCompression::
WeightedQuickUnionPathCompression(int n)
{
  count_ = n;
  for (int i = 0; i < n; ++i)
    id_.push_back(i);
}


int
WeightedQuickUnionPathCompression::
find(int p)
{
  int root = p;
  while (root != id_[root])
    root = id_[root];
  while (p != root) {
    int newp = id_[p];
    id_[p] = root;
    p = newp;
  }
  return root;
}


bool
WeightedQuickUnionPathCompression::
connected(int p, int q)
{
  return find(p) == find(q);
}


void
WeightedQuickUnionPathCompression::
union2(int p, int q)
{
  int rootP = find(p);
  int rootQ = find(q);
  if (rootP == rootQ) return;
  id_[rootP] = rootQ;
  count_--;
}
