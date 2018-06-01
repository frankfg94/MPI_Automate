/**
 * Project Untitled
 */


#include "Transition.h"
#include <iostream>
/**
 * Transition implementation
 */

Transition::Transition(Etat dep, char symb, Etat fin)
{
	etatDepart = dep;
	symbole = symb;
	etatFinal = fin;
}

Transition::Transition(Etat dep, std::string symb, Etat fin)
{
	etatDepart = dep;
	symbole = symb[0];
	etatFinal = fin;
}

Transition::Transition()
{

}

void Transition::Afficher()
{
	std::cout << "		> 		Etat initial:	" << etatDepart.numero << std::endl;
	std::cout << "		> 		Symbole:		" << symbole << std::endl;
	std::cout << "		> 		Etat final:		" << etatFinal.numero << std::endl << std::endl;
}
