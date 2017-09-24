//
//  mutate.hpp
//  Genetic
//
//  Created by Indi Kernick on 23/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef mutate_hpp
#define mutate_hpp

#include "random.hpp"
#include "chromosome.hpp"

template <typename Allele, size_t LENGTH>
Seed randomReset(
  Chromosome<Allele, LENGTH> &chromosome,
  const float prob,
  const Seed seed
) {
  Generator gen(seed);
  Distribution<float> probDist(0.0f, 1.0f);
  Distribution<Allele> alleleDist;
  
  for (Allele &a : chromosome) {
    //always invoke Generator::operator() the same number of times to
    //keep execution deterministic
    const Allele randAllele = alleleDist(gen);
    if (probDist(gen) < prob) {
      a = randAllele;
    }
  }
  
  return gen();
}

template <typename Allele, size_t LENGTH>
Seed randomAdd(
  Chromosome<Allele, LENGTH> &chromosome,
  const Allele addMag,
  const float prob,
  const Seed seed
) {
  Generator gen(seed);
  Distribution<float> probDist(0.0f, 1.0f);
  Distribution<Allele> alleleDist(-addMag, addMag);
  
  for (Allele &a : chromosome) {
    //always invoke Generator::operator() the same number of times to
    //keep execution deterministic
    const Allele randAdd = alleleDist(gen);
    if (probDist(gen) < prob) {
      a += randAdd;
    }
  }
  
  return gen();
}

#endif
