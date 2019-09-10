#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool hay_solicitante_libre(const vector<int32_t>& matchings, size_t& idx) {
  for (size_t i = 0 ; i < matchings.size() ; ++i ) {
    if ( matchings[i] == -1 ) {
      idx = i;
      return true;
    }
  }
  return false;
}

bool agoto_lista_de_preferencias(vector<int32_t>& solicitantes, 
    const vector<vector<uint32_t>>& preferencias,
    const size_t& idx_solicitante,
    size_t& idx_proximo_requerido) {

  auto proximo_requerido = ++solicitantes[idx_solicitante]; 
  idx_proximo_requerido = preferencias[idx_solicitante][proximo_requerido];
  idx_proximo_requerido--; // recuperamos 0 based index.

  return proximo_requerido == preferencias[0].size(); // este chequeo indica haber recorrido toda 
                                                      // la lista de preferencias para solicitante
                                                      // con indice idx_solicitante.
}

bool requerido_esta_libre(const vector<int32_t>& matchings, 
                          const size_t& idx, 
                          size_t& actual_pareja ) {
  for (size_t i = 0 ; i < matchings.size() ; ++i ) {
    if ( matchings[i] == idx ) {
      actual_pareja = i;
      return false;
    }
  }
  return true;
}

void gale_shapley_impl(
    const vector<vector<uint32_t>>& prefs, 
    const vector<vector<uint32_t>>& mat_comp, 
    vector<int32_t>& solicitantes, 
    vector<int32_t>& matchings) {

  size_t idx_solicitante;
  size_t idx_proximo_requerido;
  size_t actual_pareja;
  while( hay_solicitante_libre(matchings, idx_solicitante) && 
         !agoto_lista_de_preferencias(solicitantes, prefs, idx_solicitante, idx_proximo_requerido) ) {

    auto oferente      = idx_solicitante;
    auto requerido     = idx_proximo_requerido;

    if ( requerido_esta_libre(matchings, requerido, actual_pareja) ) {

      matchings[oferente] = requerido;

    }
    else { 

      if ( mat_comp[requerido][actual_pareja] < mat_comp[requerido][oferente] ) {
        // oferente queda libre
      }
      else {
        matchings[oferente]      = requerido;
        matchings[actual_pareja] = -1; // actual pareja de requerido queda libre.
      }

    }
  }
}

void imprimir_resultados(const vector<int32_t>& matchings, char quien_solicita) {
  ofstream file_resultados;
  file_resultados.open ("resultados.txt");
  
  if (quien_solicita == 'p') {
    for(size_t i=0; i < matchings.size(); ++i) {
      file_resultados << i + 1 <<  "," << matchings[i] + 1 << std::endl;
    }
  }
  else {
    for(size_t i=0; i < matchings.size(); ++i) {
      file_resultados << matchings[i] + 1 << "," <<  i + 1 << std::endl;
    }
  }

  file_resultados.close();
}

void gale_shapley(const vector<vector<uint32_t>>& comp,
                  const vector<vector<uint32_t>>& fact,
                  char  quien_solicita) {

  vector<vector<uint32_t>> matriz_comparacion{};
  vector<int32_t> solicitantes{};
  vector<int32_t> requeridos{};
  vector<int32_t> matchings{};

  if ( quien_solicita == 'p' ) {
    solicitantes       = vector<int32_t>(comp.size(),-1);
    matchings          = vector<int32_t>(comp.size(),-1);
    matriz_comparacion = fact; // si solicitan los pacientes construimos 
                               // matrix de dimensiones iguales a fact.
                               // porque el requerido definirá de acuerdo
                               // a las prioridades expresadas en el arch.
                               // de FACTIBILIDADES.
    
    for ( size_t i = 0; i < fact.size(); ++i ) {
      for ( size_t j = 0; j < fact[i].size(); ++j ) {
        auto idx_sol = fact[i][j];
        matriz_comparacion[i][--idx_sol] = j + 1;
      }
    }

    gale_shapley_impl(comp, matriz_comparacion, solicitantes, matchings);

  }
  else {
    solicitantes       = vector<int32_t>(fact.size(),-1);
    matchings          = vector<int32_t>(fact.size(),-1);
    matriz_comparacion = comp; // si solicitan los donantes construimos
                               // matrix de dimensiones iguales a comp.
                               // porque el requerido definirá de acuerdo
                               // a las prioridades expresadas en el arch.
                               // de COMPATIBILIDADES.

    for ( size_t i = 0; i < comp.size(); ++i ) {
      for ( size_t j = 0; j < comp[i].size(); ++j ) {
        auto idx_sol = comp[i][j];
        matriz_comparacion[i][--idx_sol] = j + 1;
      }
    }

    gale_shapley_impl(fact, matriz_comparacion, solicitantes, matchings);

  }

  imprimir_resultados(matchings, quien_solicita);

}

