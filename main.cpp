#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <unistd.h>
#include <set>

using namespace std;

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
// g++ main.cpp -o solver
// ./solver -i ./Instancias/ejemplo1.in -o ./Salidas/ejemplo1.out -t 2


//Al final el unordered_set no me garantiza que todos los elementos sean ingresados en el orden que aparecen, así que 
//utilizaré el set sólo para verificar si un nodo ya había sido agregado anteriormente
int main(int argc, char* argv[]) {
  string filenameIN, filenameOUT, linea;
  int c, segundos, i;
  vector<string> lineaSpliteada; //["e","3","2"]
  vector<vector<string>> todosLosArcos; //[["e","3","2"],["e","4","6"]]
  vector<int> ordenNodos;
  set<int> nodosExistentes; //este set sólo me servirá para ver si ya había agregado antes el elemento
  
  extern char *optarg;
  opterr = 0;
  
  while ((c = getopt (argc, argv, "i:o:t:")) != -1){
      switch (c){
          case 'i':
              filenameIN = optarg;
              break;
          case 'o':
              filenameOUT = optarg;
              break;
          case 't':
              segundos = stoi(optarg);
              break;
          default:
              abort ();
      }
  }
  //Primer Archivo
	fstream fileIn(filenameIN);

	if (!fileIn.is_open()) {
		fileIn.open(filenameIN, ios::in);
	}

	
  
  //Archivo de Salida
  ofstream fileOut(filenameOUT);

	if (!fileOut.is_open()) {
		fileOut.open(filenameOUT);
	}
//primero se leerá línea a línea para buscar los arcos "e de edge"
//y cada uno de ellos se agregará en un vector de vectores de string (como expliqué en clases)
	while(getline(fileIn, linea)){
		lineaSpliteada = split(linea," ");
		if(lineaSpliteada[0] == "e"){
			todosLosArcos.push_back(lineaSpliteada);
		}
	}
//acá es donde hice el cambio.  Primero en lugar de hacer 2 for separados,
//hice sólo un for anidado que haga 2 veces el ciclo.  Así evito repetir código
	for(i=1; i <= 2; i++){
//en el siguiente for con j=0 hasta todas las líneas con letra "e", se
//recorren todas las listas (o vectores) que se armaron
//en el paso anterior... donde en todosLosArcos[j][i] está cada nodo.
//cuando i = 1 se lee la primera columna y cuando i = 2, se lee la segunda.
//e i j <--- en el vector "todosLosArcos", cada elemento corresponde a una líneas que se ven de esa forma
//en el archivo de entrada

		for(int j=0; j < todosLosArcos.size(); j++){
			int largoAnterior = nodosExistentes.size();
			int elemento = stoi(todosLosArcos[j][i]);
			nodosExistentes.insert(elemento);
//acá sucede la magia.  Como ven en el siguiente IF (nodosExistentes crecerá si en el insert anterior
//el elemento no estaba, pero quedará igual si el elemento ya estaba.
//si el tamaño cambia, eso quiere decir que ese elemento es nuevo y hay que agregarlo al vector
//ordenNodos
			if(nodosExistentes.size() != largoAnterior){
				ordenNodos.push_back(elemento);
			}
		}
	}
	
	for(i=0; i < ordenNodos.size(); i++){
                cout << ordenNodos[i] << " ";
        }
	cout << endl;


//e 1 2
//e 2 3
//e 4 5
//1 2 4 3 5

  fileOut.close();
  
  return 0;

}
