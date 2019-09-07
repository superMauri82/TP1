#include <iostream>
#include <vector>

using namespace std;

void gale_shapley(const vector<vector<uint32_t>>& comp,
                  const vector<vector<uint32_t>>& fact,
                  char solicitantes) {

  for ( size_t i = 0; i < comp.size(); ++i ) {
    cout << "paciente-"<< i << ": ";
    for ( size_t j = 0; j < comp[i].size(); ++j ) {
      cout << "donante-"<< comp[i][j] << " | " ;
    }
    cout << endl;
  }

  for ( size_t i = 0; i < fact.size(); ++i ) {
    cout << "donante-"<< i << ": ";
    for ( size_t j = 0; j < fact[i].size(); ++j ) {
      cout << "paciente-"<< fact[i][j] << " | " ;
    }
    cout << endl;
  }
}
