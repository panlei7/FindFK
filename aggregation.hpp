#ifndef AGGREGATION_H_
#define AGGREGATION_H_

#include <map>
#include <vector>
#include <armadillo>

class Aggregation
{
public:
  Aggregation(arma::mat wf, double ratio, int nx, int ny);
  void Find();
  std::vector<int> ShowIndex(int num);

private:
  bool IsSelected(int index);
  arma::uvec SelectAround(int index);
  arma::mat wf_;
  arma::ivec selected_;
  std::map<int, std::vector<int> > aggregated_;
  std::map<int, int> count_;
  int nx_;
  int ny_;
  int nrow_;
  int ncol_;
  double ratio_;
};

#endif
