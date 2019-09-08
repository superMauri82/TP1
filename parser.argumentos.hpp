#include <iostream>
#include <tuple>
#include <regex>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

std::tuple<uint32_t, uint32_t, char> tuple_from_string(const string & str) {
  regex r(R"(--N\s*(\d+)\s*--M\s*(\d+)\s*--S\s*(p|d){1})");
  std::smatch sm;
  regex_search(str, sm, r);
  if ( sm.ready() && sm.size() == 4 ) {
    string N = sm[1];
    string M = sm[2];
    string S = sm[3];

    return make_tuple(static_cast<uint32_t>(stoul(N)),
                      static_cast<uint32_t>(stoul(M)),
                      S[0]);
  }

  throw std::runtime_error("Parametros (y orden) esperados: --N (num) --M (num) --S (p/d)"); 
}

std::tuple<uint32_t, uint32_t, char> parse_command_line(int ac, char* av[]) {
    try {
      ostringstream oss{"",ios::ate};
      for(size_t i=1; i < ac; ++i) {
        oss << av[i] << ' ' ;
      }
      string str_parameters = oss.str();
      return tuple_from_string(str_parameters);
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        exit(1);
    }
}

