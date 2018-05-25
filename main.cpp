#include <iostream>
#include <fstream>


using namespace std;


int main()
{


    // Permet de lire le contenu du fichier texte fourni
      ifstream myfile ("test.txt");
      if (myfile.is_open())
  {
    string line;
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }
    else cout << "Impossible d'ouvrir le fichier";
    return 0;
}
