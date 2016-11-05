#ifndef AGGREGATION_H_
#define AGGREGATION_H_

#include <map>
#include <set>
#include <armadillo>

class Aggregation
{
public:
  Aggregation(arma::mat wf, double ratio, int nx, int ny);
  void Find();
  std::set<int> ShowIndex(int num);

private:
  bool IsSelected(int index);
  arma::uvec SelectAround(int index);
  int GetOrignalIndex(int extend_index);
  arma::mat wf_;
  arma::ivec selected_;
  std::map<int, std::set<int> > aggregated_;
  std::map<int, int> count_;
  int nx_;
  int ny_;
  int nrow_;
  int ncol_;
  double ratio_;
};

#endif
