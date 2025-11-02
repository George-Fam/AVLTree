/* Le programme testtp3E.cpp (avec E majuscule) est un exemple de tests pour le critère E 
   (efficacité des fonctionnalités spécifiques au TP3).
   Pour tester :
       g++ -O testtp3E.cpp -o testE
       time ./testE
*/
#include <iostream>
#include <chrono>
#include "arbreavl.h"

// testE1 fait des insertions et des appels à inserer, contient et taille.
bool testE1(){
    std::cout << "testE1 ..." << std::endl;
    auto debut = std::chrono::steady_clock::now();
    ArbreAVL<int> a;
    int maxn=5000;
    for(int n=0;n<maxn;n++){
        for(int i=0;i<n;i++)
            a.inserer(3*i);
        for(int i=0;i<n;i++)
            a.inserer(3*i+1);

        for(int i=0;i<n;i++){
            if(a.taille() != 2*n){
                std::cout << "Erreur testE1 : a.taille() != " << (2*n) << std::endl;
            }
            if(!a.contient(3*i+1)){
                std::cout << "Erreur testE1 : a devrait contenir " << (3*i+1) << std::endl;
                return false;
            }
            if(a.contient(3*i+2)){
                std::cout << "Erreur testE1 : a ne devrait pas contenir " << (3*i+2) << std::endl;
                return false;
            }
        }
        if(a.contient(3*n)){
            std::cout << "Erreur testE1 : a ne devrait pas encore contenir " << (3*n) << std::endl;
            return false;
        }
    }
    auto fin = std::chrono::steady_clock::now();
    std::chrono::duration<double> duree = fin - debut;
    std::cout << "\ttestE1 réussi en " << duree.count() << " secondes (temps réel, pas  temps CPU)." << std::endl;
    return true;
}

// Test faisant beaucoup d'appels à l'opérateur +=
bool testE3(){
    std::cout << "testE3 ..." << std::endl;
    auto debut = std::chrono::steady_clock::now();
    ArbreAVL<int> pairs, impairs, tout;
    int N=100000;
    for(int i=0;i<N;i++){
        pairs.inserer(2*i);
        tout.inserer(2*i);
        impairs.inserer(2*i+1);
        tout.inserer(2*i+1);
    }
    // Répétez plusieurs fois
    for(int k=0;k<200;k++){
        ArbreAVL<int> a(pairs);
        ArbreAVL<int> b;
        b  = impairs;
        b += a;
        // Ne présumez pas que l'opérateur != est disponible, car il n'était pas demandé dans l'énoncé (section 2.1).
        // Combinez ! et l'operateur == pour vérifier.
        //if(b!=tout)
        if(!(b==tout)){
            std::cout << "Erreur testE3!" << std::endl;
            return false;
        }
        ArbreAVL<int> c = pairs + impairs;           
    }
    auto fin = std::chrono::steady_clock::now();
    std::chrono::duration<double> duree = fin - debut;
    std::cout << "\ttestE3 réussi en " << duree.count() << " secondes!" << std::endl;
    return true;
}

int main(){
    int nberreurs = 0; 
    if(!testE1())
       nberreurs++;
    if(!testE3())
       nberreurs++;
    
    // Important: retourner 0 si aucune erreur. Sinon >0. Il est suggéré de retourner le nombre de types d'erreurs détectées.
    return nberreurs;
}


