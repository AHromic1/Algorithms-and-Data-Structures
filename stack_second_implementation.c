#include <iostream>
#include <stdexcept>

using namespace std;  //radi testa

template <typename Tip> class Stek {
private:
  struct Cvor {
    Tip element;
    Cvor *veza;
    Cvor(const Tip &el, Cvor *v) : element(el), veza(v) {}
  };
  Cvor *vrhs{};
  int vel=0;

  bool daLiJePrazan (){
      return vel == 0;  //ako je prazan vraca true 
  }

public:
 
  Stek()  { //prazan stek
      vel = 0;
      vrhs = nullptr;
  }

  Stek(const Stek<Tip> &stek){  
      vel = stek.vel;  
        vrhs = 0;
      Cvor *pom1, *pom2 = stek.vrhs;


  for (;pom2 != nullptr; pom2 = pom2->veza) {  //sve dok nije kr
    Cvor *novi = new Cvor(pom2->element, nullptr);
    if (vrhs == nullptr)
      vrhs = novi;
    else {
      pom1->veza = novi;
    }
    pom1 = novi;
  }
  }

  Stek &operator=(const Stek<Tip> &stek){
       if (&stek != this){  //pr na samododjelu
 
       //prvo sve obrisati

        while (1) { //sve se brise
            if(daLiJePrazan()) break;
      if(daLiJePrazan()) throw "Prazan stek!";
      Tip pom(vrhs->element);
      Cvor *pom2 = vrhs->veza;
      delete vrhs; //dealokacija
      vrhs = pom2;
      vel--; //obrisano
    }

        Cvor *c1, *c2 = stek.vrhs;
        vrhs= 0;
        vel = stek.vel;
        for (c2 = stek.vrhs; c2 != nullptr; c2 = c2->veza) {
        Cvor *novi = new Cvor(c2->element, nullptr);
        if (vrhs == nullptr)
        vrhs = novi;
        else {
        c1->veza = novi;
        }
        
        c1 = novi;
    }

       }
  return *this;
  }


  ~Stek() { 
     while (1) { //sve se brise
            if(daLiJePrazan()) break;
    //  if(daLiJePrazan()) throw "Prazan stek!";
      Tip pom(vrhs->element);
      Cvor *pom2 = vrhs->veza;
      delete vrhs; //dealokacija
      vrhs = pom2;
      vel--; //obrisano
    }
      
    }

  void brisi() {
    while (1) { //sve se brise
            if(daLiJePrazan()) break;
      if(daLiJePrazan()) throw "Prazan stek!";
      Tip pom(vrhs->element);
      Cvor *pom2 = vrhs->veza;
      delete vrhs; //dealokacija
      vrhs = pom2;
      vel--; //obrisano
    }
  }

  void stavi(const Tip &el) {
    vel++; //povećavamo veličinu
    Cvor * novi = new Cvor(el, vrhs);
    vrhs = novi;
    
  }

  Tip skini() {
    if (daLiJePrazan()) throw ("Prazan stek!");
    Cvor *pom2 = vrhs->veza;
    Tip pom=vrhs->element;
    delete vrhs;  
    vel--;
    vrhs = pom2;
    return pom;
  }

  Tip &vrh() {
    if (daLiJePrazan())
      throw ("Prazan stek!");
    return vrhs->element;
  }

  int brojElemenata() const { 
      return vel; 
      }
};



//////////////////////
void test1(){
    Stek<double> s;
    s.stavi(5);
    s.stavi(10);  
}

void test2(){
     Stek<double> s;
    s.stavi(5);
    s.stavi(10);
    s.skini();
   
}
void test3(){
    Stek<double> s;
    Stek<double> s2;// = Stek<double> (5);
    //s2(5);
    s2.stavi(5);
    s=s2;
    Stek<double> s3(s);
}

void test4(){
     Stek<double> s;
    s.stavi(9);
    s.stavi(6);
    s.stavi(3);
    std::cout<<s.vrh();
}
void test5(){
    
    Stek<double> s;
    s.stavi(77);
    s.brisi();
    s.stavi(8); 
    
}
void test6(){
    Stek<int> s;
    s.stavi(77);
    s.stavi(8);
    std::cout<<s.brojElemenata();
    s.skini();
    std::cout<<s.brojElemenata();

}
void testizuzetak(){
    
    Stek<double> s;
    s.brisi();
    s.stavi(77);
    s.stavi(8); 
}

int main() {

int brel;
Stek<int> s;
for (int i(1); i<=5; i++)
	s.stavi(i);
{
        // Konstruktor kopije
	Stek<int> s2(s);
	Stek<int> s3;
        // Operator dodjele
	(s3=s).brojElemenata();
        // Destruktivna samododjela
        (s=s).brojElemenata();

	s.skini();
	brel = s2.brojElemenata();
	for (int i(0); i<brel; i++)
		std::cout << s2.skini() << " ";
	brel = s3.brojElemenata();
	for (int i(0); i<brel; i++)
		std::cout << s3.skini() << " ";
}
brel = s.brojElemenata();
for (int i(0); i<brel; i++)
	std::cout << s.skini() << " ";
  return 0;
}