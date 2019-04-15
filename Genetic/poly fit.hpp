//
//  expr bytecode.hpp
//  Genetic
//
//  Created by Indi Kernick on 19/3/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef expr_bytecode_hpp
#define expr_bytecode_hpp

#include <string>
#include <vector>
#include "chromosome.hpp"

using PolyAllele = short;
constexpr size_t POLY_DEG = 2;
using PolyChromo = Chromosome<PolyAllele, POLY_DEG + 1>;
using PolyFitness = double;

struct PolyRow {
  double x;
  double y;
};

using PolyTable = std::vector<PolyRow>;

PolyFitness polyFitness(const PolyChromo &, const PolyTable &);

#endif
