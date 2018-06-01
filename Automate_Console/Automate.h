/**
 * Project Untitled
 */

#include <iostream>
#ifndef _AUTOMATE_H
#define _AUTOMATE_H
#include "Etat.h"
#include "Transition.h"

class Automate {

private: 
	char* listeSymboles;
public: 
    bool estAsynchrone;
    bool estDeterministe;
    bool estComplet;
    int nbEtats;
    int nbSymboles;
	int nbEtatsInitiaux;
	int nbEtatsFinaux;
	Etat* listeEtats;
    Transition* listeTransitions;
    int nbTransitions;
    
	Automate(std::string texte);

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