#ifndef AGGREGATION_H_
#define AGGREGATION_H_

#include <map>
#include <vector>
#include <set>
#include <utility>


class Aggregation
{
public:
  Aggregation(std::vector<double>& flatten_array,
              int nf,
              int nk,
              double ratio,
              int num_stencil_f,
              int num_stencil_k);
  std::set<std::pair<int, int> > showPointsGivenCluster(int num);
  void aggregateAll();

private:
  std::vector<int> findApproximationsAround(int index_center);
  std::vector<int> getIndexAround(int index_center);
  std::pair<int, int> convertIndexFrom1Dto2D(int dim1,
                                             int dim2,
                                             int index);
  int convertIndexFrom2Dto1D(int dim1,
                             int dim2,
                             int index1,
                             int index2);
  bool approximateMethod(double d1,
                         double d2);

  int nf_;
  int nk_;
  double ratio_;
  int nsf_;
  int nsk_;
  int dim1_; // 2D dimmensions of extended_data_
  int dim2_;

  std::vector<double> extended_data_;
  std::vector<double> input_data_;
  std::vector<int> union_results_;
};

#endif
