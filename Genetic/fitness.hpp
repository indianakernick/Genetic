//
//  fitness.hpp
//  Genetic
//
//  Created by Indi Kernick on 23/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef fitness_hpp
#define fitness_hpp

#include <cassert>
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

template <typename Fitness>
Fitness median(const Fitness a, const Fitness b, const Fitness c) {
  //https://stackoverflow.com/a/19027761
  return std::max(std::min(a, b), std::min(std::max(a, b), c));
}

template <typename PopIter, typename FitIter>
void fitnessSortImpl(
  const PopIter popBegin,
  const FitIter fitBegin,
  const size_t size
) {
  if (size < 2) {
    return;
  } else if (size == 2) {
    if (fitBegin[0] < fitBegin[1]) {
      std::swap(fitBegin[0], fitBegin[1]);
      std::swap(popBegin[0], popBegin[1]);
    }
    return;
  }

  const auto pivot = median(*fitBegin, fitBegin[size / 2], fitBegin[size - 1]);
  FitIter left = fitBegin;
  FitIter right = fitBegin + size - 1;
  
  while (left <= right) {
    //descending order
    while (*left > pivot) {
      ++left;
    }
    while (*right < pivot) {
      --right;
    }
    if (left <= right) {
      std::swap(*left, *right);
      //the reason why I can't just use std::sort
      std::swap(popBegin[left - fitBegin], popBegin[right - fitBegin]);
      ++left;
      --right;
    }
  }
  
  const size_t between = (left - fitBegin);
  fitnessSortImpl(popBegin, fitBegin, between);
  fitnessSortImpl(popBegin + between, left, size - between);
}

template <typename Chromosome, typename Fitness>
void fitnessSort(Population<Chromosome> &pop, std::vector<Fitness> &fitnesses) {
  assert(pop.size() == fitnesses.size());
  fitnessSortImpl(pop.begin(), fitnesses.begin(), pop.size());
}

#endif
