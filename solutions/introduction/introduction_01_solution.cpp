// Copyright 2019-2024 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <ygm/comm.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  //////////////////////////////////////////////////
  // Step 1: Print the number of ranks only once. //
  //////////////////////////////////////////////////

  //One possible solution:
  if(world.rank() == 0) {
    std::cout << "Total number of ranks = " << world.size() << std::endl;
  }
  
  //Another possible solution:
    if(world.rank0())  { //simpler way to find Rank 0
    std::cout << "Total number of ranks = " << world.size() << std::endl;
  }

  //Another solution using convenience cout functions:
  world.cout0("Total number of ranks = ", world.size());


  world.barrier();
  /////////////////////////////////////////////////////////////
  // Step 2: Print a message and rank number from all ranks. //
  /////////////////////////////////////////////////////////////

  
  // Possible solution directly using std::cout
  std::cout << "Howdy from rank " << world.rank() << std::endl;

  // Another solution using convenience cout functions:
  world.cout("Howdy from rank ", world.rank());

  ///////////////////////////////////////////////////////////// //
  // Note the difference between world.cout() and world.cout0() //
  ///////////////////////////////////////////////////////////// //
  
}