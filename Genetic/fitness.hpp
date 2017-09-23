//
//  fitness.hpp
//  Genetic
//
//  Created by Indi Kernick on 23/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef fitness_hpp
#define fitness_hpp

#include "population.hpp"

template <typename Chromosome, typename Fitness, typename FitnessFun>
void calcFitness(
  const Population<Chromosome> &pop,
  std::vector<Fitness> &fitnesses,
  FitnessFun &&fun
) {
  assert(pop.size() == fitnesses.size());
  
  for (size_t i = 0; i != pop.size(); ++i) {
    fitnesses[i] = fun(pop[i]);
  }
}

#endif
