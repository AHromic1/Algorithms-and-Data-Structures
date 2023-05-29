#include <iostream>
#include <stdexcept>
#include <vector>


using namespace ::std;

//apstraktna klasa UsmjereniGraf

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

class MatricaGraf: public UsmjereniGraf<TipOznake>{
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

    MatricaGraf(int n): UsmjereniGraf<TipOznake>(n){
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


int main() {
    
  UsmjereniGraf<bool> *g = new MatricaGraf<bool>(6);
  g->dodajGranu(0, 1, 2.5);
  g->dodajGranu(1, 2, 1.2);
  g->dodajGranu(1, 3, 0.1);
  g->dodajGranu(3, 3, -4.0);
  g->dodajGranu(2, 4, 3.14);
  g->dodajGranu(2, 3, 2.73);
  g->dodajGranu(3, 5, 1);
  g->dodajGranu(5, 2, -5.0);
  for (int i = 0; i < 6; i++)
    for (int j = 0; j < 6; j++)
      cout << g->postojiGrana(i, j);
  delete g;
    return 0;
}
