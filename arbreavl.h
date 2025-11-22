/* George Fam (FAMG76050000)
 * TP3 -- Arbres AVL
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/tp3/
 */
#if !defined(_ARBREAVL_INF3105_H_)
#define _ARBREAVL_INF3105_H_

#include <cassert>
#include "pile.h"

template <class T>
class ArbreAVL {
public:
    // ----------------- Constructeurs et Destructeur -----------------
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    ~ArbreAVL();
    // ----------------------------------------------------------------

    // ----------------------- Méthodes de base  ----------------------
    // Retourne vrai si l'arbres est vide (racine est nulle).
    bool            vide() const;
    // Retourne vrai si l'élément est dans l'arbre.
    bool            contient(const T&) const;
    // Insère un élément.
    void            inserer(const T&);
    // Vide l'arbre.
    void            vider();
    // Retourne le nbr d'éléments,
    int             taille() const;
    // ----------------------------------------------------------------

    // ----------------- Opérateurs (norm. et Algebre) ----------------
    ArbreAVL<T>&    operator = (const ArbreAVL<T>& autre);
    bool            operator == (const ArbreAVL<T>& autre) const;

    // Ajoute tous les éléments dans autre
    ArbreAVL<T>&    operator += (const ArbreAVL<T>& autre);
    // Retourne l'union
    ArbreAVL<T>     operator +  (const ArbreAVL<T>& autre) const;
    // Retire tous les éléments dans autre
    ArbreAVL<T>&    operator -= (const ArbreAVL<T>& autre);
    // Retourne la différence
    ArbreAVL<T>     operator -  (const ArbreAVL<T>& autre) const;
    // ----------------------------------------------------------------

    // --------------------------- Itérateur --------------------------
    class Iterateur;

    // Retourne un itérateur au plus petit élément
    Iterateur       debut() const;
    // Retourne un itérateur nul (fin)
    Iterateur       fin() const;

    const T&        operator[](const Iterateur&) const;
    T&              operator[](const Iterateur&);
    // ----------------------------------------------------------------

private:
    // ----------------- Structures & Données internes ----------------
    struct Noeud{
        Noeud(const T&);
        T contenu;
        int equilibre;
        Noeud *gauche;
        Noeud *droite;
    };
    Noeud* racine;
    int nbElements;
    // ----------------------------------------------------------------
 
    // --------------------- Insertion & Rotations --------------------
    bool            inserer(Noeud*&, const T&);
    void            rotationDroite(Noeud*&);
    void            rotationGauche(Noeud*&);
    // ----------------------------------------------------------------

    // -------------------------- Utilitaires -------------------------
    void            vider(Noeud*&);
    void            copier(const Noeud*, Noeud*&) const;
    // ----------------------------------------------------------------
public:
    class Iterateur {
    public:
        // Constructeurs d'Itérateur
        Iterateur(const ArbreAVL& a);
        Iterateur(const Iterateur& a);
        Iterateur(const ArbreAVL& a, Noeud* c);

        // Conversions & Comparaison
        operator    bool() const;
        bool        operator!() const;
        bool        operator==(const Iterateur&) const;
        bool        operator!=(const Iterateur&) const;

        // Accès au contenu
        const T&    operator*() const;

        // Déplacement
        Iterateur&  operator++();
        Iterateur   operator++(int);

        // Affectation
        Iterateur&  operator = (const Iterateur&);
    private:
        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;

        friend class ArbreAVL;
    };
};

// --------------------------- Définitions ----------------------------

// ------------------- Constructeurs et Destructeur -------------------
template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c)
 : contenu(c), equilibre(0), gauche(nullptr), droite(nullptr) {}

template <class T>
ArbreAVL<T>::ArbreAVL() : racine(nullptr), nbElements(0) {}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre) : racine(nullptr), 
    nbElements(autre.nbElements)
{
    copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    vider(racine);
}
// --------------------------------------------------------------------

// ------------------------- Méthodes de base  ------------------------
template <class T>
bool ArbreAVL<T>::vide() const
{
    return racine == nullptr;
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
    Noeud* courant = racine;
    while(courant != nullptr){
        if(courant->contenu < element) courant = courant->droite;
        else if(courant->contenu > element) courant = courant->gauche;
        else return true;
    }
    return false;
}

template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
    inserer(racine, element);
}

template <class T>
void ArbreAVL<T>::vider(){
    vider(racine);
    nbElements = 0;
}

template <class T>
int  ArbreAVL<T>::taille() const{
    return nbElements;
}
// --------------------------------------------------------------------

// ------------------- Opérateurs (norm. et Algebre) ------------------
template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
    if(this==&autre) return *this;

    vider();
    nbElements = autre.nbElements;
    copier(autre.racine, racine);
    return *this;
}
 
template <class T>
bool ArbreAVL<T>::operator == (const ArbreAVL<T>& autre) const{
    if(this == &autre) return true;
    if(this->taille() != autre.taille()) return false;

    auto it1 = this->debut();
    auto it2 = autre.debut();

    for(; it1 && it2; ++it1, ++it2) if(*it1 != *it2) return false;

    return !it1 && !it2;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator += (const ArbreAVL<T>& autre){
    for(auto it = autre.debut(); it; ++it) this->inserer(*it);
    return *this;
}

template <class T>
ArbreAVL<T>  ArbreAVL<T>::operator +  (const ArbreAVL<T>& autre) const{
    ArbreAVL r(*this);
    r += autre;
    return r;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator -= (const ArbreAVL<T>& autre){
    ArbreAVL<T> nouv;
    auto i = this->debut();
    auto j = autre.debut();
    
    // Approche Deux-Pointeurs/Itérateurs
    while(i && j){
        const T& a = *i;
        const T& b = *j;
        
        if(a < b){
            nouv.inserer(a);
            ++i;
        }else if(b < a){
            ++j;
        }else{
            ++i;
            ++j;
        }
    }
    // Insère restant de A
    while(i){
        nouv.inserer(*i);
        ++i;
    }
    
    *this = nouv;
    return *this;
}

template <class T>
ArbreAVL<T> ArbreAVL<T>::operator -  (const ArbreAVL<T>& autre) const{
    ArbreAVL r(*this);
    r -= autre;
    return r;
}
// --------------------------------------------------------------------

// ---------------------- Insertions & Rotations ----------------------
template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element)
{
    if(noeud==nullptr)
    {
        noeud = new Noeud(element);
        nbElements++;
        return true;
    }
    if(element < noeud->contenu){
        if(inserer(noeud->gauche, element))
        {
            noeud->equilibre++;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == 1) return true;

            assert(noeud->equilibre==2);
            if(noeud->gauche->equilibre == -1) rotationGauche(noeud->gauche);
            rotationDroite(noeud);
        }
        return false;
    }
    else if(noeud->contenu < element){
        if(inserer(noeud->droite, element))
        {
            noeud->equilibre--;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == -1) return true;

            assert(noeud->equilibre==-2);
            if(noeud->droite->equilibre == 1) rotationDroite(noeud->droite);
            rotationGauche(noeud);
        }
        return false;
    }else{
      // element == noeud->contenu
      noeud->contenu = element;  // Mise à jour
      return false;
    }
}

template <class T>
void ArbreAVL<T>::rotationDroite(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->gauche;
    int  ea = temp->equilibre;
    int  eb = racinesousarbre->equilibre;
    int  neb = -(ea>0 ? ea : 0) - 1 + eb;
    int  nea = ea + (neb < 0 ? neb : 0) - 1;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::rotationGauche(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->droite;
    int ea = temp->equilibre;
    int eb = racinesousarbre->equilibre;
    int neb = -(ea < 0 ? ea : 0) + 1 + eb;
    int nea = ea + (neb > 0 ? neb : 0) + 1;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;
}
// --------------------------------------------------------------------

// ---------------------------- Utilitaires ---------------------------
template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
    if(noeud == nullptr) return;
    vider(noeud->gauche);
    vider(noeud->droite);
    delete noeud;
    noeud = nullptr;
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
    if(source == nullptr) {
        noeud = nullptr;
        return;
    }

    noeud = new Noeud(source->contenu);
    noeud->equilibre = source->equilibre;

    copier(source->gauche, noeud->gauche);
    copier(source->droite, noeud->droite);

}

// ============================= ITÉRATEUR ============================
template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a)
    : arbre_associe(a), courant(nullptr) {}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
    : arbre_associe(a.arbre_associe)
{
    courant = a.courant;
    chemin = a.chemin;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
    Iterateur iter(*this);
    iter.courant = racine;
    while(iter.courant && iter.courant->gauche != nullptr){
        iter.chemin.empiler(iter.courant);
        iter.courant = iter.courant->gauche;
    }
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{
    return Iterateur(*this);
}

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur)
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}


// Pré-incrément
template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++()
{
    assert(courant);
    if(courant->droite){
        Noeud* suivant = courant->droite;
        while (suivant){
            chemin.empiler(suivant);
            suivant = suivant->gauche;
        }
    }

    if (!chemin.vide()) courant = chemin.depiler();
    else courant = nullptr;
    
    return *this;
}

// Post-incrément
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int)
{
    Iterateur copie(*this);
    operator++();
    return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const
{
    return courant!=nullptr;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const{
    return courant==nullptr;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant==o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant!=o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const
{
    assert(courant!=nullptr);
    return courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre){
    assert(&arbre_associe==&autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}
// ====================================================================

#endif // _ARBREAVL_INF3105_H_
