#include <iostream>
#include <stdexcept>
#include <ctime>
#include <string>
#include <utility>
using namespace std;

//moja hash funkcija koja se pridrzava pravila navedenih u postavci
unsigned int hashFunkcija(int ulaz, unsigned int max) {
unsigned int suma=5383;
// 5383 je random pocetna vrijednost koja poboljsava distribuciju
for (int i = 0; i< ulaz; i++)
suma = suma*35 + i;
return suma % max;
}

////mape iz pripremne 8 i 6:
template <typename TipK, typename TipV>

//apstraktna klasa 
class Mapa{
    public: 
    Mapa(){}
    virtual ~ Mapa() {};  //VISE NIKADA NEMOJ ZABORAVITI VITICASTU ZAGRADU!!! NIKADA
    virtual  TipV operator[] (const TipK key) const = 0;
    virtual TipV &operator[] (TipK key) = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const TipK &key) = 0; 

};



template <typename TipK, typename TipV>
struct Cvor{
    TipK klj;
    TipV vr;
    Cvor *roditelj,*lijevodijete,*desnodijete;
    Cvor(const TipK &k, const TipV &v, Cvor *p=nullptr, Cvor *l=nullptr, Cvor *d=nullptr){
        klj=k;
        vr=v;
        roditelj=p;
        lijevodijete=l;
        desnodijete=d;
    }
};


template<typename TipK, typename TipV>

class BinStabloMapa: public Mapa<TipK, TipV>{

    int vel;
    Cvor<TipK, TipV> *korijenski=nullptr;

    public:
    //konstruktor
    BinStabloMapa(): vel(0), korijenski(nullptr) {}

    void kopiraj(Cvor<TipK,TipV> *p){
        if(p!=nullptr){
            (*this)[p->klj]=p->vr;  //koristi this, lakse je!
            kopiraj(p->lijevodijete);
            kopiraj(p->desnodijete);
        }
    }

    BinStabloMapa(const BinStabloMapa<TipK, TipV> &BSM){
        if(BSM.vel!=0) kopiraj(BSM.korijenski);
        vel=BSM.vel; 
    }

//jednako
    BinStabloMapa &operator=(const BinStabloMapa<TipK,TipV> &BSM){
        if(this!=&BSM){
            obrisi();
            kopiraj(BSM.korijenski);
            vel=BSM.vel;
        }
        return *this;
    }

    //destruktor

    ~BinStabloMapa(){
        if(vel != 0) {
            while(korijenski != nullptr) obrisi(korijenski->klj);
        }
    }


    int brojElemenata() const{
        return vel;
        }

    void obrisi(const TipK &k){
        Cvor<TipK,TipV> *temp1=korijenski;  //pok na kor., ne nullptr

        Cvor<TipK,TipV>  *temp2=nullptr;

        Cvor<TipK,TipV> *temp3=nullptr;
        // Cvor<TipK,TipV> *temp4=nullptr;
        

        while(temp1!=nullptr && (temp1->klj)!=k){
            temp2=temp1;
            if(temp1->klj < k){
                temp1 = temp1->desnodijete;
            }
            else
             temp1 = temp1->lijevodijete;
        }

        if(temp1==nullptr) return;   //dosli do kraja, nije nista pronadjeno

        if(temp1->lijevodijete==nullptr) 
        temp3=temp1->desnodijete;

        else if(temp1->desnodijete==nullptr) 
        temp3=temp1->lijevodijete;

        else{
            temp3=temp1->lijevodijete;

            Cvor<TipK,TipV> *n1;
            Cvor<TipK,TipV> *n2;

            n1=temp3->desnodijete;
            n2=temp1;

            while(n1!=nullptr){
                n2=temp3;
                temp3=n1;
                n1=temp3->desnodijete;
            }

            if(temp1!=n2){
                n2->desnodijete=temp3->lijevodijete;
                temp3->lijevodijete=n1->lijevodijete;
            }
            temp3->desnodijete=temp1->desnodijete;
        }
        if(temp2==nullptr) korijenski=temp3;

        else{
            if(temp2->lijevodijete==temp1) temp2->lijevodijete=temp3;
            else temp2->desnodijete=temp3;
        }

        delete temp1;
        vel--;
    }

    void obrisi(){
        while(korijenski!=nullptr) obrisi(korijenski->klj);  //brisu se redom kevi
        
        korijenski=nullptr;
        vel=0;

        /* Cvor<TipK,TipV> *temp1=korijenski;  //pok na kor., ne nullptr

        Cvor<TipK,TipV>  *temp2=nullptr;
        
        while(temp1!=nullptr && (temp1->klj)!=k){
            temp2=temp1;
            if(temp1->klj < k){
                temp1 = temp1->desnodijete;
            }
            else
             temp1 = temp1->lijevodijete;
        }*/
    }

    TipV operator[](const TipK k)const{

        Cvor<TipK,TipV> *r=korijenski;

        while(r != nullptr){

            if((r->klj)==k){ 
            return r->vr;
            }

            else if( (r->klj) < k)  {
            r=r->desnodijete;
            }

            else{
            r=r->lijevodijete;
            } 
        }

        if(r==nullptr) return TipV();  //default vrijednost, kao u pz6
        return r->vr;
    }


    TipV &operator[](TipK k){
        Cvor<TipK,TipV> *r=korijenski;

        while(r!=nullptr){

            if((r->klj)==k) return r->vr;
            else if((r->klj) < k) r=r->desnodijete;
            else r = r->lijevodijete;
        }

        if(r == nullptr){
            vel++;
        
            Cvor<TipK,TipV> *r2=korijenski,*n=nullptr;
            r=new Cvor<TipK,TipV>(k,TipV());  //default vr
            
            while(r2 != nullptr){
                n = r2;
                if((r2->klj) > (r->klj)) r2=r2->lijevodijete;  //idemo ulijevo
                else r2 = r2->desnodijete;   //idemo udesno
            }
        
        if(n==nullptr){
             korijenski=r;  //sp sl
        }

        else if((n->klj) > (r->klj)){
            n->lijevodijete=r;
            r->roditelj=n;
            }

        else{
            n->desnodijete=r;
            r->roditelj=n;
            }
        }
        return r->vr;
    }
};


template <typename TipK, typename TipV>

class NizMapa: public Mapa<TipK, TipV> {
   private: 
   int vel, kapacitet;
   std::pair<TipK, TipV> *niz; //dovoljna jedna zvjezdica
   

   public: 
   //konstruktor
   NizMapa(){
       kapacitet=10;
       vel = 0;
        niz=new pair<TipK,TipV>[kapacitet];
    
   } //random broj  za kapacitet
   //destruktor
   ~NizMapa< TipK, TipV> (){
       delete[] niz;
       kapacitet = 0;
       vel = 0; 
   }

   //obrisi citavu mapu
   void obrisi(){
        if(!vel) throw ("Map is empty!");
      delete[] niz;
        //jer je receno da se opet moze dodavati, tj. struktua mape je zadrzana
        kapacitet = 10; 
        vel = 0; 
         niz = new std::pair<TipK, TipV> [kapacitet];
   }

    //obrisi samo jedan element
   void obrisi(const TipK& key){
       if(!vel) throw ("Map is empty!");
       bool deleted = 0;
       for(int i = 0; i < vel; i++){
           if(niz[i].first == key){  //ako je pronadjen
              for(int j=i;j<vel;j++) niz[j] = niz[j + 1]; 
               deleted = 1;
               break;
           }
       }
       if(!deleted) throw ("Key does not exist!");
       vel--;
   }

    TipV operator[] (const TipK key) const {
        //ako ne postoji da li treba dodati?   DA
      
    //   bool found = 0;
      
       for(int i = 0; i < vel; i++){
           if(niz[i].first == key){
               return niz[i].second;
               //found = 1;
           }
       }
       ///AKO NIJE PRONADJEN
       /*std::pair<TipK, TipV> novi = new std::pair<TipK, TipV>(key, TipV());  //alocirali smo novi element
       vel++;*/
       return TipV();
      
    }

    TipV &operator[] (TipK key){
        //ako ne postoji da li treba dodati? 
        //treba dodati    
        
       //bool found = 0;

       for(int i = 0; i < vel; i++){
           if(niz[i].first == key){
               return niz[i].second;
               //found = 1;
           }
       }
       //if(!found) return TipV(); //VRACA DEFAULT VRIJEDNOST ZA VALUE
       if(vel == kapacitet){  
           kapacitet*=2;  //povecavamo kapacitet, najlakse odmah 2x
        pair<TipK,TipV> *temp=new pair<TipK,TipV> [kapacitet];

        for(int i=0;i<vel;i++) temp[i]=niz[i];
        delete[] niz;
        niz=temp;
        temp=nullptr;
       }
        //TipV vr=TipV(); ne treba
    niz[vel].first=key;
    niz[vel].second=TipV();
    vel++;  //dodan element 
    return niz[vel-1].second;  //vel - 1 jer je nova vel uvecana 

       //return TipV();
     
    }

//operator dodjele
    NizMapa<TipK, TipV> &operator= (const NizMapa &M){
        if(this!= &M){
            delete [] niz;  //jer u obrisi nisam  
            //alociranje nove memorije
            kapacitet = M.kapacitet;
            vel = M.vel;
            niz = new std::pair<TipK, TipV> [kapacitet];
            for(int i = 0; i < vel; i++){
                niz[i] = M.niz[i];
            }
        }
            return *this;


    }

        //kopirajuci konstruktor 
        NizMapa (const NizMapa &M): kapacitet(M.kapacitet), vel(M.vel), niz(new std::pair<TipK, TipV> [M.kapacitet]) {   
        for(int  i = 0; i < vel; i++)
        niz[i] = M.niz[i];
        }

        int brojElemenata() const {
            return vel; 
        }

};
//////

////HashMapa

template <typename TipK, typename TipV>

class HashMapa: public Mapa<TipK, TipV>{
    private:

    pair<TipK, TipV>* niz;
     int maks; //maksimalni maks koji se ce po potrebi prosirivati 
    int vel; //stvarna vel

    unsigned int (*funkcija)(TipK, unsigned int);  //neka proizvoljna hash funkcija
    
    bool d;  // za funkciju
    
public:
//konstruktor
    HashMapa(): maks(10000), vel(0){  //, tmp(TipV()){
        niz=new pair<TipK, TipV>[maks];
        funkcija=NULL;
        d=false;
    
        for(int i = 0;i < maks; i++){
            niz[i].first=TipK();  //default vrijednost, ovo ili {}
            niz[i].second=TipV();
        }
    }
    
//konstruktor 2
    HashMapa(const HashMapa<TipK, TipV> &m){
        maks=m.maks;
        vel=m.vel;
        //tmp=m.tmp;
        d=m.d;
        niz=new pair<TipK, TipV>[maks];
        funkcija=m.funkcija;
    
        for(int i = 0; i < maks; i++){
            niz[i].first=m.niz[i].first;
            niz[i].second=m.niz[i].second;
        }
    }
    //destruktor
     ~HashMapa(){
        delete [] niz;
        vel=0;
        maks = 0;  //treba li pr
        funkcija=NULL;
    }


    HashMapa<TipK, TipV> &operator =(const HashMapa<TipK, TipV> &m){
        if(this!=&m){  //samododjela!
    
        delete [] niz;
    
        maks=m.maks;
        vel=m.vel;
        d=m.d;

        niz=new pair<TipK, TipV>[maks];
        funkcija=m.funkcija;
    
        for(int i=0; i<maks; i++){
            niz[i].first=m.niz[i].first;
            niz[i].second=m.niz[i].second;
        }
        }
    
        return * this;
    }

    int brojElemenata() const { 
        return vel; 
        
    }

    void definisiHashFunkciju(unsigned int (*funk)(TipK, unsigned int)){
        d = true;
        funkcija = funk;
    }
    
    void obrisi() {
        vel = 0;
        delete [] niz;
        //MORA SE OPET ALOCIRATI, KAO I U NIZMAPA! 
        niz=new pair<TipK, TipV>[maks];
        for(int i = 0; i < maks; i++){
            niz[i].first=TipK();
            niz[i].second=TipV();
        }
    }
    ////
    
    void obrisi(const TipK &k) {
        if(!d) throw std::domain_error("Nije definisana hash funkcija!");
        
        unsigned int i(funkcija(k, maks)); //izracunali indeks pomocu hash funkcije
        
         if(niz[i].first == k){
            niz[i].first=TipK();
            niz[i].second=TipV();
            //delete niz[i]; ne a, jer je struktura
            vel--;
        }
        
        else{
            
            for( ; ; ){
                
                if(i >= maks-1) i = 0; //vracamo se na pocetak liste i ponovo pretrazujemo, kao u pred. 
                
                if(niz[i].first == k){ //nasli k
                    vel--;
                    niz[i].first = -1;  //kljuc za koji se zna da ne postoji
                    niz[i].second=TipV();

                    // delete niz[i]; ne da, jer je struktura!
                   
                    return;
                }
                
            }
            
        }
   
    }
    
    TipV &operator[]( TipK k)  {
              if(!d) throw std::domain_error ("Nije definisana hash funkcija!");
              
        unsigned int i(funkcija(k, maks));
        if(niz[i].first==k) return niz[i].second;
       
        else if(niz[i].first==TipK()){  //dodaj
            vel++;
            niz[i].first=k;
            return niz[i].second;
        }
        else{

            if(i <= maks-1) i=0;
            while(niz[i].first!=TipK()){
                if(niz[i].first==k) return niz[i].second;
                if(i==maks-1) i=0;
                i++;
            }
        }

         vel++;
        niz[i].first=k;
       
        return niz[i].second;
    }
   ///

     TipV operator[](const TipK k) const {
            if(!d) throw std::domain_error("Nije definisana hash funkcija!");
        
        for(int i = 0; i < maks; i++){
            
            if(niz[i].first == k) {
            return niz[i].second;
            }
        }
        
        return TipV(); //pr
    }
};
    
int main (){
  srand(time(NULL));
 BinStabloMapa<int, int>bm;
    NizMapa<int, int>nm;
    HashMapa<int, int>hm;
    hm.definisiHashFunkciju(hashFunkcija);
    clock_t v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0, v6 = 0;
    
    for(int i=0;i<100;i++){
        v1=clock();
        bm[rand()]=rand();
        v2=clock();
        cout<<"Bsm dodavanje: "<<(v2-v1)/(CLOCKS_PER_SEC/1000)<<" ms."<< endl;
        v1=0; 
        v2=0;
    } 
    
    bm[50000]=10;
    
    for(int i=0;i<250;i++){
        v1=clock();
        nm[rand()]=rand();
        v2=clock();
        cout<<"Nm dodavanje : "<<(v2-v1)/(CLOCKS_PER_SEC/1000)<<" ms."<< endl;
        v1=0; 
        v2=0;
    }   
    
    
    nm[50]=10;
    
    for(int i=0;i<100;i++){
        
            v1 = clock();
            hm[rand()]=rand();
            v2 = clock();
        
        cout<<"Hm dodavanje: "<<(v2-v1)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
        v1=0; 
        v2=0;
    }   
    
////TRAZENEJ///////

    v1=clock();
    bm[1000];
    v2=clock();
    cout<<"Bsm: "<<(v2-v1)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
    
    v3=clock();
    cout<<nm[50]<<endl;
    v4=clock();
    cout<<"Nm: "<<(v4-v3)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
    
    v5=clock();
    cout<<hm[5000]<<endl;
    v6=clock();
    cout<<"Hm "<<(v6-v5)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
    
    v1 = 0;
    v2 = 0;
    v3 = 0;
    v4 = 0;
    v5 = 0;
    v6 = 0;
    
    /////brisanje
    
    v1=clock();
    bm.obrisi(5000);
    v2=clock();
    cout<<"Bs"<<(v2-v1)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
    
    v3=clock();
    nm.obrisi(50);
    v4=clock();
    cout<<"Nm "<<(v4-v3)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
    
    v5=clock();
    hm.obrisi(5000);
    v6=clock();
    cout<<"Hm: "<<(v6-v5)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
    
    /*generalno, moze se zakljuciti da je mapa implementirana preko binarnog stabla najlosije efikasnosti, s tim da je
    kod dodavanja hash mapa najsporija*/
    cout<<"kraj";
    return 0;
}