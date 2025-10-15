// Copyright 2019-2025 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <ygm/comm.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  //////////////////////////////////////////////////////////////////////
  // Step 1: Modify the following code to print out the async sender. //
  //////////////////////////////////////////////////////////////////////
  auto my_first_async = []() {
    std::cout << "Received async from " << /*finish me <<*/ std::endl;
  };

  world.async(0, my_first_async);

  // Use a barrier to separate your steps
  world.barrier();
}