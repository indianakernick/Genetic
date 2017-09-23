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

template <typename Chromosome, typename Fitness>
void fitnessSort(Population<Chromosome> &pop, std::vector<Fitness> &fitnesses) {
  //@TODO this feels really inefficient 3n + n*log(n)
  //implement quicksort by hand
  
  assert(pop.size() == fitnesses.size());
  
  static std::vector<size_t> order;
  static std::vector<bool> isSorted;
  if (order.size() < pop.size()) {
    order.resize(pop.size());
    isSorted.resize(pop.size());
  }
  std::iota(order.begin(), order.begin() + pop.size(), 0);
  std::fill(isSorted.begin(), isSorted.end(), false);
  
  std::sort(order.begin(), order.begin() + pop.size(), [&fitnesses] (size_t a, size_t b) {
    return fitnesses[a] > fitnesses[b];
  });
  
  for (size_t i = 0; i != pop.size(); ++i) {
    if (isSorted[i]) {
      continue;
    }
    isSorted[i] = true;
    size_t currentPos = i;
    size_t sortedPos = order[i];
    while (currentPos != sortedPos) {
      std::swap(pop[currentPos], pop[sortedPos]);
      std::swap(fitnesses[currentPos], fitnesses[sortedPos]);
      isSorted[sortedPos] = true;
      currentPos = sortedPos;
      sortedPos = order[sortedPos];
    }
  }
}

#endif
