//
//  chromosome.hpp
//  Genetic
//
//  Created by Indi Kernick on 22/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef chromosome_hpp
#define chromosome_hpp

#include <array>

template <typename Allele, size_t LENGTH>
using Chromosome = std::array<Allele, LENGTH>;

template <typename Chromosome>
using Allele = typename Chromosome::value_type;

template <typename Chromosome>
constexpr size_t LENGTH = std::tuple_size<Chromosome>::value;

#endif
