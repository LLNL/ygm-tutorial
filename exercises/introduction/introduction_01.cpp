// Copyright 2019-2025 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <ygm/comm.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  //////////////////////////////////////////////////
  // Step 1: Print the number of ranks only once. //
  //////////////////////////////////////////////////


  // Use a barrier to seperate your steps
  world.barrier(); 



  /////////////////////////////////////////////////////////////
  // Step 2: Print a message and rank number from all ranks. //
  /////////////////////////////////////////////////////////////



  /////////////////////////////////////////////////////
  // Step 3: Ask your neighbor to print their rank.  //
  /////////////////////////////////////////////////////
}