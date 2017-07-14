#!/usr/bin/env python
import numpy as np
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description
                                     ="format input")
    parser.add_argument("-i",
                        "--input",
                        help="specify the input file")
    parser.add_argument("-o",
                        "--output",
                        help="specify the output file")
    args = parser.parse_args()
    fname_out = args.output
    fname_in = args.input
    f_output = open(fname_out, "w")
    with open(fname_in, "r") as f:
        for line in f:
            slist = line.split(",")
            f_output.write(" ".join(slist))
    f_output.close()
