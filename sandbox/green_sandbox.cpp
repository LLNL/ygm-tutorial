// Copyright 2019-2025 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <ygm/comm.hpp>
#include <ygm/container/set.hpp>
#include <ygm/container/array.hpp>

#include <faker-cxx/number.h>
#include <faker-cxx/string.h>
#include <faker-cxx/date.h>
#include <faker-cxx/internet.h>
#include <faker-cxx/person.h>
#include <faker-cxx/sport.h>
#include <faker-cxx/music.h>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);


  world.cout(faker::music::artist());
}
