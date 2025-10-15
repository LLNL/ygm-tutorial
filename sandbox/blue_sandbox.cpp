// Copyright 2019-2025 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <ygm/comm.hpp>
#include <ygm/container/map.hpp>
#include <ygm/container/set.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  world.welcome();

  return 0;
}
