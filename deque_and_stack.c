#include <iostream>
#include <stdexcept>


template<typename Tip>
class Lista {
public:
    Lista() {}
    virtual int brojElemenata() const = 0;
    virtual ~Lista() {} 
    virtual void obrisi() = 0;
    virtual void dodajIspred(const Tip &ele) = 0;
    virtual void dodajIza(const Tip &ele) = 0;
    virtual Tip operator [] (int indeks) const = 0;
    virtual Tip &operator [] (int indeks) = 0;
    virtual Tip trenutni() const = 0;
    virtual Tip &trenutni() =0;
    virtual bool prethodni() = 0;
    virtual bool next() = 0;
    virtual void pocetak() = 0;
    virtual void kraj() = 0;
};


template<typename Tip>
class DvostrukaLista: public Lista<Tip>{
    struct Cvor{
        Tip element;
        Cvor* next;
        Cvor* prev;
    };

    Cvor* poc;
    Cvor* trenut;
    Cvor* kr;
    int vel;

    bool DaLiJePrazna(){
        if(vel == 0) return true;  // ako je orazna daje true
        return false;
    }

public:
    DvostrukaLista(): Lista<Tip>(), poc(0), trenut(0), kr(0), vel(0) {}

    DvostrukaLista(const DvostrukaLista<Tip> &lista){
        vel=lista.vel;
        Cvor* temp1(lista.poc);
        Cvor* temp2(nullptr);

        while(temp1!=nullptr){
            Cvor* novi=new Cvor;
            novi->element=temp1->element;
            if(temp2==0){
                poc=novi;
                novi->prev=nullptr;
            }
            else{
                temp2->next=novi;
                novi->prev=temp2;
            }
            temp2=novi;
            if(temp1==lista.trenut){
                trenut=novi;
            }
            temp1=temp1->next;
        }

        kr=temp2;
        kr->next=nullptr;
    }

    DvostrukaLista<Tip> &operator =(const DvostrukaLista<Tip> &l){
        if(&l!=this) { 
            vel=l.vel;
        while(poc!= nullptr){
            trenut=poc;
            poc=poc->next;
            delete trenut;
        }

        Cvor* temp1(l.poc);
        Cvor* temp2(nullptr);

        while(temp1!= nullptr){
            Cvor* novi=new Cvor;
            novi->element=temp1->element;
            if(temp2==nullptr){
                poc=novi;
                novi->prev=nullptr;
            }
            else{
                temp2->next=novi;
                novi->prev=temp2;
            }

            temp2=novi;
            if(temp1 == l.trenut){

                trenut=novi;
            }

            temp1=temp1->next;
        }
        kr=temp2;
        kr->next=nullptr;  //kraj
        }

    return *this;

    }


    int brojElemenata() const { 
        return vel; 
    }

    Tip trenutni() const {
      if(vel == 0) throw ("Dvostruka lista je prazna!");
        return trenut->element;
    }
    Tip &trenutni(){
 if(vel == 0) throw ("Dvostruka lista je prazna!");
        return trenut->element;
    }
    bool prethodni(){
         if(vel == 0) throw ("Dvostruka lista je prazna!");
        if(trenut == poc) return false;  //na picetku smo
        else
        trenut=trenut->prev;
        return true;
    }

    bool next(){
         if(vel == 0) throw ("Dvostruka lista je prazna!");
        if(trenut==kr) return false;
        else
        trenut=trenut->next;
        return true;
        
    }
    void pocetak() {
       if(vel == 0) throw ("Dvostruka lista je prazna!");
        trenut=poc;
    }
    void kraj() {
      if(vel == 0) throw ("Dvostruka lista je prazna!");
       trenut=kr;
    }

    void obrisi(){
         if(vel==0) throw ("Dvostruka lista je prazna!");
        
        if(trenut==poc){
            poc=poc->next;
            delete trenut;
            trenut=poc;
            if(vel==0) kr=nullptr;
        }
        else{
            Cvor* pom(trenut);
            Cvor* pom1(trenut);
            if(trenut->next!=nullptr) 
            pom1=pom1->next;

            pom=pom->prev;
            pom->next=trenut->next;
            if(trenut->next!= nullptr) pom1->prev=pom;

            delete trenut;

            if(pom->next != nullptr) trenut=pom1;
            else if(pom->next == nullptr){
                kr=pom;
                trenut=pom;
            }
        }
        vel--;
    }



    void dodajIspred(const Tip &el){
          Cvor* novi=new Cvor;
    novi->element=el;
    if(vel==0){
        poc=novi; kr=novi; trenut=novi;
        novi->next=nullptr;
        novi->prev=nullptr;
        vel++;
        return;
    }
    if(trenut==poc){
        novi->next=poc;
        poc->prev=novi;
        novi->prev=nullptr;
        poc=novi;
        vel++;
        return;
    }
    else{
        Cvor* pom(trenut);
        pom=pom->prev;
        novi->next=trenut;
        novi->prev=pom;
        pom->next=novi;
        trenut->prev=novi;
        vel++;
    }
    
    }
    void dodajIza(const Tip &el){
        Cvor* novi=new Cvor;  //ne prolazi test sa zagradom!
    novi->element=el;
    if(vel==0){
        poc= kr = trenut = novi; 
        novi->next=nullptr;
        novi->prev=nullptr;
        vel++;
        return;
    }
   
        if(trenut!=kr){
            Cvor* neki(trenut);
            neki=neki->next;
            novi->next=neki;
            novi->prev=trenut;
            trenut->next=novi;
            neki->prev=novi;
        }
        else if(trenut==kr) {
            kr=novi;
            trenut->next=novi;
            novi->prev=trenut;
            novi->next=nullptr;
        }
        vel++;
   
    }



    Tip operator [] (int i) const{
        if(i<0 || i>=vel) throw ("Indeks je u neispravnom opesgu.");
        Cvor* pom(poc);
        int j = 0;
       while(j != i){
            pom=pom->next;
            j++;
       }
        return pom->element;
    }

    Tip &operator [] (int indeks){
        if(indeks<0 || indeks>=vel)  throw ("Indeks je u neispravnom opesgu.");
        Cvor* pom(poc);
        for(int i=0;i<indeks;i++) pom=pom->next;
        return pom->element;
    }
    ~DvostrukaLista() {
        while(poc!=nullptr){
            trenut=poc;
            poc=poc->next;
            delete trenut;
        }
        
    }
    
};





template<typename Tip>
class DvostraniRed {
    DvostrukaLista<Tip> lista;
public:

    DvostraniRed (): lista() {}
    void brisi(){
        if(lista.brojElemenata()==0) throw ("Dvostrani red je prazan!");

        int vel = lista.brojElemenata();

        for(int i=0;i<vel;i++) 
        lista.obrisi();
    }

    int brojElemenata() const { 
        return lista.brojElemenata(); 
        }

    void staviNaVrh(const Tip& el){
        if(lista.brojElemenata() != 0) lista.kraj();
        lista.dodajIza(el);
    }

    Tip skiniSaVrha(){
        if(lista.brojElemenata()==0) throw ("Dvostrani red je prazan!");
      
        lista.kraj();
        Tip e = lista.trenutni();
        lista.obrisi();
        return e;
    }

    void staviNaCelo(const Tip& el){
        if(lista.brojElemenata()!=0) lista.pocetak();
        lista.dodajIspred(el);
    }

    Tip skiniSaCela(){
        if(lista.brojElemenata() == 0) throw ("Dvostrani red je prazan!");

        if(lista.brojElemenata()!=0) lista.pocetak();
        Tip e = lista.trenutni();
        lista.obrisi();
        return e;
        
    }

    Tip &vrh(){
        if(lista.brojElemenata()==0) throw ("Dvostrani red je prazan!");
        if(lista.brojElemenata()!=0) lista.kraj();
        return lista.trenutni();
    }

    Tip &celo(){
        if(lista.brojElemenata()==0) throw std::domain_error("Dvostrani red je prazan!");
        if(lista.brojElemenata()!=0) lista.pocetak();
        return lista.trenutni();
    }
    ~ DvostraniRed() {}  //treba i destr!
};


///////TESTOVI/////////

void test1(){
    DvostraniRed<int> red;

    for(int i=0;i<5;i++) 

    red.staviNaCelo(i);
   
    red.brisi(); 
    
    std::cout<<red.brojElemenata();
    
   
}


void test3(){
    DvostraniRed<double> red;
   
    for(int i = 0;i < 4; i ++) red.staviNaVrh(i); 
       
}


void test4(){
    DvostraniRed<int> red;

    for(int i=0;i<10;i++) red.staviNaVrh(i);
   
    for(int i=0;i<10;i++) red.skiniSaVrha();

       std::cout<<red.brojElemenata();

}


void test5(){
    DvostraniRed<int> red;

    for(int i=0;i<10;i++) red.staviNaCelo(i);
    
  
    for(int i=0;i<3;i++) red.skiniSaCela();
       
   std::cout<<"br elemenata je"<<red.brojElemenata()<<"celo je sada"<<red.celo();
}


int main() {

    DvostraniRed<int> dr;
for (int i(10); i<=50; i+=10)
	dr.staviNaVrh(i);
std::cout << dr.brojElemenata() << " " << dr.vrh() << " ";
dr.brisi();
for (int i(10); i<=50; i+=10)
	dr.staviNaVrh(i);
std::cout << dr.brojElemenata() << " ";
for (int i(1); i<=5; i++)
	std::cout << dr.skiniSaVrha() << " ";
std::cout << dr.brojElemenata();

    
    return 0;
}
