//
//  expr bytecode.cpp
//  Genetic
//
//  Created by Indi Kernick on 19/3/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "poly fit.hpp"

#include <cmath>
#include <cassert>
#include <Simpleton/Utils/profiler.hpp>

PolyFitness polyFitness(
  const PolyChromo &chromo,
  const PolyTable &table
) {
  PROFILE(polyFitness);

  PolyFitness fitness = 0;
  for (const PolyRow &row : table) {
    double y = 0.0;
    y += chromo[0];
    y += chromo[1] * row.x;
    y += chromo[2] * row.x * row.x;
    
    const double dist = std::fabs(y - row.y);
    
    if (dist < 5.0) {
      ++fitness;
    }
    if (dist < 0.5) {
      fitness += 20;
    }
  }
  
  return fitness;
}

