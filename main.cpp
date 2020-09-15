#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <unistd.h>
#include <unordered_set>

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

int main(int argc, char* argv[]) {
  string filenameIN, filenameOUT, linea;
  int c, segundos, i;
  vector<string> lineaSpliteada; //["e","3","2"]
  vector<vector<string>> todosLosArcos; //[["e","3","2"],["e","4","6"]]
  vector<int> ordenNodos;
  unordered_set<int> listaNodos;
  
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
	
	while(getline(fileIn, linea)){
		lineaSpliteada = split(linea," ");
		if(lineaSpliteada[0] == "e"){
			todosLosArcos.push_back(lineaSpliteada);
		}
	}
	for(i=0; i < todosLosArcos.size(); i++){
		listaNodos.insert(stoi(todosLosArcos[i][1]));
	}

        for(i=0; i < todosLosArcos.size(); i++){
                listaNodos.insert(stoi(todosLosArcos[i][2]));
        }

	for(auto iter = listaNodos.begin(); iter != listaNodos.end(); iter++){
		ordenNodos.insert(ordenNodos.begin(),*iter); 
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
