#pragma once;
#include <iostream>

typedef int TElem;

typedef std::pair<TElem, int> TComparabil;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Nod;

typedef Nod* PNod;

class Nod{
private:
    TComparabil ec;

    PNod st, dr;

public:
    friend class Colectie;

    Nod(TElem e, PNod st, PNod dr);

    TElem element();

    int frecventa();

    PNod stanga();

    PNod dreapta();
};

class Colectie {

	friend class IteratorColectie;

private:
	PNod rad;

    PNod adauga_rec(PNod p, TElem e);

    void distrug_rec(PNod);

    TComparabil find_rec(PNod p, TElem e) const;

    int dim_rec(PNod p) const;

    PNod sterge_rec(PNod p, TElem e);

    PNod minim(PNod p);

public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;


		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// destructorul colectiei
		~Colectie();


};

