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
		 std::cout << "Etat cree" << std::endl;
	 };

	 void Etat::Afficher()
	 {
		 std::cout << "num etat{ " << numero << "}" << std::endl;
	 }


