/**
 * Project Untitled
 */
#include <string>
#include "Etat.h"
#ifndef _TRANSITION_H
#define _TRANSITION_H

class Transition 
{
public: 
    Etat etatDepart;
    Etat etatFinal;
    char symbole;
	Transition(Etat dep, char symb, Etat fin);
	Transition(Etat dep, std::string symb, Etat fin);
	Transition();

	void Afficher();
};

#endif //_TRANSITION_H