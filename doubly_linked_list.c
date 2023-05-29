#include <iostream>
using namespace std;

template<typename Tip>
struct Cvor{
    Cvor *prethodni,*sljedeci;
    Tip element;
    Cvor(const Tip &el, Cvor *previous, Cvor *next=nullptr):element(el),prethodni(previous),sljedeci(next){}
};

template<typename Tip>
class Lista{
public:
    Lista() {} 
    Lista(const Lista &l){}
    Lista &operator=(const Lista &l){}
    virtual ~Lista() {}
    virtual int brojElemenata() const=0; 
    virtual Tip &trenutni() const=0; 
    virtual bool prethodni()=0; 
    virtual bool sljedeci()=0; 
    virtual void pocetak()=0; 
    virtual void kraj()=0; 
    virtual void obrisi()=0;
    virtual void dodajIspred(const Tip& el)=0;
    virtual void dodajIza(const Tip& el)=0;
    virtual Tip &operator[](int i)const=0;
};


///dvostruka lista////////
template<typename Tip>
class DvostrukaLista: public Lista<Tip>{
    int vel;
    Cvor<Tip> *poc,*kr,*tekuci;
    bool DaLiJePrazna(){
        if(vel == 0) return true;
    }
    public:
    DvostrukaLista():Lista<Tip>(){
        vel = 0;
        tekuci = nullptr;;
        kr = nullptr;
        poc = nullptr;

    }

    ~DvostrukaLista(){
        auto it = poc;
        while(it!=nullptr){
            tekuci=it;
            it=it->sljedeci;  //pomjeramo se
            delete tekuci;
        }
        kr=nullptr;
        vel=0;
    }

    DvostrukaLista(const DvostrukaLista &l){
        try{
            vel=l.vel;
            if(l.poc!=nullptr){
                Cvor<Tip> *pomocni=l.poc,*temp;
                for(auto it=pomocni;it!=nullptr;it=it->sljedeci){
                    if(l.poc==it){
                        poc=new Cvor<Tip>{it->element,nullptr};
                        tekuci=poc;
                        if(it==l.tekuci) temp=poc;
                    }
                    else{
                        if(it==l.tekuci) temp=tekuci;
                        tekuci->sljedeci=new Cvor<Tip>{it->element,nullptr};
                        tekuci=tekuci->sljedeci;
                        if(l.kr==it) kr=tekuci;
                    }
                }
                vel=l.vel;
            }
            else{
                poc=tekuci=kr=nullptr;
                vel=0;
            }
        }
        catch(...){
            for(auto it=tekuci;it!=nullptr;it=it->sljedeci){
                it=poc->sljedeci;
                delete it;
                poc=tekuci;
            }
            vel=0;
        }
    }

    DvostrukaLista &operator=(const DvostrukaLista &dl){
        if(this==&dl) return *this;
        DvostrukaLista<Tip> kopija(dl);
        int duzina=vel;
        vel=kopija.vel;
        kopija.vel=duzina;
        Cvor<Tip> *replace=poc;
        poc=kopija.poc;
        kopija.poc=replace;
        replace=tekuci;
        tekuci=kopija.tekuci;
        kopija.tekuci=replace;
        replace=kr;
        kr=kopija.kr;
        kopija.kr=replace;
        return *this;
    }

    int brojElemenata()const{
        return vel;
        }

    Tip &trenutni()const{
        if(vel==0) throw domain_error("Dvostruka lista je prazna!");
        return tekuci->element;
    }

    bool prethodni(){
        if(tekuci==poc) return false;
        else
        tekuci=tekuci->prethodni;
        return true;
    }

    bool sljedeci(){
        if(tekuci==kr) return false;
        else
        tekuci=tekuci->sljedeci;
        return true;
    }
    void pocetak(){
        if(DaLiJePrazna()) throw domain_error("Dvostruka lista je prazna!");
        tekuci=poc;
    }
    void kraj(){
         if(DaLiJePrazna()) throw domain_error("Dvostruka lista je prazna!");
        tekuci=kr;
    }
    void obrisi(){
      if(DaLiJePrazna()) throw domain_error("Dvostruka lista je prazna!");
        vel--;
        if(poc==kr){
            delete tekuci;
            vel=0;
            poc=nullptr;
            tekuci=nullptr;
            kr=nullptr;
        }
        else if(tekuci==poc){
            Cvor<Tip> *pomocni=tekuci->sljedeci;
            delete tekuci;
            tekuci=pomocni;
            poc=tekuci;
            tekuci->prethodni=nullptr;
        }
        else if(tekuci==kr){
            Cvor<Tip> *pomocni=tekuci->prethodni;
            delete tekuci;
            tekuci=pomocni;
            kr=tekuci;
            tekuci->sljedeci=nullptr;
        }
        else{
            Cvor<Tip> *pomocni=tekuci->sljedeci;
            tekuci->prethodni->sljedeci=tekuci->sljedeci;
            tekuci->sljedeci->prethodni=tekuci->prethodni;
            delete tekuci;
            tekuci=pomocni;
        }
    }
    void dodajIspred(const Tip& el){
        if(tekuci==nullptr){
            Cvor<Tip>* novi=new Cvor<Tip>{el,nullptr};
            poc=novi;
            kr=novi;
            tekuci=novi;
        }
        else if(tekuci==poc){
            tekuci->prethodni=new Cvor<Tip>(el,nullptr,tekuci);
            poc=tekuci->prethodni;
        }
        else{
            Cvor<Tip> *novi=new Cvor<Tip>{el,tekuci->prethodni,tekuci};
            tekuci->prethodni->sljedeci=novi;
            tekuci->prethodni=novi;
        }
        vel++;
    }

    void dodajIza(const Tip& el){
        if(tekuci==nullptr){
            Cvor<Tip>*novi=new Cvor<Tip>{el,nullptr};
            tekuci = novi;
            kr= novi;
            poc=novi;
            vel+=1;
            return;
        }
        if(tekuci==kr){
            tekuci->sljedeci=new Cvor<Tip>(el,tekuci,nullptr);
            kr=tekuci->sljedeci;
            vel+=1;
            return;
        }
        
            Cvor<Tip>* novi=new Cvor<Tip>{el,tekuci,tekuci->sljedeci};
            tekuci->sljedeci->prethodni=novi;
            tekuci->sljedeci=novi;
            vel+=1;
    }

    Tip &operator[](int indeks)const{
        if(indeks > vel || indeks < 0) throw range_error("Indeks se ne nalazi u ispravnom opsegu!");
        Cvor<Tip> *pom=poc;
    int i = 0;
        while(i < indeks){ 
            pom=pom->sljedeci;
            i++;
        }
        return pom->element;
    };
};

int main() {
 
 Lista<int>* l;
l = new DvostrukaLista<int>;
for (int i(1); i<=5; i++)
	l->dodajIza(i);
do {
	std::cout << l->trenutni() << " ";
} while(l->sljedeci());
l->dodajIza(6);
l->sljedeci();
std::cout << l->trenutni();
//std::cout <<dajMaksimum(l);
delete l;




  return 0;
}