
#include "Automate.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <cstdio>


int ConvertStringToInt(std::string string)
{
	int i;

	//approach one
	std::istringstream(string) >> i; //i is 10 after this

									 //approach two
	scanf(string.c_str(), "%d", &i); //i is 10 after this

	return i;
}


template<typename T>
std::string ToString(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}


void Automate::AfficherTransitions()
{
	std::cout << "Fonction AfficherTransitions()" << std::endl;
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

	// On demande � parcourir chaque ligne d'indice i du fichier texte
	while (std::getline(f, line))
	{
		if (i == 0)
		{
			// stoi signifie string to int, c'est ainsi une conversion
			nbSymboles = ConvertStringToInt(line);
			std::cout << ">>	nombre symboles : " << nbSymboles << std::endl;
		}
		else if (i == 1)
		{
			// M�me principe
			nbEtats = ConvertStringToInt(line);
			std::cout << ">>	nombre etats : " << nbEtats << std::endl;
		}
		else if (i == 2)
		{
			// Il faut d�tecter le premier nombre qui constitue le nombre d'�tats initiaux
			std::string premierMot = line.substr(0, line.find(" "));

			// On sauvegarde la position d'arr�t
			int dernierePos = line.find(" ");

			// On convertit cette nouvelle cha�ne de caract�res en nombre
			nbEtatsInitiaux = ConvertStringToInt(premierMot);

			// On regarde ensuite les numeros qui suivent qui indiquent les numeros des etats initiaux
			std::string numEtatInitial;
			std::cout << ">>	nombre etats Initiaux : " << nbEtatsInitiaux << std::endl;

			short counter = 0;

			// allocation dynamique du nombre d'�tats initial
			std::string* strTab;
			strTab = new std::string[nbEtats];

			// On s�pare � chaque espace les mots
			for (short i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					counter++;
					i++;
				}
				strTab[counter] += line[i];
			}
			for (int i = 0; i < nbEtatsInitiaux; i++)
			{
				numEtatInitial = ConvertStringToInt(strTab[i + 1]);
				std::cout << "		>	Numero initial trouve : " + strTab[i + 1] << std::endl;
				Etat e(ConvertStringToInt(strTab[i + 1]));
				listeEtatsInitiaux.push_back(e);
			}

			// allocation dynamique puis cr�ation des diff�rents �tats
			for (int i = 0; i < nbEtats; i++)
			{
				Etat e(i);
				listeEtats.push_back(e);
			}
			for (int i = 0; i < nbEtats; i++)
			{
				for (int j = 0; j < nbEtatsInitiaux; j++)
				{
					if (listeEtatsInitiaux[j].numero == listeEtats[i].numero)
					{
						listeEtats[i].estEntree = true;
					}
					else
					{
						listeEtats[i].estEntree = false;
					};
				}
			}
			delete[] strTab;
		}
		else if (i == 3)
		{
			short counter = 0;
			std::string premierMot = line.substr(0, line.find(" "));
			nbEtatsFinaux = ConvertStringToInt(premierMot);

			// allocation dynamique du nombre d'�tats initial
			std::string* strTab2;

			strTab2 = new std::string[30];
			std::cout << ">>	nombre etats Finaux : " << nbEtatsFinaux << std::endl;

			// On s�pare � chaque espace les mots
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
				std::cout << "		>	Numero final trouve : " + strTab2[i + 1] << std::endl;
			}
			for (int i = 0; i < nbEtats; i++)
			{
				for (int j = 0; j < nbEtatsFinaux; j++)
				{
					if (ConvertStringToInt(strTab2[j + 1]) == listeEtats[i].numero)
					{
						listeEtats[i].estSortie = true;
						listeEtats[i].estTerminal = true;
					}
					else
					{
						listeEtats[i].estSortie = false;
						listeEtats[i].estTerminal = false;
					}
					listeEtatsFinaux.push_back(listeEtats[i]);
				}
			}
			delete[] strTab2;
		}
		else if (i == 4)
		{
			std::string premierMot = line.substr(0, line.find(" "));
			nbTransitions = ConvertStringToInt(premierMot);
			std::cout << ">>	nombre transitions : " << nbTransitions << std::endl;
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
				listeTransitions.push_back(t);
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

	AfficherTransitions();

	for (int j = 0; j < nbEtats; j++)
	{
		// pour chaque etat on genere un nombre de transitions
		std::cout << "Etat : " << listeEtats[j].numero << std::endl;
		int index = 0;
		for (int i = 0; i < nbTransitions; i++)
		{
			//std::cout << "iter transition" << i << std::endl;
			if (listeEtats[j].numero == listeTransitions[i].etatDepart.numero)
			{
				Transition t(listeEtats[j], listeTransitions[i].symbole, listeTransitions[i].etatFinal);
				listeEtats[j].nbTransitions++;
				//listeEtats[j].transitions[index].Afficher();
				listeEtats[j].transitions.push_back(t);
				t.Afficher();
			};
		}
		/*		listeEtats[j].transitions = new Transition[listeEtats[j].nbTransitions];
		for (int i = 0; i < listeEtats[j].nbTransitions; i++)
		{
		array[i].Afficher();
		listeEtats[j].transitions[i] = array[i];
		}
		std::cout << listeEtats[j].nbTransitions;*<  */
	}


	if (nbEtatsInitiaux == 1)
	{
		estStandard = true;
		for (int i = 0; i < nbTransitions; i++)
		{
			if (listeTransitions[i].etatFinal.numero == listeEtatsInitiaux[0].numero)
			{
				estStandard = false;
				std::cout << "(!)Cette transition revient sur l'Etat initial :" << std::endl;
				listeTransitions[i].Afficher();
			}
		}
	}
	if (estStandard)
		std::cout << ">> Cet automate est Standard car il contient :\n 1 seul etat initial\n Aucune transition entrante sur cet etat initial" << std::endl;
	else
		std::cout << ">> Cet automate n'est donc pas Standard" << std::endl;
	//AfficherTransitions();
	AfficherSymboles();

	if (estAsynchrone)
	{
		std::cout << " >> Cet automate est asynchrone car il possede au moins une transition epsilon" << std::endl;
	}
	else
	{
		std::cout << " >> Cet automate est n'est pas asynchrone car il ne possede pas de transition epsilon" << std::endl;
	}
	GetTableTransitions(false); // sait � partir de cet instant si l'automate est complet
	Determiniser();

	GetTableTransitions(true);

	std::getchar();
}




void Automate::AfficherSymboles()
{
	char* preListe = new char[nbTransitions];
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
	std::cout << " ------------------------" << std::endl;
}

char* Automate::SupprimerSymbolesDupliques(char* listeDupliquee)
{
	// On enl�ve les valeurs excessives et on les stocke dans la liste des Symboles
	char* listeFiltree = new char[nbSymboles];

	char dernierCaractereDifferent = listeDupliquee[0];
	listeFiltree[0] = dernierCaractereDifferent;
	int posSymboleListe = 1;

	for (int k = 1; k < nbTransitions; k++)
	{
		// on ignore la reconnaissance des transitions epsilon
		if (dernierCaractereDifferent != listeDupliquee[k] && dernierCaractereDifferent != '*')
		{
			dernierCaractereDifferent = listeDupliquee[k];
			listeFiltree[posSymboleListe] = dernierCaractereDifferent;

			// on a trouv� un caract�re diff�rent et on l'a plac� dans le tableau, on incr�mente donc le tableau des diff�rents caract�res pour passer � la case suivante
			posSymboleListe++;
		}

	}
	return listeFiltree;
}

Etat Automate::GetEtat(int numero)
{
	for (int i = 0; i < nbEtats; i++)
	{
		if (i == numero)
		{
			return listeEtats[i];
		}
	}
}

Etat Automate::GetEtat(std::string numero)
{
	for (int i = 0; i < nbEtats; i++)
	{
		if (i == ConvertStringToInt(numero))
		{
			return listeEtats[i];
		}
	}
}

Transition * Automate::GetTransitionsPourSymbole(char symbole)
{
	std::vector<Transition> trans;
	for (int i = 0; i < nbTransitions; i++)
	{
		if (listeTransitions[i].symbole == symbole)
		{
			trans.push_back(listeTransitions[i]);
			//trans.back().Afficher();
		};
	}
	Transition* tab = &trans[0];
	return tab;
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

void Automate::Completer()
{
	for (int i = 0; i < nbTransitions; i++)
	{
		if (listeTransitions[i].symbole == '-')
		{
			listeTransitions[i].symbole = 'p';
		}
	}
}

void Automate::Afficher() {

}

void Automate::Determiniser()
{
	std::cout << "ENTREE";
	GetTransitionsPourSymbole('a');
	std::string premierEtat;
	std::string** tt = GetTableTransitions(false);
	std::cout << "	";

	for (int i = 0; i < nbSymboles; i++)
	{
		std::cout << listeSymboles[i] << "	";
	}
	std::cout << "\nE ";
	Etat* etatsL1;
	etatsL1 = new Etat[nbEtatsInitiaux];
	for (int i = 0; i < nbEtatsInitiaux; i++)
	{
		std::cout << listeEtatsInitiaux[i].numero;
		etatsL1[i] = listeEtatsInitiaux[i];
	}

	// Initialisation dynamique, il faudra d�-allouer avec delete[]
	std::string** tDet = new std::string*[nbEtats];
	for (int i = 0; i < nbSymboles; i++)
		tDet[i] = new std::string[nbSymboles];
	//pour la premiere ligne
	std::cout << "  ";
	for (int i = 0; i < nbSymboles; i++)
	{
		std::string s = "";
		for (int j = 0; j < nbEtats; j++)
		{
			if (tt[j][i] != "-" &&  GetEtat(listeEtats[j].numero).estEntree)
				s += tt[j][i];
		}
		tDet[i][0] += s;

		std::cout << s;
		std::cout << "   ";
	}


	// pour le reste des lignes
	for (int i = 0; i < nbSymboles; i++)
	{

	}

}

void Automate::GetEtats() {

}

std::string** Automate::GetTableTransitions(bool complet = false)
{
	// On cree le contenu de la table de transitions
	int nbColonnes = nbSymboles;
	int nbLignes = nbEtats;
	int espacement = 2;

	// Initialisation dynamique, il faudra d�-allouer avec delete[]
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
					s += ToString(listeEtats[i].transitions[k].etatFinal.numero);
				}
			}
			if (s == "")
			{
				if (!complet)
					s = '-';
				else
				{
					s = 'p';
				}
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
			// ligne termin�e, on retourne � la ligne
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
