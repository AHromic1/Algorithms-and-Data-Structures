#include <iostream>
#include <stdexcept>
#include <ctime>
#include <string>
#include <utility>
using namespace std;

/////////Mape iz pripremne zadace 9//////////////////


////mape iz pripremne 8 i 6:
template <typename TipK, typename TipV>

//apstraktna klasa 
class Mapa{
    public: 
    Mapa(){}
    virtual ~ Mapa() {};  
    virtual  TipV operator[] (const TipK key) const = 0;
    virtual TipV &operator[] (TipK key) = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const TipK &key) = 0; 

};
/////


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





/////////////  
template<typename TipK, typename TipV>
class AVLStabloMapa: public Mapa<TipK, TipV>{
    struct Cvor{
        TipK klj;
        TipV vr;
        Cvor* roditelj, * lijevodijete,* desnodijete;
        int balans;
        Cvor(TipK k, TipV v, Cvor* l, Cvor* d, Cvor* p): balans(0), klj(k), vr(v), lijevodijete(l), desnodijete(d), roditelj(p){}
    }; //redoslijed bitan!
    //u cvor je dodan balans

    Cvor* korijenski;
    int vel;
    TipV defempt;
    
    Cvor* trazi(const TipK& klj, Cvor* cvor) const {
        if(cvor == 0) return 0;
        else if(klj == cvor->klj) return cvor;
        else if(klj < cvor->klj) return trazi(klj, cvor->lijevodijete);
        return trazi(klj, cvor->desnodijete); //vece
    }
    
    int visina(Cvor* p) {
	    int t;
	    if (p == NULL)	return -1;  //default vrijednost
	    else {
		    t = p -> balans;  
		    return t;
	    }
    }
 
    Cvor* srlfunk(Cvor* &p1) {
	    Cvor* p2;
	    p2 = p1->lijevodijete;
	    p1->lijevodijete = p2->desnodijete;
	    p2->desnodijete = p1;
	    p1->balans = max(visina(p1->lijevodijete),visina(p1->desnodijete)) + 1;
	    p2->balans = max(visina(p2->lijevodijete),p1->balans) + 1;
        //p1->balans++; p2->balans++;
	    return p2;
    }
    ///
    Cvor* srrfunk(Cvor* &p1) {
    	Cvor* p2;
	    p2 = p1->desnodijete;
	    p1->desnodijete = p2->lijevodijete;
	    p2->lijevodijete = p1;
	    p1->balans = max(visina(p1->lijevodijete),visina(p1->desnodijete)) + 1;
	    p2->balans = max(p1->balans,visina(p2->desnodijete)) + 1;
	    return p2;
    }   
    
    //iskoristene srrfunk i srlfunk
    Cvor* drlfunk(Cvor* &p1) {
	    p1->lijevodijete = srrfunk(p1->lijevodijete);
	    return srlfunk(p1);
    }

    Cvor* drrfunk(Cvor* &p1) {
	    p1->desnodijete = srlfunk(p1->desnodijete);
	    return srrfunk(p1);
    }
    
   //izmjene su u dodaj! (detaljnije opisano u komentaru na kraju zadatka)
    void dodaj(const TipK& klj,const TipV &vr, Cvor*& cvor, Cvor* roditelj){
      int maksi;
        if(cvor == 0){
            cvor=new Cvor(klj, vr, 0, 0, roditelj);
            vel++;
        }
        else if(klj < cvor->klj) {
            dodaj(klj, vr, cvor->lijevodijete, cvor); //ide u lijevo podstablo kao i inace
            if ((visina(cvor->lijevodijete) - visina(cvor->desnodijete))==2){ //uslov ispunjen za rotaciju
	            if (klj < cvor->lijevodijete->klj) cvor = srlfunk(cvor); //poziv ranije definisane funkcije
	            else cvor=drlfunk(cvor);
	        }
        }
        else if (klj > cvor->klj){
	      dodaj(klj, vr, cvor->desnodijete, cvor);
	      if ((visina(cvor->desnodijete) - visina(cvor->lijevodijete))==2){ //ponovo sve isto, samo za desno stablo, jer je ovo slucaj za vece vrijednsoti
		    if (klj > cvor->desnodijete->klj) cvor=srrfunk(cvor);
		    else cvor = drrfunk(cvor);
	      }
	    }
	   
	    int n1, n2; 
        
	    n1=visina(cvor->lijevodijete); ///MORA u odvojene varijable ili pada sedmi test
	    n2=visina(cvor->desnodijete);
	
	    maksi=max(n1,  n2 );
	    cvor->balans = maksi + 1;
	  
    }
    
    void brisi(Cvor* c){
        if(c){
            brisi(c->lijevodijete);  //brisemo rekurzivno lijevu pa desnu granu i napokon korijen
            brisi(c->desnodijete);
            delete c;
            vel--;
        }
        
    }
    
    void kopiraj(Cvor*& c1, Cvor* c2, Cvor* roditelj){
        if(c2 == 0) return;  //ne prihvata izuzetak!
        c1 = new Cvor(c2->klj, c2->vr, 0, 0, roditelj);
        kopiraj(c1->lijevodijete, c2->lijevodijete, c1);
        kopiraj(c1->desnodijete, c2->desnodijete, c1);
        vel++;
    }
    
    bool obrisiP(Cvor* kor,const TipK &k){
        Cvor* p=kor;
        Cvor* prvi=0;
        Cvor* m=0;
        Cvor* pm=0;
        Cvor* tmp=0;
        while(p!=0 && k!=p->klj){
            prvi=p;
            if(k<p->klj) p=p->lijevodijete;
            else p=p->desnodijete;
        }
        if(p==0) return false;
        if(p->lijevodijete==0) m=p->desnodijete;
        else{
            if(p->desnodijete==0) m=p->lijevodijete;
            else{
                pm=p;
                m=p->lijevodijete;
                tmp=m->desnodijete;
                while(tmp!=0){
                    pm=m;
                    m=tmp;
                    tmp=m->desnodijete;
                }
                if(pm!=p){
                    pm->desnodijete=m->lijevodijete;
                    m->lijevodijete=p->lijevodijete;
                }
                m->desnodijete=p->desnodijete;
            }
        }
        if(prvi==0) korijenski=m;
        else{
            if(p==prvi->lijevodijete) prvi->lijevodijete=m;
            else prvi->desnodijete=m;
        }
        delete p;
        return true;
    }
    
public:
//konstruktori
    AVLStabloMapa(): Mapa<TipK, TipV>(), korijenski(0), vel(0), defempt(TipV()) {

    }
    
    AVLStabloMapa(const AVLStabloMapa<TipK, TipV> &am): korijenski(0), vel(0), defempt(TipV()) {
        kopiraj(korijenski, am.korijenski, 0);
    }

    //destruktor
    
    ~AVLStabloMapa(){
        if(vel) //ako nije prazno
        brisi(korijenski);
    }


    AVLStabloMapa<TipK, TipV>& operator=(const AVLStabloMapa<TipK, TipV> &m){
        if(this!=&m) {
        
        brisi(korijenski);
        korijenski=0;
        
        kopiraj(korijenski, m.korijenski, 0);
        }
        return *this;
    }

    ////
    int brojElemenata() const { 
        return vel; 
        }
    
    TipV &operator [] ( TipK klj){
        dodaj(klj, TipV(), korijenski, 0);
        Cvor* c=trazi(klj, korijenski);
        if(c==0) return defempt;
        return c->vr;
    }
     TipV operator [] (const TipK klj) const{
        Cvor* c = trazi(klj, korijenski);
        if(c==0) return defempt; //ne moze tipv default, deklarisala varijablu
        else return c->vr;
    }
    void obrisi(){
        brisi(korijenski);
        korijenski = 0;
    }

    void obrisi(const TipK &klj){
         Cvor* r = korijenski;
        Cvor* temp = 0;
        Cvor* m = 0;
        Cvor* pm = 0;
        Cvor* tmp = 0;
        while(r != 0 && klj != r->klj){
            temp = r;
            if(klj < r->klj) 
            r = r->lijevodijete;
            else 
            r = r->desnodijete;
        }
        if(r == 0) throw("Prazno!");
        if(r->lijevodijete == 0) m = r->desnodijete;
        else{
            if(r->desnodijete == 0) m = r->lijevodijete;
            else{
                pm = r;
                m = r->lijevodijete;
                tmp = m->desnodijete;
                while(tmp!= 0){
                    pm = m;
                    m = tmp;
                    tmp = m->desnodijete;
                }
                if(pm != r){
                    pm->desnodijete = m->lijevodijete;
                    m->lijevodijete = r->lijevodijete;
                }
                m->desnodijete = r->desnodijete;
            }
        }
        if(temp == 0) korijenski = m;
        else{
            if(r == temp->lijevodijete) temp->lijevodijete = m;
            else temp->desnodijete = m;
        }
        delete r;
         vel--;
    }

};


/*Razlika izmedju AVL i obicnog stabla je u balansiranju cvorova, tako da je razlika u visini uvijek najvise 1, a najmanje -1.
Stoga, izmjene u kodu su najvise dosle do izrazaja u metodama poput dodaj, gdje, po dodavanju, treba eventualno
izvrisiti rotaciju. 
Sto se ostatka koda tice logika je manje - vise ista. Takodjer su dodane i pomocne, rekurzivne funkcije u private dijelu klase.
One su zatm pozivane iz public dijela. Npr visina koja je specificirana u postavci zadatka, pomocu koje se moze
odrediti balans, te i sam atribut balans u cvor da bi se poboljsala efikasnost i prolaznost testova.
*/

int main (){
  /*  // Osnovni test funkcionalnosti AVLStabloMapa
AVLStabloMapa<std::string,std::string> m;
m["Sarajevo"] = "BiH";
m["Zagreb"] = "Hrvatska";
cout << m.brojElemenata() << " " << m["Zagreb"] << " '"; // 2 Hrvatska

// Test praznih elemenata
cout << m["Beograd"] <<"' '"; // ''
cout << m["zagreb"] << "' "; // ''
m.obrisi("Zagreb");

// Potpuno korektna AVLStabloMapa nece kreirati objekte "Beograd" i "zagreb"
// jer oni nemaju vri pa ce se ispod ispisati 1
// Ali to zahtijeva implementaciju "Pristupnika" pa cemo priznavati
// rjesenje koje ispise broj 3
cout << m.brojElemenata(); // 3 ili 1

// Test brisanja
cout << " '" << m["Zagreb"] << "' " ; // ''
m.obrisi();
cout << m.brojElemenata(); // 0
cout << " '" << m["Sarajevo"] << "' "; // ''

    cout<<"kraj";*/


      srand(time(NULL));
 BinStabloMapa<int, int>bm;
    NizMapa<int, int>nm;
   // HashMapa<int, int>hm;
   // hm.definisiHashFunkciju(hashFunkcija);
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
    
    
    
////TRAZENEJ///////

    v1=clock();
    bm[1000];
    v2=clock();
    cout<<"Bsm: "<<(v2-v1)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
    
    v3=clock();
    cout<<nm[50]<<endl;
    v4=clock();
    cout<<"Nm: "<<(v4-v3)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
    
   
    
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
    
v1 = 0;
v2 = 0;
////avl 
    for(int i=0;i<10000;i++){
        v1=clock();
        nm[rand()]=rand();
        v2=clock();
        if(i > 1 && i < 9) cout<<"AVL  "<<(v2-v1)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
        else continue;
        v1=0; 
        v2=0;
    }   
    
    nm[5000]=10;
    
   
    v1 = 0; v2 = 0;
    v1=clock();
    cout<<nm[1000]<<endl;
    v2=clock();
    cout<<"AVL stablo mapa"<<(v2-v1)/(CLOCKS_PER_SEC/1000)<<" ms."<<endl;
    
    cout<<"kraj";
    return 0;
}