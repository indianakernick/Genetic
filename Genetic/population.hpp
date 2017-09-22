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
class Population {
public:
  Population(const size_t size, const Allele<Chromosome> seed)
    : population(size) {
    std::mt19937_64 generator(seed);
    std::uniform_int_distribution<Allele<Chromosome>> dist;
    for (Chromosome &c : population) {
      for (Allele<Chromosome> &a : c) {
        a = dist(generator);
      }
    }
  }
  
private:
  std::vector<Chromosome> population;
};

#endif
