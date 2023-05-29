#include <iostream>

using namespace std;


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


//// RED/ /////////////////////////////////////////
template <typename Tip> class Red  {
  private: 
    Cvor<Tip> *poc{}, *kr{};
    int vel = 0;
  
public:
  Red() : poc(nullptr), kr(nullptr), vel(0) {

  }
  ~Red() { 
      
   // if (poc == nullptr || vel == 0) throw "Red je prazan!";
    while (vel != 0) {
   Tip pom = poc->element;
   Cvor<Tip> *temp = poc->veza;
   delete poc;
   poc = temp;
   vel--;
  }
      
      
      } 
  //definisanje konstruktora i op dodjele
  Red(const Red<Tip> &r){
  Cvor<Tip> *temp = r.poc;
  while (temp != nullptr) {
    Cvor<Tip> *novo = new Cvor<Tip>(temp->element, nullptr);
    if (poc == nullptr){
      poc =  novo;
      kr = novo;
    }
    else {
      kr->veza = novo;
      kr = kr->veza;
    }
    vel++;
    temp = temp->veza;
  }
}
  Red( Red <Tip> &&r): vel(r.vel), poc(r.poc),kr(r.kr){
    r.poc=nullptr;
   r.kr=nullptr;
    r.vel=0;
 
}
  Red &operator=(const Red<Tip> &r){

  if (&r != this) { //samododjela
    
  brisi();  //sve se brise prvo 

  Cvor<Tip> *temp = r.poc;
  while (temp != nullptr) {
    Cvor<Tip> *novi = new Cvor<Tip>(temp->element, nullptr);
    if (poc == nullptr){
    poc = novi;
    kr = novi;
    }
    else {
      kr->veza = novi;
      kr = kr->veza;
    }
    temp = temp->veza;
    vel++;
  }
  }
  return *this;
}
  


  //ovaj je preko swap, "ukradeni" podaci
  Red &operator=(Red<Tip> &&r){
    std::swap(poc, r.poc);
    std::swap(kr,r.kr);
    std::swap(vel, r.vel);
    return *this;
}

  void brisi(){
      if (poc == nullptr) throw "Red je prazan!";
    while (vel != 0) {
   Cvor<Tip> *temp = poc->veza;
   delete poc;
   poc = temp;
   vel--;
  }
  }

  void stavi(const Tip &element){
      

  Cvor<Tip> *novi = new Cvor<Tip>(element, nullptr);
  if (poc == nullptr){
    poc = novi;
     kr = novi;
  }
  else {
    kr->veza = novi;
    kr = kr->veza;
  }

  vel++;

  }

  Tip skini(){
  if (poc == nullptr)
    throw "Red je prazan!";
   Tip pom = poc->element;
   Cvor<Tip> *temp = poc->veza;
   delete poc;
   poc = temp;
   vel--;
   return pom;
  
}
  Tip &celo() const{
      
  if (poc == nullptr)
    throw "Red je prazan!";
  return poc->element;

  }
  int brojElemenata() const { 
      return vel; }
};
 





void test1(){
    Red<double> r;
    r.stavi(7);
   
    
}
void test2(){
     Red<double> r;
    r.stavi(7);
    r.skini();
}

void test3(){
        Red<double> r1, r2;
        for(int i=0;i<4;i++){
            r1.stavi(i);
        }     
        r2=r1;      
}


void test5(){
      Red<double> r1, r2;
        for(int i=0;i<3;i++){
            r1.stavi(i);
        }
        r2=std::move(r1);
                 
}
void test6(){
     Red<double> r;
        for(int i=0;i<3;i++){
            r.stavi(i);
        }
        std::cout<<r.celo();
}

void test7(){
  Red<double> r;
        for(int i=0;i<3;i++){
            r.stavi(i);
        }
        r.brisi();
}
void test8(){
    Red<double> r;
    std::cout<<r.brojElemenata();
}
 
 ////


 int main(){
Red<int> r;
for (int i(1); i<=5; i++)
	r.stavi(i);
std::cout << r.brojElemenata() << " " << r.celo() << " ";
r.brisi();
for (int i(1); i<=5; i++)
	r.stavi(i);
std::cout << r.brojElemenata() << " ";
for (int i(1); i<=5; i++)
	std::cout << r.skini() << " ";
std::cout << r.brojElemenata() << " ";
for (int i(1); i<=5; i++)
	r.stavi(i);
std::cout << r.brojElemenata() << " " << r.celo();
     return 0;
 }


