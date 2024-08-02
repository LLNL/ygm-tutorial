// Copyright 2019-2021 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <ygm/comm.hpp>
#include <ygm/container/map.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  world.cout("Howdy from ", world.rank());

  //
  // Practice with async_visit and for_all
  {
    ygm::container::map<std::string, std::string> favorite_colors(world);
    if (world.rank0()) {
      favorite_colors.async_insert("Andy", "Orange");
      favorite_colors.async_insert("Colin", "Blue");
      favorite_colors.async_insert("Drake", "Green");
      favorite_colors.async_insert("Sonja", "Yellow");
      favorite_colors.async_insert("Rachel", "Orange");
      favorite_colors.async_insert("Jess", "Green");
    }
    world.barrier();

    // Print names and favorite colors in a for_all
    favorite_colors.for_all(/* Your lambda here */);

    // Print names of people whose favorite color is "Green"
    favorite_colors.for_all(/* Your lambda here */);

    // Create a set of names we are interested in
    ygm::container::set<std::string> characters_of_interest(world);
    characters_of_interest.async_insert("Colin");
    characters_of_interest.async_insert("Jess");
    characters_of_interest.async_insert(
        "Max");  // Not in map of favorite colors

    // Print favorite colors of names in set using async_visit
    characters_of_interest.for_all([&favorite_colors](const std::string& name) {
      favorite_colors.async_visit(
          name, /* Write lambda to print favorite color here */);
    });

    // Re-run your for_all on favorite_colors to print all favorite colors. What
    // happened since you first printed?

    // Let's add a favorite color for Max
    if (world.rank0()) {
      favorite_colors.async_insert("Max", "Orange");
    }
    world.barrier();

    // Add a new interesting character as well
    if (world.rank0()) {
      characters_of_interest.async_insert("Jake");
    }
    world.barrier();

    // Print the favorite colors of our characters of interest in a way that
    // doesn't create any new entries using async_visit_if_contains instead of
    // async_visit

    // Do the same, but print a message for any character of interest without a
    // favorite color as well using async_contains.
    // Hint: The lambda given to
    // async_contains is provided an extra boolean as a first argument
    // indicating whether the key exists. This allows you to control behavior
    // based on whether the key exists or not.
  }

  return 0;
}
