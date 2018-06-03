/*
 * Project Untitled
 */


#include "Automate.h"
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <vector>

/**
 * Automate implementation
 */



void Automate::AfficherTransitions()
{
	std::cout << "Fonction AfficherTransitions()"  << std::endl;
	for (int i = 0; i < nbTransitions; i++)
	{
		listeTransitions[i].Afficher();
	}
}


void Espacer(int espace)
{
	for (int e = 0; e < espace; e++)
	{
		std::cout << " ";
	}
}

Automate::Automate(std::string texte)
{
	std::cout << "Generation ..." << std::endl;
	std::istringstream f(texte);
	std::string line;
	int i = 0;

	// On demande à parcourir chaque ligne d'indice i du fichier texte
	while (std::getline(f, line))
	{
		if (i == 0)
		{
			// stoi signifie string to int, c'est ainsi une conversion
			nbSymboles = std::stoi(line);
			std::cout << ">>	nombre symboles : " << nbSymboles << std::endl;
		}
		else if (i == 1)
		{
			// Même principe
			nbEtats = std::stoi(line);
			std::cout << ">>	nombre etats : " << nbEtats << std::endl;
		}
		else if (i == 2)
		{
			// Il faut détecter le premier nombre qui constitue le nombre d'états initiaux
			std::string premierMot = line.substr(0, line.find(" "));

			// On sauvegarde la position d'arrêt
			int dernierePos = line.find(" ");

			// On convertit cette nouvelle chaîne de caractères en nombre
			nbEtatsInitiaux = std::stoi(premierMot);

			// On regarde ensuite les numeros qui suivent qui indiquent les numeros des etats initiaux
			std::string numEtatInitial;
			std::cout << ">>	nombre etats Initiaux : " << nbEtatsInitiaux << std::endl;

			short counter = 0;

			// allocation dynamique du nombre d'états initial
			std::string* strTab;
			strTab = new std::string[nbEtats];

			// On sépare à chaque espace les mots
			for (short i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					counter++;
					i++;
				}
				strTab[counter] += line[i];
			}
			listeEtatsInitiaux = new Etat[nbEtatsInitiaux];
			for (int i = 0; i < nbEtatsInitiaux; i++)
			{
				numEtatInitial = std::stoi(strTab[i + 1]);
				std::cout << "		>	Numero initial trouve : " + strTab[i + 1] << std::endl;
				Etat e(std::stoi(strTab[i + 1]));
				listeEtatsInitiaux[i] = e;
			}

			// allocation dynamique puis création des différents états
			listeEtats = new Etat[nbEtats];
			for (int i = 0; i < nbEtats; i++)
			{
				Etat e(i);
				this->listeEtats[i] = e;
			}
			for (int i = 0; i < nbEtats; i++)
			{
				for (int j = 0; j < nbEtatsInitiaux; j++)
				{
					if (listeEtatsInitiaux[j].numero == listeEtats[i].numero)
					{
						listeEtats[i].estEntree = true;
					};
				}
			}
			delete[] strTab;
		}
		else if (i == 3)
		{
			short counter = 0;
			std::string premierMot = line.substr(0, line.find(" "));
			nbEtatsFinaux = std::stoi(premierMot);

			// allocation dynamique du nombre d'états initial
			std::string* strTab2;

			strTab2 = new std::string[30];
			std::cout << ">>	nombre etats Finaux : " << nbEtatsFinaux << std::endl;

			// On sépare à chaque espace les mots
			for (short i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					counter++;
					i++;
				}
				strTab2[counter] += line[i];
			}
			listeEtatsFinaux = new Etat[nbEtatsFinaux];

			for (int i = 0; i < nbEtatsFinaux; i++)
			{
				std::cout << "		>	Numero final trouve : " + strTab2[i + 1] << std::endl;
			}
			for (int i = 0; i < nbEtats; i++)
			{
				for (int j = 0; j < nbEtatsFinaux; j++)
				{
					if (std::stoi(strTab2[j + 1]) == listeEtats[i].numero)
					{
						listeEtats[i].estSortie = true;
						listeEtats[i].estTerminal = true;
						std::cout << "sortie" << std::endl;
						listeEtatsFinaux[j] = listeEtats[i];
					};
				}
			}
			delete[] strTab2;
		}
		else if (i == 4)
		{
			std::string premierMot = line.substr(0, line.find(" "));
			nbTransitions = std::stoi(premierMot);
			std::cout << ">>	nombre transitions : " << nbTransitions << std::endl;
			listeTransitions = new Transition[nbTransitions];
		}
		else if (i >= 5)
		{
			std::string mot = line.substr(0, line.find(" "));
			// On transforme le mot en chaine de caracteres
			std::istringstream iss(line);
			char c; // dummy character for the colon
			int a[3];
			iss >> a[0];
			for (int i = 1; i < 3; i++)
				iss >> c >> a[i];
			if ((i - 5) < nbTransitions)
			{
				// On saisit le premier et dernier chiffre du mot
				int in = a[0];
				int f = a[1];
				Etat init(in);
				Etat final(f);
				Transition t(init, mot.substr(1, 1), final);
				listeTransitions[i - 5] = t;
				if (t.symbole == '*' && !estAsynchrone)
				{
					estAsynchrone = true;
				}
			}
		}
		// on indique ensuite les etats qui sont initiaux et finaux
		i++;
	}
	std::cout << "\nAutomate cree avec succes !" << std::endl;
	auto array = std::make_unique<Transition[]>(nbTransitions);
	for (int j = 0; j < nbEtats; j++)
	{
		// pour chaque etat on genere un nombre de transitions
		std::cout << "Etat : " << listeEtats[j].numero << std::endl;
		int index = 0;
		for (int i = 0; i < nbTransitions; i++)
		{
			listeEtats[j].transitions = new Transition[nbTransitions];
			if (listeEtats[j].numero == listeTransitions[i].etatDepart.numero)
			{
				Transition t(listeEtats[j], listeTransitions[i].symbole, listeTransitions[i].etatFinal);
				listeEtats[j].transitions[index] = t;
				listeEtats[j].nbTransitions++;
				//listeEtats[j].transitions[index].Afficher();
				array[index] = t;
				index++;
			};
		}
		listeEtats[j].transitions = new Transition[listeEtats[j].nbTransitions];
		for (int i = 0; i < listeEtats[j].nbTransitions; i++)
		{
			array[i].Afficher();
			listeEtats[j].transitions[i] = array[i];
		}
		std::cout << listeEtats[j].nbTransitions;
	}


	if (nbEtatsInitiaux == 1)
	{
		estStandard = true;
		for (int i = 0; i < nbTransitions; i++)
		{
			if (listeTransitions[i].etatFinal.numero == listeEtatsInitiaux[0].numero)
			{
				estStandard = false;
				std::cout << "(!)Cette transition revient sur l'Etat initial :"<<std::endl;
				listeTransitions[i].Afficher();
			}
		}
	}
	if (estStandard)
		std::cout << "Cet automate est Standard car il contient :\n 1 seul etat initial\n Aucune transition entrante sur cet etat initial"<<std::endl;
	else
		std::cout << "Cet automate n'est donc pas Standard" <<std::endl;
	AfficherTransitions();
	AfficherSymboles();


	GetTableTransitions(); // sait à partir de cet instant si l'automate est complet
	std::getchar();
}




void Automate::AfficherSymboles()
{	
	char* preListe = new char[ nbTransitions];
	// on rajoute tous les symboles
	int index = 0;
	for (int k = 0; k < nbTransitions; k++)
	{
		if (listeTransitions[k].symbole != '*')
		{
			preListe[index] = listeTransitions[k].symbole;
			index++;
		}
	}
	

	/*size_t arraySize = sizeof(listeSymboles) / sizeof(*listeSymboles);	

	std::sort(listeSymboles, listeSymboles + arraySize);
*/

	listeSymboles = SupprimerSymbolesDupliques(preListe);

	std::cout << " --- Liste des symboles ---" << std::endl;
	for (int l = 0; l < nbSymboles; l++)
	{
		std::cout << l << " : " << listeSymboles[l] << std::endl;
	}
	std::cout << " ------------------------" << std::endl;;

}

char* Automate::SupprimerSymbolesDupliques(char* listeDupliquee)
{
	// On enlève les valeurs excessives et on les stocke dans la liste des Symboles
	char* listeFiltree = new char[nbSymboles];

	char dernierCaractereDifferent = listeDupliquee[0];
	int posSymboleListe = 0;

	for (int k = 0; k < nbTransitions; k++)
	{
		// on ignore la reconnaissance des transitions epsilon
		if (dernierCaractereDifferent != listeDupliquee[k] && dernierCaractereDifferent != '*')
		{
			dernierCaractereDifferent = listeDupliquee[k];
			listeFiltree[posSymboleListe] = dernierCaractereDifferent;

			// on a trouvé un caractère différent et on l'a placé dans le tableau, on incrémente donc le tableau des différents caractères pour passer à la case suivante
			posSymboleListe++;
		}
	}
	return listeFiltree;
}

void Automate::Minimiser() {

}

void Automate::GenComplementaire() {

}

void Automate::LireMot() {

}

void Automate::RecoMot() {

}

void Automate::Standardiser() {

}

void Automate::Afficher() {

}

void Automate::Determiniser() 
{	
	std::string ** tt = GetTableTransitions();
	std::cout << "E ";
	for (int i = 0; i < nbEtatsInitiaux; i++)
	{
		std::cout << listeEtatsInitiaux[i].numero;
	}

}

void Automate::GetEtats() {

}

std::string** Automate::GetTableTransitions() 
{
	// On cree le contenu de la table de transitions
	int nbColonnes = nbSymboles;
	int nbLignes = nbEtats;
	int espacement = 2;

	// Initialisation dynamique, il faudra dé-allouer avec delete[]
	std::string** contenuTableTrans = new std::string*[nbColonnes];
	for (int i = 0; i < nbLignes; i++)
		contenuTableTrans[i] = new std::string[nbLignes];

	int x = 0;
	int y = 0;

	for (int j = 0; j < nbSymboles; j++)
	{
		std::cout << "Symbole : " << listeSymboles[j] << std::endl;
		for (int i = 0; i < nbEtats; i++)
		{
			std::cout << "Etat : " << i << std::endl;
			std::string s = "";
			for (int k = 0; k < listeEtats[i].nbTransitions; k++)
			{
				// Creation de chaque case du tableau
				if (listeSymboles[j] == listeEtats[i].transitions[k].symbole)
				{
					s += std::to_string(listeEtats[i].transitions[k].etatFinal.numero);

				}
			}
			if (s == "")
			{
				s = '-';
				estComplet = false;
			}
			contenuTableTrans[i][j] = s;
		}

		// AffichageTableTransitions

		int decalageDetecte;
		std::cout << "------------------";
		for (int i = 0; i < nbSymboles; i++)
		{
			std::cout << "--------";
		}
		std::cout << "\n";
		for (int x = 0; x < nbLignes + 1; x++)
		{
			// Ligne x
			if (x == 0)
			{
				std::cout << "		      ";
			}
			else if (x != 0)
			{
				if (listeEtats[x - 1].estEntree)
					std::cout << "E ";
				if (listeEtats[x - 1].estSortie)
					std::cout << "S ";
				if (listeEtats[x - 1].estTerminal)
					std::cout << " T ";
				else if (!listeEtats[x - 1].estTerminal)
					std::cout << " NT ";
				std::cout << "		| " << x - 1 << " | ";
			}
			for (int y = 0; y < nbColonnes; y++)
			{
				if (x == 0)
				{
					std::cout << listeSymboles[y];
					Espacer(espacement);
					if (espacement == 0)
						Espacer(1);
				}
				else
				{
					std::cout << contenuTableTrans[x - 1][y];
					decalageDetecte = contenuTableTrans[x - 1][y].length() - 1;
					Espacer(espacement - decalageDetecte);
				}
			}
			// ligne terminée, on retourne à la ligne
			std::cout << "\n";
		}
		std::cout << "------------------";
		for (int i = 0; i < nbSymboles; i++)
		{
			std::cout << "--------";
		}
		std::cout << "\n";
	}
	return contenuTableTrans;
}