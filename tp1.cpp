#include <iostream>
#include <vector>
#include "parser.argumentos.hpp"
#include "loader.preferencias.hpp"
#include "gale_shapley.hpp"

using namespace std;

int main(int ac, char* av[]) {
  auto tuple = parse_command_line(ac, av);
  auto n = std::get<0>(tuple);
  auto m = std::get<1>(tuple);
  auto p = std::get<2>(tuple);

  vector<vector<uint32_t>> compatibilidades( n, vector<uint32_t>(m,0));
  vector<vector<uint32_t>> factibilidades( m, vector<uint32_t>(n,0));

  load_compatibilidades(compatibilidades);   // Cargamos preferencias de pacientes.
  load_factibilidades(factibilidades);       // Cargamos preferencias de donantes.

  gale_shapley(compatibilidades,factibilidades,p); // Generamos emparejamientos.

}
