//
//  random.hpp
//  Genetic
//
//  Created by Indi Kernick on 22/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef random_hpp
#define random_hpp

#include <random>

using Generator = std::mt19937;

using Seed = typename Generator::result_type;

template <typename Allele>
using Distribution = std::conditional_t<
  std::is_integral<Allele>::value,
  std::uniform_int_distribution<Allele>,
  std::uniform_real_distribution<Allele>
>;

#endif
