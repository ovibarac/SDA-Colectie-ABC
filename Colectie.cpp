#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

const TComparabil NIL(-1, -1);

bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

Nod::Nod(TElem e, PNod st, PNod dr) {
    this->ec = TComparabil(e, 1);
    this->st = st;
    this->dr = dr;
}

TElem Nod::element() {
    return ec.first;
}

int Nod::frecventa() {
    return ec.second;
}

PNod Nod::stanga() {
    return st;
}

PNod Nod::dreapta() {
    return dr;
}

Colectie::Colectie() {
	rad = nullptr;
}

PNod Colectie::adauga_rec(PNod p, TElem e) {
    if(p == nullptr){
        p = new Nod(e, nullptr, nullptr);
    }else{
        if(e < p->element()){
            p->st = adauga_rec(p->st, e);
        }else if(e > p->element()){
            p->dr = adauga_rec(p->dr, e);
        }else{
            //daca este egal se creste frecventa
            p->ec.second++;
        }
    }
    return p;
}

void Colectie::adauga(TElem e) {
	rad = adauga_rec(rad, e);
}

void Colectie::distrug_rec(PNod p) {
    if(p!= nullptr){
        distrug_rec(p->stanga());
        distrug_rec(p->dreapta());
        delete p;
    }
}

PNod Colectie::minim(PNod p) {
    //O(h)
    while(p->stanga() != nullptr){
        p = p->stanga();
    }
    return p;
}

PNod Colectie::sterge_rec(PNod p, TElem e) {
    if(p == nullptr){
        return nullptr;
    }else{
        if(e < p->element()){
            //se sterge din subarborele stang
            p->st = sterge_rec(p->st, e);
            return p;
        }else if(e > p->element()){
            //se sterge din subarborele drept
            p->dr = sterge_rec(p->dr, e);
            return p;
        }else{
            if(p->frecventa() > 1){
                //daca sunt mai multe scade doar frecventa
                p->ec.second--;
            }else{
                //sterge nodul
                PNod temp;
                PNod repl;
                if(p->stanga() != nullptr && p->dreapta() != nullptr){
                    //nodul are si subarbore stang si drept
                    temp = minim(p->dreapta());
                    p->ec.first = temp->ec.first;
                    //sterge nodul cu cheia minima din subarborele drept
                    p->dr = sterge_rec(p->dr, p->element());
                    return p;
                }else{
                    temp = p;
                    if(p->stanga() == nullptr){
                        //nu exista subarbore stang
                        repl = p->dreapta();
                    }else{
                        //nu exista subarbore drept
                        repl = p->stanga();
                    }
                    delete temp;

                    return repl;
                }
            }
        }
    }
}

bool Colectie::sterge(TElem e) {
    bool rez = cauta(e);
    rad = sterge_rec(rad, e);
    return rez;
}

TComparabil Colectie::find_rec(PNod p, TElem e) const{
    if(p == nullptr){
        return NIL;
    }else{
        if(e < p->element()){
            return find_rec(p->st, e);
        }else if(e > p->element()){
            return find_rec(p->dr, e);
        }else{
            //daca este egal returneaza elementul
            return p->ec;
        }
    }
}

bool Colectie::cauta(TElem elem) const {
    TComparabil comp = find_rec(rad, elem);
    if(comp != NIL){
        return true;
    }
	return false;
}


int Colectie::nrAparitii(TElem elem) const {
	TComparabil comp = find_rec(rad, elem);
    if(comp != NIL){
        return comp.second;
    }
	return 0;
}

int Colectie::dim_rec(PNod p) const {
    if(p == nullptr){
        return 0;
    }else{
        return p->frecventa() + dim_rec(p->st) + dim_rec(p->dr);
    }
}

int Colectie::dim() const {
    return dim_rec(rad);
}


bool Colectie::vida() const {
	return rad == nullptr;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
    distrug_rec(rad);
}
