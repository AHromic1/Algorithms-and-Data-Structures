#include <iostream>
#include <stdexcept>
#include <ctime>
#include <string>
#include <utility>
#include <vector>
#include <queue>
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


/*
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
*/
/*
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
*/
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
  /*  }

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
};*/


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

////HashMapaLan

template <typename TipK, typename TipV>

class HashMapaLan: public Mapa<TipK, TipV>{
    private:

    pair<TipK, TipV>* niz;
     int maks; //maksimalni maks koji se ce po potrebi prosirivati 
    int vel; //stvarna vel

    unsigned int (*funkcija)(TipK, unsigned int);  //neka proizvoljna hash funkcija
    
    bool d;  // za funkciju
    
public:
//konstruktor
    HashMapaLan(): maks(10000), vel(0){  //, tmp(TipV()){
        niz=new pair<TipK, TipV>[maks];
        funkcija=NULL;
        d=false;
    
        for(int i = 0;i < maks; i++){
            niz[i].first=TipK();  //default vrijednost, ovo ili {}
            niz[i].second=TipV();
        }
    }
    
//konstruktor 2
    HashMapaLan(const HashMapaLan<TipK, TipV> &m){
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
     ~HashMapaLan(){
        delete [] niz;
        vel=0;
        maks = 0;  //treba li pr
        funkcija=NULL;
    }


    HashMapaLan<TipK, TipV> &operator =(const HashMapaLan<TipK, TipV> &m){
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
    
    
template <typename TipOznake>
class Grana;
template <typename TipOznake>
class Cvor;
template <typename TipOznake>
class GranaIterator;

template<typename TipOznake>

class UsmjereniGraf{
public:
 
    UsmjereniGraf(int n) {} 
    
    virtual ~UsmjereniGraf() {}
    
    virtual int dajBrojCvorova() const=0;
    
    virtual void postaviBrojCvorova(int n)=0;
    
    virtual void dodajGranu(int p, int d, float t) = 0;
    
    virtual void obrisiGranu(int p, int d)=0;
    
    virtual void postaviTezinuGrane(int p, int d,float t) = 0;
    
    virtual bool postojiGrana(int p, int d)=0;
    
    virtual float dajTezinuGrane(int p, int d) const=0;
    
    //za cvor/grana klase
    
    virtual void postaviOznakuCvora(int n, TipOznake oznaka)=0;
    
    virtual TipOznake dajOznakuCvora(int v) const =0;  //cvor
    
    virtual void postaviOznakuGrane(int p, int d, TipOznake oznaka)=0;
    
    virtual TipOznake dajOznakuGrane(int p, int d) const =0;
    
    virtual Grana<TipOznake> dajGranu(int p, int d) {
        
        return Grana<TipOznake>(this, p, d); 
        
    }
    
    virtual Cvor<TipOznake> dajCvor(int v) {
        return Cvor<TipOznake>(this, v); 
        
    }
    
     virtual GranaIterator<TipOznake> dajSljedecuGranu(int p, int d)=0;
     
    virtual GranaIterator<TipOznake> dajGranePocetak()=0;
    
    virtual GranaIterator<TipOznake> dajGraneKraj()=0;
    
   
   
};



/*Što se tiče klase Cvor, pored metoda dajOznaku i postaviOznaku, klasa Cvor treba
posjedovati konstruktor koji prima pokazivač na UsmjereniGraf i redni broj čvora, te
metodu dajRedniBroj koja vraća redni broj čvora.
*/

template<typename TipOznake>
class Cvor{
    private:
    UsmjereniGraf<TipOznake>* graf;
    int nti;  //redni broj cvora
public:
//konstruktor
    Cvor(UsmjereniGraf<TipOznake>* g, int br): graf(g), nti(br) {
        
    } 
      
    /*TipOznake dajOznaku() const { 
        return  
        
    }*/   //MORA preko grafa, jer je to atribut, ne moze ovako
    
    
    TipOznake dajOznaku() const { 
        return graf->dajOznakuCvora(nti); 
        
    }
    
    void postaviOznaku(TipOznake o){
        graf->postaviOznakuCvora(nti, o);
    }

    
    int dajRedniBroj() const { 
        return nti; 
        
    }
    
};   

/*Klasa Grana treba posjedovati metode: dajTezinu, postaviTezinu, dajOznaku i
postaviOznaku čije je značenje očigledno.
Također treba posjedovati metode dajpCvor i dajdCvor koje trebaju
vraćati objekat tipa Cvor.*/

template<typename TipOznake>

class Grana{
    private:
    
    UsmjereniGraf<TipOznake>* graf;
    int p; //p cvor
    
    int d; //d cvor
    
public:

    Grana(UsmjereniGraf<TipOznake>*g, int c, int go): graf(g), p(c), d(go) {
        
    }
    
    double dajTezinu() const {
        
        return graf->dajTezinuGrane(p, d); 
        
    }
    
    void postaviTezinu(double t) { 
        graf->postaviTezinuGrane(p, d, t); 
        
    }
    
    TipOznake dajOznaku() const {
        return graf->dajOznakuGrane(p, d); 
        
    }
    
    void postaviOznaku(TipOznake o) { 
        graf->postaviOznakuGrane(p, d, o);
        }
        
    Cvor<TipOznake> dajPolazniCvor() const { //const fjnkcije, samo vracaju, nista se dalje ne radi! 
        return graf->dajCvor(p); 
        
    }
    Cvor<TipOznake> dajDolazniCvor() const { 
        return graf->dajCvor(d); 
        
    }
    
};

/*template <typename TipOznake>
class GranaIterator {
public:
 Grana<TipOznake> operator*();
 bool operator==(const GranaIterator &iter) const;
 bool operator!=(const GranaIterator &iter) const;
 GranaIterator& operator++();
 GranaIterator operator++(int);
};
*/

template<typename TipOznake>

class GranaIterator{
private:

    UsmjereniGraf<TipOznake>* graf;
    int p;
    int d;
    
public:

    GranaIterator(UsmjereniGraf<TipOznake>* g, int c, int go): graf(g), p(c), d(go) {
        
    }
    
    Grana<TipOznake> operator*() { 
        return graf->dajGranu(p, d); 
        
    }
    
    bool operator==(const GranaIterator &iter) const {  //klasicno poredjenje
        
        return ( graf==iter.graf && p==iter.p && d==iter.d) ;
    }
    
    
    bool operator!=(const GranaIterator &iter) const {
        //moze i preko prethodne fubkcije msm
 
        return !(graf==iter.graf && p==iter.p && d==iter.d); 
      
    }
    
    GranaIterator &operator ++(){
        //int t = p
        
        if(p==-1 && d==-1){
            p=0;  //JER SU CVOROVI! Nije klasicni ++
            d=-1;
            
        }
        
        GranaIterator i= graf->dajSljedecuGranu(p, d);
        p=i.p;
        d=i.d;
        return *this;
    }
    
    GranaIterator operator ++(int){  //druga verzija, pref
       
        GranaIterator i = *this;  //moze
       
        ++(*this);
        
        return i;
    }
};


/////DRUGI ZADATAK///////

template<typename TipOznake>

class ListaGraf: public UsmjereniGraf<TipOznake>{
    private:

   vector<TipOznake> c;
   
   struct atr{
        float tezina;
        TipOznake oznaka;
        bool e;  //pom za oznacavanje popunjenih/nepopunjenih 
    };  //atr * niz -lakse preko vektora, a u zadatku nije specificirano sta dq se koristi te ce ovdje biti prikazana implementacija
    //pomocu vektora
     vector<vector<atr>>m; //matrica
   
public:

    ListaGraf(int n): UsmjereniGraf<TipOznake>(n){
        m.resize(n); c.resize(n);
        
        for(int i = 0; i < n; i++){
            
            m[i].resize(n);
            
            for(int j = 0; j < n; j++){
                
                m[i][j].e = false; //sve je po defaultu false, slicno kao u pred., kasnije ce se popuniti 
            }
        }
    }
    
    
    int dajBrojCvorova() const override { 
        //for(int i = 0 ; i < n; i++)
        return m.size(); 
        
    }
    
    void postaviBrojCvorova(int n) override  {
        
        if(n <= m.size() - 1) throw ("Nemoguce je postaviti manji broj cvorova od stvarne velicine matrice!");
        
        vector<vector<atr> >m2 (n);
        
        for(int i=0; i<n; i++){
            
            m2.resize(n);
            
            for(int j=0;j<n;j++){
                m2[i][j].e=false;
            }
        }
        //prepisivanje
         int s = m.size();
        for(int i =  0; i < s; i++){
            for(int j = 0; j < s; j++){
                m2[i][j]=m[i][j];
            }
        }
        c.resize(n);
    }
    ///Za ova trazi da su override, jer gore ima neka implementacija!
    void dodajGranu(int p, int d, float t) override {
        atr a;
        a.tezina = t;
        a.e = true;
        m[p][d]=a;
    }
    
    void obrisiGranu(int p, int d) override {
        
        m[p][d].e = false;
    }
    
    void postaviTezinuGrane(int p, int d, float t) override{
        m[p][d].tezina = t;
    }
    
    float dajTezinuGrane(int p, int d) const override {
        return m[p][d].tezina;
    }
    
    bool postojiGrana(int p, int d)  override{
        return m[p][d].e;
    }
    
    void postaviOznakuCvora(int n, TipOznake o) override {
        c[n]=o;
    }
    
    TipOznake dajOznakuCvora(int vertice) const  override{
        return c[vertice];
    }
    
    void postaviOznakuGrane(int p, int d, TipOznake o)  override{
        m[p][d].oznaka = o;
    }
    
    TipOznake dajOznakuGrane(int p, int d) const override {
        return m[p][d].oznaka;
    }
    
    Grana<TipOznake> dajGranu(int p, int d)  override  {
        return Grana<TipOznake>(this, p, d);
    }
    Cvor<TipOznake> dajCvor(int vertice) override {
        return Cvor<TipOznake>(this, vertice);
    }

    GranaIterator<TipOznake> dajGranePocetak()  override{
        GranaIterator<TipOznake> gr(this, 0, -1);
        auto grana = ++gr;
        return grana;
    }
    
    GranaIterator<TipOznake> dajGraneKraj() override  {
        GranaIterator<TipOznake> gr(this, -1, -1);
        return gr;
    }
    GranaIterator<TipOznake> dajSljedecuGranu(int p, int d)  override {

            int s = m.size();  //moze i bez ali hajde

        for(int i = p; i < s; i++){
            for(int j = 0; j < s; j++){
                if(j<=d && i==p ) continue;  //preskoci

                else if(m[i][j].e) {
                    return GranaIterator<TipOznake>(this, i, j);
                }
            }
        }
        return GranaIterator<TipOznake>(this, -1, -1); //nema
    }
   // ~mGraf() {}
};

////BFS I DFS ALGORITMI FUNKCIJE
template <typename t>
void bfs(UsmjereniGraf<t> *g, std::vector<Cvor<t>> &bfsv, Cvor<t> cvor) {
    cvor.postaviOznaku(1);
    bfsv.push_back(cvor);
    std::queue<Cvor<t>> q;
    q.push(cvor);
    while(!q.empty()) {  //sve dok se ne ispremjestaju sve grane
        Cvor<t> c=q.front(); //naprijed pushamo
        q.pop();
       GranaIterator<t> grana=g->dajGranePocetak();
        for(GranaIterator<t> pok=grana;pok!=g->dajGraneKraj();pok++) {
            Cvor<t> pol=(*pok).dajPolazniCvor();
            Cvor<t> dol=(*pok).dajDolazniCvor();
            int pom=0;
            if(dol.dajOznaku()!=1) pom++;
            if(pol.dajRedniBroj()==c.dajRedniBroj() )pom++;
            if(pom==2)
            {
                dol.postaviOznaku(1);
                bfsv.push_back(dol);
                q.push(dol);
            }
        }
    }
}

template <typename t>
void dfs(UsmjereniGraf<t>* g, std::vector<Cvor<t>> &dfsv, Cvor<t> cvor) {
    cvor.postaviOznaku(1);
    dfsv.push_back(cvor); //cvor od kojeg pocinjemo
    GranaIterator<t> gr = g->dajGranePocetak();
    GranaIterator<t> gr2 = gr;
    gr2++;
    for( ;gr2!=g->dajGraneKraj(); gr2++) {
        Cvor<t> dol;
        dol = (*gr2).dajDolazniCvor();
        if((*gr2).dajPolazniCvor().dajRedniBroj() == cvor.dajRedniBroj() && dol.dajOznaku()!=1)
            dfs(g, dfsv, dol); //rekurzija
    }
}

//////
int main(){
    return 0;
}