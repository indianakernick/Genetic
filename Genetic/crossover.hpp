//
//  crossover.hpp
//  Genetic
//
//  Created by Indi Kernick on 23/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef crossover_hpp
#define crossover_hpp

#include <cassert>
#include "random.hpp"
#include "chromosome.hpp"

template <typename Allele, size_t LENGTH>
void oneCrossover(
  Chromosome<Allele, LENGTH> &a,
  Chromosome<Allele, LENGTH> &b,
  const size_t point
) {
  assert(point < LENGTH);

  for (size_t i = point; i != LENGTH; ++i) {
    std::swap(a[i], b[i]);
  }
}

template <typename Allele, size_t LENGTH, size_t POINTS>
void multiCrossover(
  Chromosome<Allele, LENGTH> &a,
  Chromosome<Allele, LENGTH> &b,
  const std::array<size_t, POINTS> &points
) {
  static_assert(POINTS < LENGTH);
  
  bool swap = false;
  size_t currentPoint = 0;
  for (size_t i = 0; i != LENGTH; ++i) {
    if (currentPoint != POINTS && points[currentPoint] == i) {
      currentPoint++;
      swap = !swap;
    }
    if (swap) {
      std::swap(a[i], b[i]);
    }
  }
}

template <typename Allele, size_t LENGTH>
Seed uniformCrossover(
  Chromosome<Allele, LENGTH> &a,
  Chromosome<Allele, LENGTH> &b,
  const Seed seed
) {
  Generator gen(seed);
  Distribution<bool> dist;
  
  for (size_t i = 0; i != LENGTH; ++i) {
    if (dist(gen)) {
      std::swap(a[i], b[i]);
    }
  }
  
  return gen();
}

#endif
