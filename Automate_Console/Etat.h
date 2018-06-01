/**
 * Project Untitled
 */


#ifndef _ETAT_H
#define _ETAT_H

class Transition;

class Etat
{

public: 
    int numero;
    bool estSortie;
    bool estEntree;
	Transition* transitions;
	Etat(int i);
	Etat();
	void Afficher();
};

#endif //_ETAT_H