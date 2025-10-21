#include <iostream>
#include "arbreavl.h"

// Cette fonction vérifie la présence des fonctionnalités demandées au TP3 (de base + nouvelles).
// dans la classe générique ArbreAVL dans arbreavl.h.
// Si ce test compile, c'est bon signe. Mais, ce test n'est pas exhaustif.
// Le bon fonctionnement n'est pas vérifié.
// L'efficacité temporelle n'est pas mesurée.
void test00_compilation(){
   ArbreAVL<int> a1;
   ArbreAVL<int> a2(a1);
   const ArbreAVL<int>& a3 = a1;
   bool b = a3.vide();
   b = a3.contient(5);
   a1.inserer(1);
   a2.vider();
   
   // Nouvelles fonctionnalitées TP3
   int t = a1.taille();
   b = (a3==a2);
   
   a1+=a3;
   a2 = a3+a3;
   
   a1-=a3;
   a2 = a3-a3;
}


bool test01(){
   ArbreAVL<int> a;
   a.inserer(1);
   int t = a.taille();
   bool r = t==1;
   if(!r)
       std::cout << "Mauvaise taille !" << std::endl;
   return r;
}

bool test02(){
   ArbreAVL<int> a;
   a.inserer(10);
   a.inserer(20);
   if(!a.contient(10)){
       std::cout << "10 doit être dans a !" << std::endl;
       return false;
   }
   if(a.contient(15)){
       std::cout << "15 ne doit pas être dans a !" << std::endl;
       return false;
   }
   return true;
}

int main(){
    test00_compilation();
    int nb_types_erreur=0;
    if(!test01())
        nb_types_erreur++;
    if(!test02())
        nb_types_erreur++;
    
    // Important: retourner 0 si aucune erreur. Sinon >0. Il est suggéré de retourner le nombre de types d'erreurs détectées.
    return nb_types_erreur;
}


