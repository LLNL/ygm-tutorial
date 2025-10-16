#include <ygm/comm.hpp>
#include <ygm/io/parquet_parser.hpp>

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  std::vector<std::string> filenames = {"data/"};
  ygm::io::parquet_parser parquetp(world, filenames);

  const auto&             schema = parquetp.get_schema();

  world.cout0(schema[0].name, "\t", schema[1].name, "\t", schema[2].name);
}