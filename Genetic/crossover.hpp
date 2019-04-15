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
#include <Simpleton/Utils/profiler.hpp>

template <typename Allele, size_t LENGTH>
void oneCrossover(
  Chromosome<Allele, LENGTH> &a,
  Chromosome<Allele, LENGTH> &b,
  const size_t point
) {
  PROFILE(oneCrossover);

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
  PROFILE(multiCrossover);

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
  const float prob,
  const Seed seed
) {
  PROFILE(uniformCrossover);

  Generator gen(seed);
  Distribution<float> dist(0.0f, 1.0f);
  
  for (size_t i = 0; i != LENGTH; ++i) {
    if (dist(gen) < prob) {
      std::swap(a[i], b[i]);
    }
  }
  
  return gen();
}

#endif
