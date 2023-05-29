#include <iostream>
#include <ctime>
#include <stdexcept>
#include <utility>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
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
        while(korijenski!=nullptr) obrisi(korijenski->klj);  //brisu se redom kljucevi
        
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
        
        if(n==nullptr) korijenski=r;  //sp sl

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


///niz mapa pz6/////
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

/*NAPOMENA: nijedan test nisam uspjela pokrenuti na c9, mada sam duzi vremenski period iznova pokusavala
 (ni za ovu ni za jednu drugu vjezbu, koje su prije prolazile
bez problema.) Greska koja se javljala je bila do c9, pretpostavljam, i glasila je:
IZLAZ KOMPAJLERA:
cc1plus: warning: ‘-Werror=’ argument ‘-Werror=implicit-function-declaration’ is not valid for C++
collect2: fatal error: vfork: Resource temporarily unavailable
compilation terminated.

Testirajuci rucno, sve je radilo na drugim online kompajlerima, te i u main-u c9 (osim testa 7).
Ukoliko bude doslo do neke sitnice, poput pogresnog razmaka i sl, koja bi uzrokovala pad testova, nadam se
da ce se ova cinjenica uvaziti.

hvala (:
*/


int main() {// Test rada sa tipom koji nema default konstruktor (std::vector)
// Osnovni test funkcionalnosti BinStabloMapa
BinStabloMapa<std::string,std::string> m;
m["Sarajevo"] = "BiH";
m["Zagreb"] = "Hrvatska";
cout << m.brojElemenata() << " " << m["Zagreb"] << " '"; // 2 Hrvatska

// Test praznih elemenata
cout << m["Beograd"] <<"' '"; // ''
cout << m["zagreb"] << "' "; // ''
m.obrisi("Zagreb");

// Potpuno korektna BinStabloMapa nece kreirati objekte "Beograd" i "zagreb"
// jer oni nemaju vrijednosti pa ce se ispod ispisati 1
// Ali to zahtijeva implementaciju "Pristupnika" pa cemo priznavati
// rjesenje koje ispise broj 3
cout << m.brojElemenata(); // 3 ili 1

// Test brisanja
cout << " '" << m["Zagreb"] << "' " ; // ''
m.obrisi();
cout << m.brojElemenata(); // 0
cout << " '" << m["Sarajevo"] << "' "; // ''


/*
  BinStabloMapa<int, int> BSM;
    NizMapa<int, int> NM;
    clock_t v1(0), v2(0), v3(0), v4(0);
    
    srand(time(NULL));
    
    for(int i=0;i<10000;i++){
        v1=clock();
        BSM[rand()]=rand();  //random puni
        v2=clock();
        cout<<"Binarno stablo mapa  dodavanje velikog broja (10000) elemenata jeizvrsila za:"<<(v2-v1)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
        //u milisekundama najbolje
        v1=0; 
        v2=0;
    } 
    
   //niz mapa
    
    for(int i=0;i<10000;i++){
        v3=clock();
        NM[rand()]=rand();
        v4=clock();
        cout<<"Niz mapa  dodavanje velikog broja (10000) elemenata je izvrsila za : "<<(v4-v3)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
        v3=0; 
        v4=0;
    }   */
    
  
    
   //Ocigledno je da implemetacija mape pmocu binarnog stabla postize bolju vremensku efikasnost u odnosu na onu implementaciju
  // s niz mapom
   

return 0;
}
