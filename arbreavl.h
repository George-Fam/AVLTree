/* Squelette minimal pour classe générique ArbreAVL<T> du TP3.
 * TP3 -- Arbres AVL
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/tp3/
 *
 * Recommandation:
 *  - Réutilisez votre solution des Lab6 et Lab7.
 *  - Ajoutez-y les fonctions demandées ci-dessous.
 *
 */
#if !defined(_ARBREAVL_INF3105_H_)
#define _ARBREAVL_INF3105_H_

template <class T>
class ArbreAVL {
  public:
// Constructeurs
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    ~ArbreAVL();

    // Lab6 / Tâche 2 - Fonctions de base
    bool vide() const;
    bool contient(const T&) const;
    void inserer(const T&);
    void vider();

    // Nouvelles fonctionnalités du TP3:
    int             taille() const; // retourne le nombre d'éléments
    
    ArbreAVL<T>&    operator = (const ArbreAVL<T>& autre);

    bool            operator == (const ArbreAVL<T>& autre) const;
    
    ArbreAVL<T>&    operator += (const ArbreAVL<T>& autre); // ajoute tous les éléments dans autre
    ArbreAVL<T>     operator +  (const ArbreAVL<T>& autre) const; // retourne l'union

    ArbreAVL<T>&    operator -= (const ArbreAVL<T>& autre); // retire tous les éléments dans autre
    ArbreAVL<T>     operator -  (const ArbreAVL<T>& autre) const; // retourne la différence
    

  private:
    // Copiez ici votre code "partie privée" du lab 6.
};


//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::ArbreAVL() 
{
    // À compléter.
}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre)
{
    // À compléter.
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    // À décommenter:
    //vider(racine);
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
    // À compléter.
    return false;
}

template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
}

template <class T>
bool ArbreAVL<T>::vide() const
{
    // À compléter : doit retourner vrai si et seulement si l'arbre est vide.
    return true;
}

template <class T>
void ArbreAVL<T>::vider(){
    // À compléter.
}

template <class T>
int  ArbreAVL<T>::taille() const{
    // À compléter.
    return 0;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
    // À compléter.
    return *this;
}

   
template <class T>
bool ArbreAVL<T>::operator == (const ArbreAVL<T>& autre) const{
    // À compléter.
    return false;
}
    
template <class T> // ajoute tous les éléments dans autre
ArbreAVL<T>& ArbreAVL<T>::operator += (const ArbreAVL<T>& autre){
    // À compléter.
    return *this;
}

template <class T>  // retourne l'union
ArbreAVL<T>  ArbreAVL<T>::operator +  (const ArbreAVL<T>& autre) const{
    // À compléter.
    return *this;
}
template <class T> // retire tous les éléments dans autre
ArbreAVL<T>& ArbreAVL<T>::operator -= (const ArbreAVL<T>& autre){
    // À compléter.
    return *this;
}

template <class T> // retourne la différence
ArbreAVL<T> ArbreAVL<T>::operator -  (const ArbreAVL<T>& autre) const{
    // À compléter.
    return *this;
}


#endif // _ARBREAVL_INF3105_H_
