#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <tuple>
using namespace std;

std::tuple<uint32_t, uint32_t, char>  parse_command_line(int ac, char* av[]) {
    try {

        po::options_description desc("Parametros Esperados");
        desc.add_options()
            ("N", po::value<uint32_t>(), "Numero de Pacientes (n)")
            ("M", po::value<uint32_t>(), "Numero de Donantes (m)")
            ("S", po::value<char>()->default_value('p'), "p: pacientes - d: donantes")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);    

        // Se retorna (N,M,S), p. ej.: (10,30,p)
        return std::make_tuple(
            vm["N"].as<uint32_t>(), 
            vm["M"].as<uint32_t>(),
            vm["S"].as<char>() == 'd' ? 'd' : 'p'
        );


    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        exit(1);
    }
}

