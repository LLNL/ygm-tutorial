// Copyright 2019-2024 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <string>
#include <ygm/comm.hpp>
#include <ygm/container/bag.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  //////////////////////////////////////////////////////////////
  // Step 1: Compute the number of unique strings in the bag. //
  //////////////////////////////////////////////////////////////

  ygm::container::bag<std::string> mybag(
      world, {"red", "orange", "yellow", "red", "green", "cyan", "red", "blue",
              "green", "magenta", "purple"});



  /////////////////////////////////////////////////////////////
  // Step 2: Count the number of "green"s in the bag.        //
  /////////////////////////////////////////////////////////////


  /////////////////////////////////////////////////////////////
  // Step 3: Find the most frequently occuring string        //
  /////////////////////////////////////////////////////////////
}