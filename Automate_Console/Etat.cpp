/**
 * Project Untitled
 */


#include "Etat.h"
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


