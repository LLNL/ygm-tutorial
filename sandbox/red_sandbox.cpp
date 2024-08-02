// Copyright 2019-2021 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <ygm/comm.hpp>
#include <ygm/container/bag.hpp>

int main(int argc, char** argv) {
  //
  // Modify the following code to write print out the number of processors
  {
    ygm::comm world(&argc, &argv);

    world.cout("Howdy from ", world.rank());
  }

  //
  // Modify the following code to print out the async sender
  {
    ygm::comm world(&argc, &argv);
    ASSERT_RELEASE(world.size() > 1);

    auto my_first_async = []() {
      std::cout << "Received async from " << /*finish me <<*/ std::endl;
    };

    world.async(0, my_first_async);
  }

  //
  // Word counter using counting set

  //
  // Word counter using reduce_by_key

  //
  // Print out only the even numbers using filter

  //
  // Count the number of even numbers using filter, map & reduce
  // {
  //   ygm::comm                world(&argc, &argv);
  //   ygm::container::bag<int> ibag(world, {3, 1, 4, 1, 5});
  //   ibag.filter([](int i) { return i % 2 == 0; })
  //       .map([](int i) { return size_t(1); })
  //       .reduce(std::plus<size_t>());
  // }



  // line, csv, json

  return 0;
}