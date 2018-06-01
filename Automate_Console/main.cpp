/**
 * Project Untitled
 */



/**
 * Main implementation
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

#include "Automate.h"
#include "Transition.h"
#include "Etat.h"
using namespace std;


string loadedText;

// Permet de récupérer le texte d'un fichier pour conversion
void ChargerFichier(string nom)
{
	ifstream myfile(nom + ".txt");

	// eof signifie end of file, on regarde ainsi l'index de fin du fichier

	if (myfile.is_open())
	{
		if (myfile.peek() == std::ifstream::traits_type::eof())
		{
			cout << "Fichier existant mais vide\n" << endl;
			return;
		}
		string line;
		cout << " \n-- Tentative chargement :" << nom << ".txt" <<"  -- \n" << endl;
		while (getline(myfile, line))
		{

			cout << line << '\n';
			loadedText += (line + "\n");
		}
		myfile.close();

		// on vérifie si le fichier n'est pas vide

			cout << "\n --	Chargement OK	  -- \n" << endl;
	}
	else cout << "Impossible d'ouvrir le fichier\n" << endl;
}

// Lance le menu principal


void LancerMenu() 
{
	std::string nomFichier = "test";
	int choix = 1;
	do
	{
		cout << "------Choisissez l'option : ------" << endl;
		cout << "1.Charger un fichier txt" << endl;
		cout << "2.Table de transitions" << endl;
		cout << "3.Quitter" << endl;

		ChargerFichier(nomFichier);
		cout << "> Fichier charge : " << nomFichier << endl;

		cout << "\nVotre choix:  ";
		cin >> choix;

		switch (choix)
		{
		case 1:
			// Permet de lire le contenu du fichier texte fourni
			cout << "Entrez le nom du fichier : ";
			cin >> nomFichier;
			ChargerFichier(nomFichier);
			break;
		case 2:
			if (!nomFichier.empty())
			{
				Automate A(loadedText);
			}
			else
			{
				cout << "Veuillez d'abord charger un fichier\n" << endl;
			}
			break;
		case 3:
			return;
			break;
		default:
			cout << "Veuillez entrer une valeur valide\n" << endl;
			break;
		}
	} while (true);

	
}

int main()
{
		LancerMenu();

	// permet d'empêcher le programme de se fermer directement
	std::getchar();
}

void LancerTests() 
{

}

void Convertir()
{

}

