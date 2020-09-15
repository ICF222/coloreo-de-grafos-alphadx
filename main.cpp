#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <unistd.h>

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
// g++ main.cpp -o main.exe
// ./main -f ./archivos/grafo1 -s ./archivos/pruebas1 -o ./archivos/grafo1_pruebas1.sal

int main(int argc, char* argv[]) {
  string filenameIN, filenameOUT;
  int c, segundos;
  
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


  fileOut.close();
  
  return 0;

}