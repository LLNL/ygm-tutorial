#include <ygm/comm.hpp>
#include <ygm/io/line_parser.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  std::vector<std::string> filenames = {"data/loremipsum.txt"};
  ygm::io::line_parser lp(world, filenames);

  /////////////////////////////////////////////////////////////
  // Step 1: Print all the lines in the input file.          //
  /////////////////////////////////////////////////////////////
  lp.for_all([&world](std::string line) {
    world.cout(line);
    // You could process each line here as needed.
  });
  // Note, if file was larger (>8MB) then the parsing would be parallelized.

  /////////////////////////////////////////////////////////////
  // Step 2: Count all the lines in the file.                //
  /////////////////////////////////////////////////////////////
  size_t count = lp.transform([](auto s) -> size_t {
                     return 1;
                   }).reduce(std::plus<size_t>());
  world.cout0(count);
}