#include "tools.hpp"
#include "../include/catch.hpp"
#include "../src/aggregation.hpp"

#include <set>
#include <utility>

using namespace tools;

TEST_CASE("find points along a line", "[line]")
{
  const int dim1 = 10;
  const int dim2 = 10;

  const double ratio = 0.5;

  std::vector<double> data(dim1*dim2, 0.);

  SECTION("slope = 1")  {
    const int nx = 1;
    const int ny = 1;
    std::set<std::pair<int, int> > points;
    points.insert(std::make_pair(2, 2));
    points.insert(std::make_pair(3, 3));
    points.insert(std::make_pair(4, 4));
    points.insert(std::make_pair(5, 5));
    points.insert(std::make_pair(6, 6));
    points.insert(std::make_pair(7, 7));

    for (auto &point : points)
      data[convert2Dto1D(dim1, dim2, point.first, point.second)] = 1.;

    Aggregation agg(data, dim1, dim2, ratio, nx, ny);
    agg.aggregateAll();
    std::set<std::pair<int, int> > result = agg.showPointsGivenCluster(0);
    REQUIRE(result == points);
  }

  SECTION("slope =  2")  {
    const int nx = 2;
    const int ny = 2;
    std::set<std::pair<int, int> > points;
    points.insert(std::make_pair(1, 2));
    points.insert(std::make_pair(2, 4));
    points.insert(std::make_pair(3, 6));
    points.insert(std::make_pair(4, 8));

    for (auto &point : points)
      data[convert2Dto1D(dim1, dim2, point.first, point.second)] = 1.;

    Aggregation agg(data, dim1, dim2, ratio, nx, ny);
    agg.aggregateAll();
    std::set<std::pair<int, int> > result = agg.showPointsGivenCluster(0);
    REQUIRE(result == points);
  }

}

TEST_CASE("find points along two lines", "[line]")
{
  const int dim1 = 10;
  const int dim2 = 10;

  const double ratio = 0.1;

  std::vector<double> data(dim1*dim2, 0.);

  const int nx = 2;
  const int ny = 2;

  std::set<std::pair<int, int> > points1;
  points1.insert(std::make_pair(2, 2));
  points1.insert(std::make_pair(3, 3));
  points1.insert(std::make_pair(4, 4));
  points1.insert(std::make_pair(5, 5));
  points1.insert(std::make_pair(6, 6));
  points1.insert(std::make_pair(7, 7));

  std::set<std::pair<int, int> > points2;
  points2.insert(std::make_pair(1, 2));
  points2.insert(std::make_pair(2, 4));
  points2.insert(std::make_pair(3, 6));
  points2.insert(std::make_pair(4, 8));

  std::set<std::pair<int, int> > points;
  points.insert(points1.cbegin(), points1.cend());
  points.insert(points2.cbegin(), points2.cend());

  for (auto &point : points1)
    data[convert2Dto1D(dim1, dim2, point.first, point.second)] = 1.;
  for (auto &point : points2)
    data[convert2Dto1D(dim1, dim2, point.first, point.second)] = 3.;

  Aggregation agg(data, dim1, dim2, ratio, nx, ny);
  agg.aggregateAll();
  std::set<std::pair<int, int> > result1 = agg.showPointsGivenCluster(0);
  REQUIRE(result1 == points1);
  std::set<std::pair<int, int> > result2 = agg.showPointsGivenCluster(1);
  REQUIRE(result2 == points2);
}
