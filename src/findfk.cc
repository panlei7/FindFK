#include "aggregation.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <utility>

int main(int argc, char *argv[])
{
  int nx = std::stoi(argv[1]);
  int ny = std::stoi(argv[2]);
  double dmax = std::stod(argv[3]);
  double ratio = std::stod(argv[4]);
  int niter = std::stoi(argv[5]);

  if (dmax > 1. || dmax < 0.) {
    std::cout << "dmax should between 0 and 1" << std::endl;
    return -1;
  }
  std::ifstream infile("test_data.txt");

  if (!infile) {
    std::cout << "Error opening input file" << std::endl;
    return -1;
  }

  std::string line;
  std::vector<double> data;
  int nk = 0;
  int nf = 0;

  while (std::getline(infile, line)) {
    ++nf;
    std::istringstream record(line);
    std::string number_s;
    while (record >> number_s) {
      if (nf == 1)
        ++nk;
      double number_d = std::stod(number_s);
      if (number_d <= 0.)
        number_d = -1.;
      data.push_back(number_d);
    }
  }
  int nmax = static_cast<int>(nf*nk*dmax);
  Aggregation agg(data, nf, nk, ratio, nx, ny, nmax);
  agg.aggregateAll();

  std::ofstream outfile("output.txt");
  if (!outfile) {
    std::cout << "Error opening output file" << std::endl;
    return -1;
  }
  for (int i=0; i<niter; ++i) {
    std::set<std::pair<int, int> > result = agg.showPointsGivenCluster(i);
    for (auto r : result)
      outfile << i << " " << r.first << " " << r.second << std::endl;
  }
  return 0;
}
