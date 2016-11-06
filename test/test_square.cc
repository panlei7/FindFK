#include "../include/catch.hpp"
#include "../src/aggregation.hpp"

#include <set>
#include <iostream>

int convert2Dto1D(int dim1,
                  int dim2,
                  int index1,
                  int index2)
{
  return index1*dim2 + index2;
}


TEST_CASE("find a square", "[square]")
{
  const int dim1 = 10;
  const int dim2 = 10;

  const int nx = 1;
  const int ny = 1;
  const double ratio = 0.5;

  std::vector<double> data(dim1*dim2, 0.);

  SECTION("one square in the center") {
    std::set<std::pair<int, int> > points;
    points.insert(std::make_pair(4, 4));
    points.insert(std::make_pair(5, 4));
    points.insert(std::make_pair(6, 4));
    points.insert(std::make_pair(4, 5));
    points.insert(std::make_pair(5, 5));
    points.insert(std::make_pair(6, 5));
    points.insert(std::make_pair(4, 6));
    points.insert(std::make_pair(5, 6));
    points.insert(std::make_pair(6, 6));

    for (auto &point : points)
      data[convert2Dto1D(dim1, dim2, point.first, point.second)] = 1.;

    Aggregation agg(data, dim1, dim2, ratio, nx, ny);
    agg.aggregateAll();
    std::set<std::pair<int, int> > result = agg.showPointsGivenCluster(0);
    REQUIRE(result == points);
  }
}
