/*
 * Project Untitled
 */


#include "Automate.h"
#include <iostream>
#include <string>
#include <sstream>
#include <array>

/**
 * Automate implementation
 */



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
			std::cout << "ok2" << std::endl;
			for (int i = 0; i < nbEtatsInitiaux; i++)
			{
				numEtatInitial = std::stoi(strTab[i+1]);
				std::cout << "		>	Numero initial trouve : " + strTab[i + 1] << std::endl;
			}
			delete[] strTab;

	


			// allocation dynamique puis création des différents états
			listeEtats = new Etat[nbEtats];
			for (int i = 0; i < nbEtats; i++)
			{
				Etat e(i);
				this->listeEtats[i]= e;
			}
			
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
			for (int i = 0; i < nbEtatsFinaux; i++)
			{
				nbEtatsFinaux = std::stoi(strTab2[i + 1]);
				std::cout << "		>	Numero final trouve : " + strTab2[i + 1] << std::endl;
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
				Transition t(init, mot.substr(1, 1),final);
				//std::cout << std::endl << ">>	Transition " << i - 5 << std::endl << std::flush;
				//t.Afficher();
				listeTransitions[i - 5] = t;
				
			}
		}
		
		// on indique ensuite les etats qui sont initiaux et finaux
		i++;
	}
	std::cout << "\nAutomate cree avec succes !" << std::endl;

	for (int j = 0; j < nbEtats; j++)
	{
		// pour chaque etat on genere un nombre de transitions
		std::cout << "Etat : " << listeEtats[j].numero << std::endl;
		for (int i = 0; i < nbTransitions; i++)
		{
			this->listeEtats[j].transitions = new Transition[nbTransitions];
			// on parcoure toutes les transitions a disposition
			// on regarde si une des transitions commence par l'état
			// ici si le numero de l'état est égal au numero de la transition de de(part

			if (listeEtats[j].numero == listeTransitions[i].etatDepart.numero)
			{
				std::cout << "Etat i   : " << listeEtats[j].numero << std::endl;
				std::cout << "Symbole  : " << listeTransitions[i].symbole << std::endl;
				std::cout << "Etat f   : " << listeTransitions[i].etatFinal.numero << std::endl;
				std::cout << "Correspondance trouvee entre etat " << listeEtats[j].numero << " et " << listeTransitions[i].etatDepart.numero << std::endl;
				listeEtats[j].transitions[i].etatDepart = listeEtats[j].numero;
				listeEtats[j].transitions[i].etatFinal = listeTransitions[i].etatFinal.numero;
				listeEtats[j].transitions[i] = listeTransitions[i];

				// allocation dynamique
			};
		}
	}
	AfficherSymboles();





	// On cree le contenu de la table de transitions
	int nbColonnes = nbSymboles;
	int nbLignes = nbEtats;
	int espacement = 4;

	// Initialisation dynamique, il faudra dé-allouer avec delete[]
	std::string** contenuTableTrans = new std::string*[nbLignes];
	for (int i = 0; i < nbColonnes; i++)
	{
		contenuTableTrans[i] = new std::string[nbColonnes];
	}


	int x = 0;
	int y = 0;
	for (int i = 0; i < nbEtats; i++)
	{
		Transition* transitionsEtat = new Transition[nbTransitions];
		transitionsEtat =listeEtats[i].transitions;

		for (int j = 0; j < nbSymboles; j++)
		{
			std::string caseTableTransition = "";
			if (transitionsEtat[j].symbole == listeSymboles[nbSymboles])
			{
				caseTableTransition += transitionsEtat[j].etatFinal.numero;
			}
			std::cout << caseTableTransition << std::endl;
			// tous les etats de sortie sont ajoutés dans le string
			//contenuTableTrans[j][i] = caseTableTransition;
		}
		
	}

	//Assigner la table de transitions 


	// AffichageTableTransitions
	for (int x = 0; x < nbLignes; x++)
	{
		// Ligne x
		std::cout << x <<" | ";
		for (int y = 0; y < nbColonnes; y++)
		{

		    if (x == 0)
			{
				std::cout << listeSymboles[y];
				for (int e = 0; e < espacement; e++)
				{
					std::cout << " ";
				}
			}
			else
			{
				// Colonne y
				//std::cout<< contenuTableTrans[x][y] << " " ;
				std::cout << '*';
				for (int e = 0; e < espacement; e++)
				{
					std::cout <<" ";
				}
			}
		}

		// ligne terminée, on retourne à la ligne
		std::cout << "\n";
	}
}


void Automate::AfficherSymboles()
{	
	char* preListe = new char[ nbTransitions];
	// on rajoute tous les symboles
	for (int k = 0; k < nbTransitions; k++)
	{
		preListe[k] = listeTransitions[k].symbole;
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

void Automate::Determiniser() {

}

void Automate::GetEtats() {

}

void Automate::GetTableTransitions() {

}