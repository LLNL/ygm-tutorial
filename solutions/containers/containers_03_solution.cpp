// Copyright 2019-2024 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <map>
#include <string>
#include <ygm/comm.hpp>
#include <ygm/container/bag.hpp>
#include <ygm/container/set.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  ygm::container::bag<int> mybag(world);

  if (world.rank0()) {
    for (int i = 0; i < 100; ++i) {
      mybag.async_insert(i);
    }
  }

  ///////////////////////////////////////////////////
  // Step 1: Add up all the even numbers in mybag. //
  ///////////////////////////////////////////////////

  int even_sum = mybag.filter([](int i){return i%2==0;}).reduce(std::plus<int>());

  world.cout0("Sum of even numbers = ", even_sum);
}