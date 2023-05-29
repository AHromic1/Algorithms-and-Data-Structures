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

class NizLista : public Lista <Tip> {   //mora <Tip> !!! pr
    private:
    int  kapacitet, vel, tekuci;
Tip **niz;  //zasto mora dupli ? - testovi 
   
int testIzuzetak (int indeks){
    return vel != 0;  //ako je vel nula, tj ako je prazna lista vratit će false, u suprotnom je true
}

public:
NizLista<Tip>() {   //da li treba Tip?
   kapacitet = 10;  //neki broj staviti??? jer se mora alocirati s većim od 0
   vel = 0;
   tekuci = -1; //jerjoš nema nijedan element - nema ind negativni
   niz = new Tip* [kapacitet] {};  //alociram memoriju za pok, stvaranje liste, tj niza
}

//kopirajuci k  - da li trebaju i gore???
//+ dodati override 
//NizLista(const )


~NizLista<Tip>(){
    if(!niz) return ;

    for(int i = 0; i < vel; i++){  //vel ili kapacitet 
        delete niz[i];
    }
    delete [] niz; //brise se niz iz memorije
    tekuci = -1;
    vel = 0;
    kapacitet = 0; //vel i kapacitet su sada nula
    //sve vraćeno kao prije
}
 int brojElemenata() const override{
     return vel;
 }
//kopirajuci konstruktor 
NizLista<Tip> (const NizLista<Tip> &n): kapacitet(n.kapacitet), vel(n.vel), niz(new Tip *[n.kapacitet]), tekuci(n.tekuci){ //prostor za kopiranje novog
for(int i = 0; i < vel; i++){
   niz[i] = new Tip (n[i]);
}
//da li se destruktor poziva i ovdje?
}

  Tip &trenutni() override {  //DA LI VRAĆA STVARNO TRENUTNI ILI JEDAN PRIJE ??? - trenutni jer je tako u ovom slucaju odredjeno (by me)
     
     return *niz[tekuci];  //**niz - isti rezultat
 }

Tip trenutni() const override {  //DA LI VRAĆA STVARNO TRENUTNI ILI JEDAN PRIJE ??? - trenutni jer je tako u ovom slucaju odredjeno (by me)
     
     return *niz[tekuci];  //**niz - isti rezultat
 }


 // operator dodjele 

 NizLista<Tip> & operator = (const NizLista<Tip> &n){
     if(&n != this) { //zasto ref inace?  - test na samododjelu, nista se ne desava ako jedan te isti kopiramo
    /* if(n.kapacitet <= kapacitet){  //regularno se kopira
        for(int i = 0; i < n.vel; i++){
        niz[i] = (*n)[i];
        }
        kapacitet = n.kapacitet;
     }
     else{  //ako nije potrebno je dealocirati memoriju i alocirati novu sa dovoljno mjesta da primi n
     }*/

     //efikasnije da dva puta ne brisemo / dodajemo
        for(int i = 0; i < vel; i++){  //vel ili kapacitet 
        delete niz[i];
    }
    delete [] niz;

    niz = new Tip * [n.kapacitet];
    for(int i = 0; i < n.vel; i++){
        niz[i] = new Tip (n[i]);  //radi preko pok, ne samih clanova!!!
    }
    kapacitet = n.kapacitet;
    vel = n.vel;
    tekuci = n.tekuci; 
     }
     return *this;
 }

 bool prethodni() override{
     
     if (testIzuzetak(tekuci) == 0) throw "Lista je prazna! ";
     if (tekuci == 0) 
     return false;

     //for(int i = 0; i < tekuci; i++) niz++;
     tekuci -= 1;
     return true;
 }

 bool sljedeci() override{
     if (testIzuzetak(tekuci) == 0) throw "Lista je prazna! ";
     if (tekuci >=  vel - 1)  // ako je na kraju false i ništa se ne dešava
     return false;

     tekuci++;
     return true;
     //šta ako postoji samo jedan element
 }

 void pocetak() override{
     if (testIzuzetak(tekuci) == 0) throw "Lista je prazna! ";
tekuci = 0;
}

void kraj() override{
    if (testIzuzetak(tekuci) == 0) throw "Lista je prazna! ";
    tekuci = vel - 1;//kraj, bez -1 bi bilo iza kraja
}

 void obrisi() override{
     
     if (testIzuzetak(tekuci) == 0) throw "Lista je prazna! ";
        delete niz[tekuci];

        for(int i = tekuci; i < vel - 1; i++){ //od supljine
            niz[i] = niz[i + 1];
        }
        vel--;
        if(tekuci == vel) tekuci --;  //rubni slučaj, tekuci na zadnjem mjestu, on ostane vani nakon 
 }

 void dodajIspred(const Tip& el) override{
        if(vel == 0){
                tekuci = 0; 
                vel++;
                niz[0] = new Tip (el); 
                return;

        }

     if(vel > kapacitet) throw "Lista je puna! Nemoguce je dodati novi element!";

 if(vel == kapacitet)  {
        kapacitet *= 2;  //zauzima se duplo više prostora 
        auto pom = new Tip * [kapacitet];
        for(int i = 0; i < vel; i++){
            pom[i] = niz[i];
        }

        delete [] niz;  // ne mora for je rpom pokauje na ostalo
        niz = pom; 
    }  //pom se obriše na kraju
   
    
    for(int i = vel; i > tekuci; i--){

        niz[i] = niz[i - 1];

    }
    niz[tekuci] = new Tip(el); //svaki novi član dinamički alociran 
    vel++;

    tekuci++; //tekuci opet daje indeks istog elementa kao i prije ubacivanja, po zahtjevu zadatka 
    }



 void dodajIza(const Tip& el) override{//zasto se prosljedjuje po referenci 
 if(vel == 0){
                tekuci = 0; 
                vel++;
                niz[0] = new Tip (el); 
                return ;

        }

    if(vel > kapacitet) throw "Lista je puna! Nemoguce je dodati novi element!";

      if(vel == kapacitet)  {
        kapacitet *= 2;  //zauzima se duplo više prostora 
        auto pom = new Tip * [kapacitet];
        for(int i = 0; i < vel; i++){
            pom[i] = niz[i];
        }

        delete [] niz;  // ne mora for je rpom pokauje na ostalo
        niz = pom; 
    }  //pom se obriše na kraju
   
    niz[vel] = new Tip(el);  // S OVIM RADI

//rotiram redom
     for(int i = vel; i > tekuci + 1; i--){

        //niz[i] = niz[i - 1];
        Tip *temp; 
        temp = niz[i];
        niz[i] = niz[i - 1];
        niz[i - 1] = temp;

    }
    //niz[tekuci + 1] = new Tip( el);
    vel++;

}
Tip &operator[] (int i) override {  
    if (i < 0 || i > vel - 1) throw "Indeks nije u dozvoljenom opsegu!";
   return *niz[i];
}

Tip operator[] (int i) const override {  
    if (i < 0 || i > vel - 1) throw "Indeks nije u dozvoljenom opsegu!";
   return *niz[i];
}

};

//kaze u napomeni da se brise i sl, a prije toga da nema implementacije??? - destruktor 
 //Tip &operator[] (int i) = 0;  ne treba, jr je obicni niz koji vec podrzava indeksaciju???


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




int main (){

    //NizLista

NizLista<double> * l = new NizLista<double>;
l ->dodajIspred(2.5);
l->dodajIza(3);
std::cout<<"Trenutni element je"<<
l->trenutni();


NizLista<double> * l2 = l;
l2->pocetak();
for(int i = 0; i < l2->brojElemenata(); i++){ 
    std::cout<<"el ";
}
l->pocetak();
std::cout<<"Trenutni element je"<<
l->trenutni();

l2->kraj();
std::cout<<"Trenutni element je"<<
l2->trenutni();

l2->trenutni() = 2.4;

l->prethodni();
std::cout<<"Trenutni element je"<<
l->trenutni();

l->sljedeci();

std::cout<<"Trenutni element je"<<
l->trenutni();

l2->obrisi();

for(int i = 0; i < l2->brojElemenata(); i++){
std::cout<<l2->trenutni();


}

delete l;

delete l2;


JednostrukaLista<double> * l3 = new JednostrukaLista<double>;
l3 ->dodajIspred(2.5);
l3->dodajIza(3);
std::cout<<"Trenutni element je"<<
l3->trenutni();


JednostrukaLista<double> * l4 = l3;
l4->pocetak();
for(int i = 0; i < l4->brojElemenata(); i++){ 
    std::cout<<"el ";
}
l3->pocetak();
std::cout<<"Trenutni element je"<<
l3->trenutni();

l4->kraj();
std::cout<<"Trenutni element je"<<
l4->trenutni();

l4->trenutni() = 2.4;

l3->prethodni();
std::cout<<"Trenutni element je"<<
l3->trenutni();

l3->sljedeci();

std::cout<<"Trenutni element je"<<
l3->trenutni();


for(int i = 0; i < l3->brojElemenata(); i++){
std::cout<<l3->trenutni();


}
l3->obrisi();
for(int i = 0; i < l3->brojElemenata(); i++){
std::cout<<l3->trenutni();

}

delete l4;

delete l3;




    return 0;
};