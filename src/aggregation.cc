#include "aggregation.hpp"
#include "WeightedQuickUnionPathCompression.hpp"

#include <map>
#include <vector>
#include <utility>
#include <set>
#include <cmath>
#include <iostream>

Aggregation::Aggregation(std::vector<double>& flatten_array,
                         int nf,
                         int nk,
                         double ratio,
                         int num_stencil_f,
                         int num_stencil_k):
  nf_(nf),
  nk_(nk),
  ratio_(ratio),
  nsf_(num_stencil_f),
  nsk_(num_stencil_k),
  dim1_(nf+2*num_stencil_f),
  dim2_(nk+2*num_stencil_k),
  extended_data_((nf+2*num_stencil_f)*(nk+2*num_stencil_k), 0.),
  input_data_(flatten_array)
{
  for (auto id_f = 0; id_f < nf_; ++id_f)
    for (auto id_k = 0; id_k < nk_; ++id_k) {
      int index_input_1D = convertIndexFrom2Dto1D(nf_, nk_, id_f, id_k);
      int index_extended_1D = convertIndexFrom2Dto1D(dim1_,
                                                     dim2_,
                                                     id_f+nsf_,
                                                     id_k+nsk_);
      extended_data_[index_extended_1D] = flatten_array[index_input_1D];
    }
}


std::vector<int> Aggregation::getIndexAround(int index_center)
{
  std::pair<int, int> index_2D = convertIndexFrom1Dto2D(dim1_,
                                                        dim2_,
                                                        index_center);
  int fc = index_2D.first;
  int kc = index_2D.second;
  std::vector<int> indexAround;
  for (auto id_f = fc-nsf_; id_f < fc+nsf_; ++id_f)
    for (auto id_k = kc-nsk_; id_k < kc+nsk_; ++id_k) {
      if (id_f == fc && id_k == kc) continue;
      indexAround.push_back(convertIndexFrom2Dto1D(dim1_,
                                                   dim2_,
                                                   id_f,
                                                   id_k));
    }
  return indexAround;
}


std::pair<int, int>
Aggregation::convertIndexFrom1Dto2D(int dim1,
                                    int dim2,
                                    int index)
{
  int id1 = index / dim2;
  int id2 = index % dim2;
  return std::make_pair(id1, id2);
}


int Aggregation::convertIndexFrom2Dto1D(int dim1,
                                        int dim2,
                                        int index1,
                                        int index2)
{
  return index1*dim2 + index2;
}


std::vector<int>
Aggregation::findApproximationsAround(int index_center)
{
  std::vector<int> index_around = getIndexAround(index_center);
  double value_center = extended_data_[index_center];
  std::vector<int> index_approximation;
  for (auto i=0; i<index_around.size(); ++i)
    if (approximateMethod(value_center, extended_data_[index_around[i]]))
      index_approximation.push_back(index_around[i]);
  return index_approximation;
}


bool Aggregation::approximateMethod(double d1,
                                    double d2)
{
  if (d1 <= 0.)
    return false;
  else {
    double value = std::abs(d1-d2) / d1;
    return (value < ratio_);
  }
}


void Aggregation::aggregateAll()
{
  WeightedQuickUnionPathCompression wqupc(extended_data_.size());
  for (auto id_f = nsf_; id_f < nf_+nsf_; ++id_f)
    for (auto id_k = nsk_; id_k < nk_+nsk_; ++id_k) {
      int index_center = convertIndexFrom2Dto1D(dim1_,
                                                dim2_,
                                                id_f,
                                                id_k);
      auto index_around = findApproximationsAround(index_center);
      for (auto index: index_around)
        wqupc.union2(index_center, index);
    }
  for (auto id_f = nsf_; id_f < nf_+nsf_; ++id_f)
    for (auto id_k = nsk_; id_k < nk_+nsk_; ++id_k) {
      int index = convertIndexFrom2Dto1D(dim1_,
                                         dim2_,
                                         id_f,
                                         id_k);
      union_results_.push_back(wqupc.find(index));
    }
}


std::set<std::pair<int, int>>
Aggregation::showPointsGivenCluster(int num)
{
  std::map<int, int> count;
  for (auto r : union_results_)
    ++count[r];
  std::vector<std::pair<int, int> > pairs;
  for (auto itr=count.cbegin(); itr != count.cend(); ++itr) {
    pairs.push_back(std::make_pair(itr->first, itr->second));
  }

  std::sort(pairs.begin(), pairs.end(),
            [=](std::pair<int, int>& a, std::pair<int, int>& b)
            {return a.second > b.second;});

  std::set<std::pair<int, int> > result;
  for (auto i = 0; i < union_results_.size(); ++i) {
    if (union_results_[i] == pairs[num].first) {
      std::pair<int, int> index2D = convertIndexFrom1Dto2D(nf_,
                                                           nk_,
                                                           i);
      result.insert(index2D);
    }
  }

  return result;
}

