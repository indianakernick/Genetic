//
//  parent.hpp
//  Genetic
//
//  Created by Indi Kernick on 22/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef parent_hpp
#define parent_hpp

#include <cassert>
#include "population.hpp"

///Randomly copies individuals with fitter individuals more likely to be copied
template <typename Chromosome, typename Fitness>
Seed copyRandomFitest(
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

///Copies the top fitest individuals from the population
template <typename Chromosome, typename Fitness>
void copyFitest(
  Population<Chromosome> &fitest,
  const Population<Chromosome> &population,
  const std::vector<Fitness> &fitnesses,
  std::vector<size_t> &order
) {
  assert(fitest.size() < population.size());
  assert(population.size() == fitnesses.size());
  
  if (order.size() != population.size()) {
    order.resize(population.size());
  }

  //order is a vector of indicies onto population
  //order is sorted by fitness in decending order
  //the index at the beginning of order refers to
  //the fitest chromosome in the population
  std::iota(order.begin(), order.end(), 0);
  std::sort(order.begin(), order.end(), [&fitnesses] (const size_t l, const size_t r) {
    return fitnesses[l] > fitnesses[r];
  });
  for (size_t c = 0; c != fitest.size(); ++c) {
    fitest[c] = population[order[c]];
  }
}

#endif
