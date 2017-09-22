//
//  parent.hpp
//  Genetic
//
//  Created by Indi Kernick on 22/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef parent_hpp
#define parent_hpp

#include "population.hpp"

template <typename Chromosome, typename Fitness>
Seed selectParents(
  Population<Chromosome> &parents,
  const Population<Chromosome> &population,
  const std::vector<Fitness> &fitnesses,
  const Seed seed
) {
  assert(parents.size() <= population.size());
  assert(population.size() == fitnesses.size());
  
  const Fitness fitnessSum = std::accumulate(fitnesses.cbegin(), fitnesses.cend(), 0);
  Generator gen(seed);
  Distribution<Fitness> dist(0, fitnessSum);
  
  for (Chromosome &p : parents) {
    Fitness choice = dist(gen);
    for (size_t f = 0; f != fitnesses.size(); ++f) {
      const Fitness fitness = fitnesses[f];
      if (choice < fitness) {
        p = population[f];
        break;
      }
      choice -= fitness;
    }
  }
  return gen();
}

#endif
