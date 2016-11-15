#include "tools.hpp"
#include "../include/catch.hpp"
#include "../src/aggregation.hpp"

#include <set>
#include <utility>

using namespace tools;


TEST_CASE("find points of a square", "[square]")
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

    Aggregation agg(data, dim1, dim2, ratio, nx, ny, data.size());
    agg.aggregateAll();
    std::set<std::pair<int, int> > result = agg.showPointsGivenCluster(0);
    REQUIRE(result == points);
  }

  SECTION("two squares in the center") {
    std::set<std::pair<int, int> > points1;
    points1.insert(std::make_pair(4, 2));
    points1.insert(std::make_pair(5, 2));
    points1.insert(std::make_pair(6, 2));
    points1.insert(std::make_pair(4, 3));
    points1.insert(std::make_pair(5, 3));
    points1.insert(std::make_pair(6, 3));
    std::set<std::pair<int, int> > points2;
    points2.insert(std::make_pair(4, 6));
    points2.insert(std::make_pair(5, 6));
    points2.insert(std::make_pair(4, 6));
    points2.insert(std::make_pair(5, 6));
    std::set<std::pair<int, int> > points;
    points.insert(points1.cbegin(), points1.cend());
    points.insert(points2.cbegin(), points2.cend());


    for (auto &point : points)
      data[convert2Dto1D(dim1, dim2, point.first, point.second)] = 1.;

    Aggregation agg(data, dim1, dim2, ratio, nx, ny, data.size());
    agg.aggregateAll();
    std::set<std::pair<int, int> > result1 = agg.showPointsGivenCluster(0);
    REQUIRE(result1 == points1);
    std::set<std::pair<int, int> > result2 = agg.showPointsGivenCluster(1);
    REQUIRE(result2 == points2);
  }
}
