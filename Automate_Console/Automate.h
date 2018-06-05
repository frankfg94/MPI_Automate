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
	bool estAsynchrone; // valide dès qu'une asterisque est détectée dans une transition
	bool estDeterministe;
	bool estComplet;
	bool estStandard;
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

	void AfficherSymboles();

	char* SupprimerSymbolesDupliques(char* listeDupliquee);

	Etat GetEtat(int numero);
	Etat GetEtat(std::string numero);

	Transition* GetTransitionsPourSymbole(char symbole);

    void Minimiser();
    
    void GenComplementaire();
    
    void LireMot();
    
    void RecoMot();
    
    void Standardiser();
    
	void Completer();

    void Afficher();
    
    void Determiniser();
    
    void GetEtats();
    
    std::string** GetTableTransitions(bool complet);
private: 
   std::string Identifiant;
};

#endif //_AUTOMATE_H