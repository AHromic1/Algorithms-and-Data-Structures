#include <iostream>
#include <ctime>
#include <stdexcept>
#include <utility>
#include <string>

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


int main() {
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
// jer oni nemaju vri pa ce se ispod ispisati 1
// Ali to zahtijeva implementaciju "Pristupnika" pa cemo priznavati
// rjesenje koje ispise broj 3
cout << m.brojElemenata(); // 3 ili 1

// Test brisanja
cout << " '" << m["Zagreb"] << "' " ; // ''
m.obrisi();
cout << m.brojElemenata(); // 0
cout << " '" << m["Sarajevo"] << "' "; // ''



    return 0;
}
