// Copyright 2019-2025 Lawrence Livermore National Security, LLC and other YGM
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

  ygm::container::bag<std::string> mybag(
      world, {"one", "fish", "two", "fish", "red", "fish", "blue", "fish"});

  ygm::container::set<std::string> myset(
      world, {"one", "fish", "two", "fish", "red", "fish", "blue", "fish"});

  //////////////////////////////////////////////////////////////////////////////
  // Step 1: Print and compare the partitioning of elements between bag & set //
  //////////////////////////////////////////////////////////////////////////////

  auto bag_printer = [&world](const std::string& s) {
    world.cout(s, " in bag");
  };
  mybag.for_all(bag_printer);

  auto set_printer = [&world](const std::string& s) {
    world.cout(s, " in set");
  };
  myset.for_all(set_printer);

  ////////////////////////////////////////////////////////////////////////////////
  // Note how the output from all the ranks gets interleaved in                 //
  // nondeterministic order.   Compare with multiple runs.                      //
  ////////////////////////////////////////////////////////////////////////////////
}