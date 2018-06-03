/**
 * Project Untitled
 */


#include "Etat.h"
#include "Automate.h"
#include <iostream>

/**
 * Etat implementation
 */

	 Etat::Etat(int i)
 {
		 numero = i;
	 };

	 Etat::Etat()
	 {
	 };

	 void Etat::Afficher()
	 {
		 std::cout << "num etat{ " << numero << "}" << std::endl;
	 }

	 void Etat::AfficherTransitions()
	 {
		 std::cout << "Fonction AfficherTransitions() pour l'Etat : " << numero << std::endl;
		 for (int i = 0; i < nbTransitions ;i++)
		 {
			 transitions[i].Afficher();
		 };
	 }



