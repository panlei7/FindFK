#include "../include/catch.hpp"
#include "../src/aggregation.hpp"

#include <armadillo>
#include <set>

TEST_CASE("find a square", "[square]")
{
  const int dim1 = 10;
  const int dim2 = 10;
  arma::mat data(dim1, dim2, arma::fill::zeros);

  const int nx = 1;
  const int ny = 1;
  const double ratio = 50;

  SECTION("one square in the center") {
    const int dx = 2;
    arma::uvec ix = {2, 2, 2, 3, 3, 3, 4, 4, 4};
    arma::uvec iy = {4, 5, 6, 4, 5, 6, 4, 5, 6};
    data(ix, iy).fill(1.);
    Aggregation agg(data, ratio, nx, ny);
    agg.Find();
    std::set<int> result = agg.ShowIndex(0);
    std::set<int> ref;
    for (auto i: ix)
      for (auto j: iy)
        ref.insert(arma::sub2ind(arma::size(dim1, dim2), i, j));
    REQUIRE(result == ref);
  }
}
