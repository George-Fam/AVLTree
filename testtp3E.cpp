#include <iostream>
#include "arbreavl.h"

bool testE1(){
    bool erreur=false;
    ArbreAVL<int> a;
    int maxn=10000;
    for(int n=0;n<maxn;n++){
        for(int i=0;i<n;i++)
           a.inserer(3*i);
        for(int i=0;i<n;i++)
           a.inserer(3*i+1);
        
        for(int i=0;i<n;i++){
           if(!a.contient(3*i+1))
              erreur=true;
           if(!a.contient(3*i+2))
              erreur=true;
           if(a.contient(3*i+3))
              erreur=true;
        }
    }
    return !erreur;
}

int main(){
    int nberreurs = 0; 
    if(!testE1())
       nberreurs++;
    
    // Important: retourner 0 si aucune erreur. Sinon >0. Il est suggéré de retourner le nombre de types d'erreurs détectées.
    return nberreurs;
}


