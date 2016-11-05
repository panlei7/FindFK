#include "aggregation.hpp"
#include "WeightedQuickUnionPathCompression.hpp"

#include <map>
#include <vector>
#include <utility>
#include <set>

#include <armadillo>

Aggregation::Aggregation(arma::mat wf,
                         double ratio,
                         int nx,
                         int ny):
  selected_(wf.n_elem, arma::fill::zeros),
  nx_(nx),
  ny_(ny),
  nrow_(wf.n_rows),
  ncol_(wf.n_cols),
  ratio_(ratio)
{
  arma::mat wf_(2*nx_ + nrow_, 2*ny_ + ncol_, arma::fill::zeros);
  wf_.submat(nx_, ny_, nrow_+nx_, ncol_+ny_) = wf;
}


void Aggregation::Find()
{
  int nwf = wf_.n_elem;
  WeightedQuickUnionPathCompression wqupc(nwf);
  arma::uvec indices1d = arma::sort_index(wf_, "descend");
  int nlimit = static_cast<int>(nwf*ratio_);
  if (nlimit > nwf) nlimit = nwf;
  for (int i=0; i<nlimit; ++i) {
    int index_center = indices1d(i);
    if(IsSelected(index_center)) continue;
    arma::uvec selected = SelectAround(index_center);
    for (auto s : selected) {
      wqupc.union2(index_center, s);
      selected_(s) = 1;
    }
  }
  for (int i=0; i<nlimit; ++i) {
    int index = indices1d(i);
    if (!IsSelected(index)) continue;
    int index_find = wqupc.find(index);
    ++count_[index_find];
    int orignal_index = GetOrignalIndex(index)
    aggregated_[index_find].insert(original_index);
  }
}


bool Aggregation::IsSelected(int index1d)
{
  return selected_(index1d);
}



std::set<int> Aggregation::ShowIndex(int num)
{
  std::vector<std::pair<int, int> > pairs;
  for (auto itr=count_.cbegin(); itr != count_.cend(); ++itr)
    pairs.push_back(std::make_pair(itr->first, itr->second));
  std::sort(pairs.begin(), pairs.end(),
            [=](std::pair<int, int>& a, std::pair<int, int>& b)
            {return a.second > b.second;});
  return aggregated_[pairs[num].first];
}

arma::uvec Aggregation::SelectAround(int index1d)
{
  arma::uvec index2d = arma::ind2sub(arma::size(wf_), index1d);
  arma::mat scope = wf_.submat(index2d(0)-nx_,
                               index2d(1)-ny_,
                               index2d(0)+nx_,
                               index2d(1)+ny_);
  // simple case: only > 0
  arma::uvec indices_find = arma::find(scope>0);
  unsigned index_begin = index1d - wf_.n_cols*nx_ - ny_;
  return indices_find + index_begin;
}


int Aggregation::GetOrignalIndex(int extend_index)
{
  arma::uvec extendsub = arma::ind2sub(arma::size(wf_), extend_index);
  return arma::sub2ind(arma::size(nrow_, ncol_), extendsub)
}
