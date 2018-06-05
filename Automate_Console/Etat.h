/**
 * Project Untitled
 */


#ifndef _ETAT_H
#define _ETAT_H
#include <vector>
class Automate;
class Transition;
class Etat
{

public: 
    int numero;
	int nbTransitions;
    bool estSortie;
    bool estEntree;
	bool estTerminal; 
	bool estPoubelle;
	std::vector<Transition> transitions;
	Etat(int i);
	Etat();
	void Afficher();
	void AfficherTransitions();
};

#endif //_ETAT_H