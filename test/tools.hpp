#ifndef TOOLS_H_
#define TOOLS_H_

namespace tools
{
  inline int convert2Dto1D(int dim1,
                    int dim2,
                    int index1,
                    int index2)
  {
    return index1*dim2 + index2;
  }
}

#endif
