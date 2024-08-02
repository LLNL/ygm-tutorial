// Copyright 2019-2024 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <map>
#include <string>
#include <ygm/comm.hpp>
#include <ygm/container/bag.hpp>
#include <ygm/container/counting_set.hpp>
#include <ygm/container/set.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  ygm::container::bag<std::string> mybag(
      world, {"red", "orange", "yellow", "red", "green", "cyan", "red", "blue",
              "green", "magenta", "purple"});

  //////////////////////////////////////////////////////////////
  // Step 1: Compute the number of unique strings in the bag. //
  //////////////////////////////////////////////////////////////

  {
    ygm::container::set<std::string> myset(world, mybag);

    world.cout0("Number of unique strings: ", myset.size());
  }

  /////////////////////////////////////////////////////////////
  // Step 2: Count the number of "green"s in the bag.        //
  /////////////////////////////////////////////////////////////

  {
    ygm::container::counting_set<std::string> cset(world, mybag);

    std::map<std::string, size_t> kg = cset.key_gather({"green"});
    world.cout0("Number of greens: ", kg["green"]);
  }

  /////////////////////////////////////////////////////////////
  // Step 3: Find the most frequently occuring string        //
  /////////////////////////////////////////////////////////////
}