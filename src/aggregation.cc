#include "aggregation.hpp"
#include "WeightedQuickUnionPathCompression.hpp"

#include <map>
#include <vector>
#include <utility>
#include <set>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <numeric>

namespace {
  const double MINIMIUM = -1.e5;
}

Aggregation::Aggregation(std::vector<double>& flatten_array,
                         int nf,
                         int nk,
                         double ratio,
                         int num_stencil_f,
                         int num_stencil_k,
                         int num_max):
  nf_(nf),
  nk_(nk),
  ratio_(ratio),
  nsf_(num_stencil_f),
  nsk_(num_stencil_k),
  dim1_(nf+2*num_stencil_f),
  dim2_(nk+2*num_stencil_k),
  num_max_(num_max),
  extended_data_((nf+2*num_stencil_f)*(nk+2*num_stencil_k), MINIMIUM),
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


int Aggregation::convertIndexFromInputToExtended(int index)
{
  std::pair<int, int> index_input_1D =
    convertIndexFrom1Dto2D(nf_, nk_, index);
  return convertIndexFrom2Dto1D(dim1_,
                                dim2_,
                                index_input_1D.first+nsf_,
                                index_input_1D.second+nsk_);
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
    double value = std::abs(d1-d2);
    return (value < ratio_*2);
  }
}

std::vector<int> Aggregation::sortInputData()
{
  auto &v = input_data_;
  std::vector<int> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  std::sort(idx.begin(),
            idx.end(),
            [&v](size_t i1, size_t i2){return v[i1]>v[i2];});

  return idx;
}

void Aggregation::aggregateAll()
{
  WeightedQuickUnionPathCompression wqupc(extended_data_.size());

  auto index_input_sorted = sortInputData();
  std::vector<int> index_extended_sorted;

  for (auto i=0; i<num_max_; ++i) {
    auto index_input = index_input_sorted[i];
    auto index_extend = convertIndexFromInputToExtended(index_input);
    auto index_around = findApproximationsAround(index_extend);
    for (auto index: index_around)
      wqupc.union2(index_extend, index);
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

