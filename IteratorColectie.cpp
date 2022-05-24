#include "IteratorColectie.h"
#include "Colectie.h"
#include <stack>


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    //iteratorul parcurgere in inordine
    curent = col.rad;

}

TElem IteratorColectie::element(){
	while(curent != nullptr){
        //adauga in stiva ramura stanga
        s.emplace(curent);
        curent = curent->stanga();
    }
    curent = s.top();
    s.pop();
    return curent->element();
}

bool IteratorColectie::valid() const {
	return curent != nullptr || !s.empty();
}

void IteratorColectie::urmator() {
	curent = curent->dreapta();
}

void IteratorColectie::prim() {
	curent = col.rad;
}
