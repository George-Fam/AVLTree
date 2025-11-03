#include <iostream>
#include <chrono>
#include <ostream>
#include "arbreavl.h"

void test00_compilation(){
   ArbreAVL<int> a1;
   ArbreAVL<int> a2(a1);
   const ArbreAVL<int>& a3 = a1;
   bool b = a3.vide();
   b = a3.contient(5);
   a1.inserer(1);
   a2.vider();
   
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
   bool r = a.taille()==1;
   a.inserer(1);
   r &= a.taille()==1;
   if(!r) std::cout << "Mauvaise taille !"<<std::endl;
   return r;
}
bool test02(){
   ArbreAVL<int> a;
   a.inserer(10);
   a.inserer(20);
   if(!a.contient(10)){
       std::cout<<"10 doit être dans a !"<<std::endl;
       return false;
   }
   if(a.contient(15)){
       std::cout<<"15 ne doit pas être dans a !"<<std::endl;
       return false;
   }
   return true;
}
bool test03_union(){
    ArbreAVL<int> a, b,c;
    a.inserer(1);
    a.inserer(2);
    b.inserer(2);
    b.inserer(3);
    c=a+b;
    if(!(c.contient(1) && c.contient(2) && c.contient(3))){
        std::cout << "Erreur dans union, 3 manquant!" << std::endl;
        return false;
    }
    return true;
}
bool test04_diff(){
    ArbreAVL<int> a,b,c;
    a.inserer(1);
    a.inserer(2);
    a.inserer(3);
    b.inserer(-1);
    b.inserer(3);
    b.inserer(4);
    c = a - b;
    if(c.contient(3)||c.contient (-1)||!c.contient(1)||!c.contient(2)){
        std::cout << "Erreur dans difference" << std::endl;
        return false;
    }
    return true;
}
bool test05_plusEgal(){
    ArbreAVL<int> a,b;
    a.inserer(1);
    b.inserer(2);
    b.inserer(3);
    a += b;
    if(!(a.contient(1) && a.contient(2) && a.contient(3))){
        std::cout << "Erreur dans union, 3 manquant!" << std::endl;
        return false;
    }
    return true;
}
bool test06_egalite(){
    ArbreAVL<int> a, b;
    for(int i=1;i<=5;i++) a.inserer(i);
    b.inserer(3);
    b.inserer(1);
    b.inserer(4);
    b.inserer(2);
    b.inserer(5);
    bool q=!(a==b);
    b.inserer(6);
    bool r=(a==b);
    if(q||r){
        std::cout<< "Erreur dans operateur egalite" << 
            "(evalue structure au lieu d'elements)"<< std::endl;
        return false;
    }
    return true;
}
bool test07_taille_ops(){
    ArbreAVL<int> a,b,c,d;
    for(int i=1;i<=500;i++) a.inserer(i);
    for(int i=251;i<=750;i++) b.inserer(i);

    if(a.taille()!=500 || b.taille()!=500){
        std::cout<<"Erreur taille initiale (a ou b .taille() doit etre 500)"  
            <<std::endl;
        return false;
    }

    c = a+b;
    if(c.taille()!=750){
        std::cout<<"Erreur taille + (1-500 + 251-750 doit etre 1-750)"
            <<std::endl;
        return false;
    }

    d = a;
    d += b;
    if(d.taille()!=750){
        std::cout<<"Erreur taille += (1-500 + 251-750 doit etre 1-750)"
            <<std::endl;
        return false;
    }

    c = a-b;
    if(c.taille()!=250){
        std::cout<<"Erreur taille - (1-500 - 251-750 doit etre 1-250)"
            <<std::endl;
        return false;
    }


    d = a;
    d -= b;
    if(d.taille()!=250){
        std::cout<<"Erreur taille -= (1-500 - 251-750 doit etre 1-250)"
            <<std::endl;
        return false;
    }

    return true;
}
bool test08_ops_identique(){
    ArbreAVL<int> a,b,c;
    bool r=false;
    for(int i = 1; i <=20; i++) {
        a.inserer(i);
        b.inserer(i);
    }
    a+=a;
    if(a.taille()!=20) r=true;
    c = a + b;
    if(c.taille()!=20) r=true;
    c = b - a;
    if(c.taille()!=0) r=true;
    b-=a;
    if(b.taille()!=0) r=true;
    if(r){
        std::cout<<"Erreur dans operations avec operateurs identiques"
            <<std::endl;
        return false;
    }
    return true;
}
bool test09_copie(){
    ArbreAVL<int> a,b;
    a.inserer(1);
    a.inserer(2);
    b = a;
    ArbreAVL<int> c(b);
    a.inserer(3);
    b.inserer(4);
    if(b.contient(3) || c.contient(4)){
        std::cout<<"Erreur copie non profonde"<<std::endl;
        return false;
    }
    return true;
}
bool testE_taille(){
    ArbreAVL<int> a;
    const int n = 2000000;
    for(int i=0; i<n;i++) a.inserer(i);
    
    auto debut = std::chrono::steady_clock::now();
    long long somme = 0;
    for(int i=0; i<n;i++) somme+=a.taille();
    auto fin = std::chrono::steady_clock::now();
    double duree = std::chrono::duration<double>(fin-debut).count();
    
    if(duree > 0.3){
        std::cout<<"taille() inefficace: "<<duree<<" secondes"<<std::endl;
        return false;
    }
    return true;
}
bool testE_egal(){
    ArbreAVL<int> a,b;
    const int n = 1500000;
    for(int i=0;i<n;i++){
        a.inserer(i);
        b.inserer(i);
    }

    auto debut = std::chrono::steady_clock::now();
    bool egal = (a==b);
    auto fin = std::chrono::steady_clock::now();
    double duree = std::chrono::duration<double>(fin-debut).count();

    if(!egal){
        std::cout<<"Egal logique mauvais"<<std::endl;
        return false;
    }
    if(duree > 0.3){
        std::cout<<"== inefficace: "<<duree<<" secondes"<<std::endl;
        return false;
    }
    return true;
}
bool testE_plusEgal(){
    ArbreAVL<int> a,b;
    const int n = 1500000;
    for(int i=0;i<n;i++){
        a.inserer(2*i);
        b.inserer(2*i+1);
    }

    auto debut = std::chrono::steady_clock::now();
    a += b;
    auto fin = std::chrono::steady_clock::now();
    double duree = std::chrono::duration<double>(fin-debut).count();

    if(duree > 0.3){
        std::cout<<"+= inefficace: "<<duree<<" secondes"<<std::endl;
        return false;
    }
    return true;
}

bool testE_plus(){
    ArbreAVL<int> a,b;
    const int n = 1500000;
    for(int i=0;i<n;i++){
        a.inserer(i);
        b.inserer(i+n);
    }

    auto debut = std::chrono::steady_clock::now();
    ArbreAVL<int> c = a + b;
    auto fin = std::chrono::steady_clock::now();
    double duree = std::chrono::duration<double>(fin-debut).count();

    if(duree > 0.3){
        std::cout<<"+ inefficace: "<<duree<<" secondes"<<std::endl;
        return false;
    }
    return true;
}

bool testE_moinsEgal(){
    ArbreAVL<int> a,b;
    const int n = 1500000;
    for(int i=0;i<n;i++){
        a.inserer(i);
        b.inserer(i+n);
    }
    a += b;
    b += a;

    auto debut = std::chrono::steady_clock::now();
    a -= b;
    auto fin = std::chrono::steady_clock::now();
    double duree = std::chrono::duration<double>(fin-debut).count();

    if(duree > 0.4){
        std::cout<<"-= inefficace: "<<duree<<" secondes"<<std::endl;
        return false;
    }
    return true;
}

int main(){
    test00_compilation();
    int nb_types_erreur=0;
    if(!test01()) nb_types_erreur++;
    if(!test02()) nb_types_erreur++;
    if(!test03_union()) nb_types_erreur++;
    if(!test04_diff()) nb_types_erreur++;
    if(!test05_plusEgal()) nb_types_erreur++;
    if(!test06_egalite()) nb_types_erreur++;
    if(!test07_taille_ops()) nb_types_erreur++;
    if(!test08_ops_identique()) nb_types_erreur++;
    if(!test09_copie()) nb_types_erreur++;

    if(!testE_taille()) nb_types_erreur++;
    if(!testE_egal()) nb_types_erreur++;
    if(!testE_plusEgal()) nb_types_erreur++;
    if(!testE_plus()) nb_types_erreur++;
    if(!testE_moinsEgal()) nb_types_erreur++;
    return nb_types_erreur;
}


