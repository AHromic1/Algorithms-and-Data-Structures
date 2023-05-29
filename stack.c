#include <iostream>

template <typename Tip> struct Cvor {
  Tip element;
  Cvor<Tip> *veza;
  Cvor(const Tip &el=0, Cvor *sljedeci=nullptr) : element(el), veza(sljedeci) {} //jer je din alokacija
};

template <typename Tip>   //BEZ ;

class Lista {

public:

Lista () {};  //ne virtual!!!
virtual int brojElemenata() const = 0;//getteri const

//virtual  Tip &trenutni() = 0;   //referenca da bi se moglo dalje raditi nad tim elementom, zasto const???
virtual  Tip &trenutni()  = 0;//mijenja se vrijednost
virtual Tip trenutni() const = 0;  //vraća se samo vrijednost 
virtual bool prethodni() = 0;  //= 0, implementacija u izvedenim klasama

virtual bool sljedeci()  = 0;

virtual void pocetak() = 0;

virtual void kraj() = 0;

virtual void obrisi() = 0;

virtual void dodajIspred(const Tip& el) = 0;

virtual void dodajIza(const Tip& el) = 0; //zasto se prosljedjuje po referenci 

//kaze u napomeni da se brise i sl, a prije toga da nema implementacije??? - destruktor 
virtual Tip &operator[] (int i) = 0;  // s referencom ili bez ?   moze bez? 

virtual Tip operator[] (int i) const = 0;  // isto kao za trenutni


virtual ~ Lista() {}; 

};


template <typename Tip>
 class JednostrukaLista : public Lista<Tip> {
     private:

Cvor<Tip> *poc = nullptr , *tekuci = nullptr, *kr = nullptr;  //kada se template nesto koristi, MORA se reci sta je !

int lduzina, dduzina; 
int vel;
//tekuci pokazuje na tekuci 
bool daLiJePrazna(){
    return (vel == 0); //ako vrati 1 lista je prazna 
}


 
 public:
 JednostrukaLista(){
    
poc = nullptr;
tekuci = nullptr;
kr = nullptr;
//lduzina = 0;
//dduzina = 0;
vel = 0;
    
     //treba li negdje nullptr? sta da su bili shared pokazivaci?
 }


JednostrukaLista (const JednostrukaLista<Tip> &l){
    poc = new Cvor<Tip>  (l.poc->element, nullptr);  //inic, zasad je null
    Cvor<Tip> *pom = poc;
    Cvor<Tip> *pom2 = l.poc;  //bez okruglih zagrada

    while(pom2 != l.kr){
        pom->veza = new Cvor<Tip>  (pom2->element, nullptr );
        pom2 = pom2->veza;
        pom = pom -> veza;
    }
    kr = pom;
    tekuci = l.tekuci;
    vel = l.vel;
}


JednostrukaLista &operator=(const JednostrukaLista<Tip> &l){
    if(&l != this){  //samododjela

    poc = new Cvor<Tip> (l.poc -> element, nullptr);  //zbog ovoga treba konstruktor ( : 

    Cvor<Tip> *pom = poc;
    //brisemo postojece cvorove:
    /*
while(poc != nullptr){
         tekuci = poc -> veza;  //da bi se mogla kretati kroz listu, brisem preko tekuceg
         delete poc;
         poc = tekuci;

     }
     delete poc;  //jso zadnji element obrisan
     //poc = nullptr;  // okej?
     tekuci = nullptr;
     kr = nullptr;   //izbrisani su svi elementi na koje pokazuju, sada svima još dodijelim nullptr

    // lduzina = 0;
   //  dduzina = 0; 
     vel = 0;
*/
    Cvor<Tip> *pom2 = l.poc;  //bez okruglih zagrada

    while(pom2 != l.kr){
        pom->veza = new Cvor<Tip>  (pom2->element, nullptr );
        pom2 = pom2->veza;
        pom = pom -> veza;
    }
    kr = pom;
    tekuci = l.tekuci;
    vel = l.vel;

    }

    return *this;

}

 ~JednostrukaLista(){
     //npr ako napravim ovdje novi cvor, da li trebam i unistiti? 
     /*for(Cvor<Tip> * p = pocetak; p != nullptr; p->veza){
         delete p;
     }*/
     
     while(poc != kr){
         tekuci = poc -> veza;  //da bi se mogla kretati kroz listu, brisem preko tekuceg
         delete poc;
         poc = tekuci;

     }
     delete poc;  //jso zadnji element obrisan
     //poc = nullptr;  // okej?
     tekuci = nullptr;
     kr = nullptr;   //izbrisani su svi elementi na koje pokazuju, sada svima još dodijelim nullptr

     //lduzina = 0;
     //dduzina = 0; 
     vel = 0;

 }

int brojElemenata() const override{
    return vel;
}

Tip trenutni() const override{  
   
    return tekuci->element; 
}
Tip &trenutni()  override{  //PROVJERI
   
    return tekuci->element;  
}

bool prethodni() override{
    if(daLiJePrazna()) throw "Lista je prazna!";
    if(tekuci == poc) return false;  //ako je na prvom mjestu nista se ne desava; moglo je i preko lduzine

    Cvor <Tip> * pom = poc;

    while(pom->veza != tekuci){
        pom = pom -> veza;
    }
    tekuci = pom;

return true;
}

 bool sljedeci() override{
     if(daLiJePrazna()) throw "Lista je prazna!";
    if(tekuci == kr) return false;

    tekuci = tekuci -> veza;

return true;

 }

 void pocetak() override{  //ali tekuci je jedan ispred? 

     if(daLiJePrazna()) throw "Lista je prazna!";
     tekuci = poc;  

 }

 
void kraj() override{  
     if(daLiJePrazna()) throw "Lista je prazna!";

        tekuci = kr;
}

 void obrisi() override{
      if(daLiJePrazna()) throw "Lista je prazna!";
    
    if(vel == 1){  //specifican slucaj kada se u listi nalazi samo jedan element 
    delete tekuci; 
    kr= nullptr; 
    poc = nullptr;
    vel = 0;
    return;
    }
    if(tekuci == poc){
        poc = poc->veza;
       /* Cvor <Tip> *pom = poc; //radi i bez pom
        tekuci = tekuci->veza;
        poc = tekuci;
        delete pom;*/
        delete tekuci;
        tekuci = poc;
        vel -= 1;

        return;
    }
    if (tekuci == kr){
        Cvor<Tip> *pom = poc;
        //for(int i = 0; i < vel -1 ; i++)  //doci ce do predzadnjeg
      while(pom ->veza != tekuci)
            pom = pom->veza;
            
        
        delete kr;
        tekuci = pom;
        kr = pom;  //moram imati ovaj atribut, dio je klase 
        pom = nullptr; 
        vel -= 1;
        return;
    }

    //svi drugi slucajevi:
    Cvor<Tip> *pom = poc;
    //brojanje
    int i = 0;
    //neefikasno bilo!

    while (pom -> veza!= tekuci) 
        pom = pom->veza;  //doci ce do jednog prije tekuceg
    

    pom->veza = tekuci->veza;  //pom sada pokazuje na onog poslije tekuceg 
    delete tekuci; //brisemo tekuci koji sada više nije u listi, ali jeste u memoriji 
    tekuci = pom->veza; //tekuci je iduci neobrisani element
    pom = nullptr;
    vel -= 1; 
     
}

 void dodajIspred(const Tip& el) override{
     
     
     //slucaj 1
     if(vel == 0){
         
         Cvor<Tip> *novi = new Cvor<Tip> (el, poc);  //dvije vrijednost da s einic!!!
         tekuci = novi;
         poc = novi;
         kr = novi;
         vel+=1;
         return;
     }

     //slucaj 2
     if(tekuci == poc){
          Cvor<Tip> *novi = new Cvor<Tip> (el, poc);
         /*poc = poc->veza;// jedna iza poc
         novi->veza = poc; //prvi pokazuje na drugi
         poc = novi; //novi je prvi element, tj pocetak sada pokazje na novi*/
         poc = novi;  //lakše ovako, sada je početak jednostavno novi 
         vel+=1;
         return;

     }
    //slucaj 3
    Cvor<Tip> *novi = new Cvor<Tip> (el, nullptr);
    Cvor <Tip> *pom = poc;
    while(pom ->veza != tekuci){
            pom = pom->veza;
    }
        
        pom -> veza = novi;
        novi-> veza = tekuci;
        pom = nullptr;

    vel+=1;

}

 void dodajIza(const Tip& el) override{
     Cvor<Tip> *novi = new Cvor<Tip> (el, nullptr);

     
        //slucaj 1
     if(vel == 0){
         tekuci = novi;
         poc = novi;
         kr = novi;
         vel+=1;
         return;
     }

     //slucaj 2
     
    if(tekuci == kr){
        kr -> veza = novi;
        kr = novi;
        vel +=1;
        return;
    }


    Cvor<Tip> *pom = tekuci->veza; //pok, bez din al, pokazuje na elemnt iza tekuceg
    tekuci->veza = novi; //tekuci pokazuje na novi
    novi->veza = pom;  //novi pokazuje na pomocni, uveden je u listu
    pom = nullptr;
    vel+=1;

 } 

 Tip operator[] (int i) const override{
     if(i < 0 || i >= vel) throw ("Indeks je u nedozvoljenom opsegu!");  
     // pr u testovima kakvo se uzima i

    Cvor<Tip> *pom = poc;
     for(int j = 0; j < i; j++){
         pom = pom -> veza;
     }
    return pom -> element;

 }

Tip &operator[] (int i) override{
    if(i < 0 || i >= vel) throw ("Indeks je u nedozvoljenom opsegu!");  
     // pr u testovima kakvo se uzima i

    Cvor<Tip> *pom = poc;
     for(int j = 0; j < i; j++){
         pom = pom -> veza;
     }
    return pom -> element;
}


 };


//////////////////////////////STEK////////////////////////////////




template <typename Tip>
class Stek{

private:
JednostrukaLista<Tip> l;

bool daLiJePrazan(JednostrukaLista<Tip> l2){
    return (l2.brojElemenata()); //ako je broj elmenata nula vraca false
}

//int vel;
 
 public:

//void operator = (const Stek &s);  lista ce se pobrinuti msm
Stek (const Stek &s){
   l(s);
}
 Stek() {
     l();
 } // Podrazumijevani konstruktor
 //virtual ~Stek() {} // Bazni destruktor, lista ce se pobrinuti
  void brisi() {  //brise sve elemente iy steka 
    Cvor<Tip> *t = l.trenutni();
    t = l.pocetak();
    while(1){
         bool pom(l.prethodni()());
            if(!pom){  //kada je trenutni na pocetku liste break
                break;
            }      
    }

    while(1){
        bool pom(l.sljedeci());
        
            if(!pom){  //kada je trtenutni na kraju liste break
                break;
            } 
            l.obrisi();  //brise se trenutni  
           
    }
   
  }


  void stavi(const Tip& el){

       while(1){
        bool pom(l.sljedeci());
        
            if(!pom){  //kada je trtenutni na kraju liste break
                break;
            }  
    }

    //da li bi moglo while(l.sljedeci())  

    //kada je tekuci na kraju dodati clan
    l.dodajIza(el);

  }
  Tip skini() {
      if(!daLiJePrazan(l)) throw ("Stek je prazan!");
      while(1){
        bool pom(l.sljedeci());
        
            if(!pom){  //kada je trtenutni na kraju liste break
                break;
            }  
    }

    //da li bi moglo while(l.sljedeci())  

    Tip temp = l.trenutni();
    l.obrisi();
    
    return temp;

  }

  const Tip& vrh() {
           if(!daLiJePrazan(l)) throw ("Stek je prazan!");
        while(1){
        bool pom(l.sljedeci());
        
            if(!pom){  //kada je trtenutni na kraju liste break
                break;
            }  
    }

    //da li bi moglo while(l.sljedeci())  

    
    
    return l.trenutni();




  }




  int brojElemenata() const {
      return l.brojElemenata();
  } 
    };



int main(){


    return 0;
}