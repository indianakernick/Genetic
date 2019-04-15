//
//  main.cpp
//  Genetic
//
//  Created by Indi Kernick on 22/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <iostream>

#include "mutate.hpp"
#include "fitness.hpp"
#include "poly fit.hpp"
#include "crossover.hpp"
#include "select parents.hpp"

void printChromo(PolyChromo chromo) {
  std::cout << "y = " <<
    chromo[0] << " + " <<
    chromo[1] << "x + " <<
    chromo[2] << "x^2\n";
}

PolyTable table;

PolyFitness fitnessFun(const PolyChromo &chromo) {
  return polyFitness(chromo, table);
}

void initTable() {
  for (int x = -200; x <= 200; ++x) {
    table.push_back({double(x), 5.0*x*x + 2.0*x - 9.0});
  }
}

int main(int, const char **) {
  initTable();

  Population<PolyChromo> pop = makePopulation<PolyChromo>(2 * 1024);
  std::vector<PolyFitness> fitness(pop.size());
  Population<PolyChromo> parents(pop.size() / 2);
  Seed seed = 674;
  seed = initRandom(pop, seed);
  
  int gen = 0;
  
  while (gen < 10000) {
    PROFILE(Generation);
    
    if (gen % 500 == 0) {
      std::cout << gen << '\n';
    }
  
    calcFitness(pop, fitness, &fitnessFun);
    fitnessSort(pop, fitness);
    seed = copyRandomFitest(parents, pop, fitness, seed);
    {
      PROFILE(Breed);
      for (size_t p = 0; p != parents.size(); p += 2) {
        seed = uniformCrossover(parents[p], parents[p + 1], 0.4f, seed);
        seed = randomAdd(parents[p], PolyAllele(2), 0.2f, seed);
        seed = randomAdd(parents[p + 1], PolyAllele(2), 0.2f, seed);
      }
    }
    replaceWeakest(pop, parents);
    gen++;
  }
  
  std::cout << gen << '\n';
  std::cout << "Fitness " << fitness[0] << '\n';
  std::cout << "Chromo  ";
  printChromo(pop[0]);
  
  std::cout << '\n';
  
  PROFILER_INFO(stdout);
  
  return 0;
}
