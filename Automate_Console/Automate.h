/**
 * Project Untitled
 */

#include <iostream>
#ifndef _AUTOMATE_H
#define _AUTOMATE_H
#include "Transition.h"

class Etat;
class Automate {

private: 
	

public: 
	char* listeSymboles;
	bool estAsynchrone;
	bool estDeterministe;
	bool estComplet;
	int nbEtats;
	int nbSymboles;
	int nbEtatsInitiaux;
	int nbEtatsFinaux;
	Etat* listeEtats;
	Etat* listeEtatsInitiaux;
	Etat* listeEtatsFinaux;
	Transition* listeTransitions;
	int nbTransitions;
	void AfficherTransitions();

	Automate(std::string texte);

	void StockerTransitions();

	void AfficherSymboles();

	char* SupprimerSymbolesDupliques(char* listeDupliquee);

	char* GetSymboles();

    void Minimiser();
    
    void GenComplementaire();
    
    void LireMot();
    
    void RecoMot();
    
    void Standardiser();
    
    void Afficher();
    
    void Determiniser();
    
    void GetEtats();
    
    void GetTableTransitions();
private: 
   std::string Identifiant;
};

#endif //_AUTOMATE_H