//
//  population.hpp
//  Genetic
//
//  Created by Indi Kernick on 22/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef population_hpp
#define population_hpp

#include <vector>
#include <random>
#include "chromosome.hpp"

template <typename Chromosome>
using Population = std::vector<Chromosome>;

template <typename Chromosome>
Population<Chromosome> makePopulation(const size_t size) {
  return {size};
}

template <typename Chromosome>
void initRandom(Population<Chromosome> &pop, const Allele<Chromosome> seed) {
  std::mt19937_64 gen(seed);
  std::uniform_int_distribution<Allele<Chromosome>> dist;
  for (Chromosome &c : pop) {
    for (Allele<Chromosome> &a : c) {
      a = dist(gen);
    }
  }
}

#endif
