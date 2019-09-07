#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void load_file_data_into_vector(vector<vector<uint32_t>>& vec, string filename ) {
  ifstream fs{filename, ios_base::in};

  string line;
  string token;
  size_t i = 0;
  while ( getline(fs,line) ) {

    istringstream buffer(line);
    for( size_t j = 0; getline( buffer, token, ',' ); ++j ) {
      if ( j == 0 ) continue;
      vec[i][j-1] = std::stoi(token);
    }

    ++i;
  } 

  fs.close();
}

void load_compatibilidades(vector<vector<uint32_t>>& vec) {
  load_file_data_into_vector(vec, "compatibilidades.txt");
}

void load_factibilidades(vector<vector<uint32_t>>& vec) {
  load_file_data_into_vector(vec, "factibilidades.txt");
}
