#include <iostream>
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

    //PR treba li 
    

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

//////TESTOVI///////

int TEST1(){
    NizMapa<int, int> n;
    //combo parnih i neparnih 
    n[0] = 1;
    NizMapa<int, int> n2;
    n2[2] = 3; 

    n = n2; 

    n2.obrisi();
    return n2.brojElemenata();


}

int TEST2(){
    NizMapa<int, int> n;
    //combo parnih i neparnih 
    n[0] = 1;
    n[2] = 3; 
    
    return n.brojElemenata();
}

int TEST3(){
  NizMapa<int, int> n;
    //combo parnih i neparnih 
    n[0] = 1;
    n[2] = 3; 
    n.obrisi(0);
    
    return n.brojElemenata();

}




int main(){
   // NizMapa<string,int> nizm;

   NizMapa<std::string,std::string> m;
m["Sarajevo"] = "BiH";
m["Zagreb"] = "Hrvatska";
cout << m.brojElemenata() << " " << m["Zagreb"] << " '"; // 2 Hrvatska

// Test praznih elemenata
cout << m["Beograd"] <<"' '"; // ''
cout << m["zagreb"] << "' "; // ''
m.obrisi("Zagreb");

// Potpuno korektna NizMapa nece kreirati objekte "Beograd" i "zagreb"
// jer oni nemaju vrijednosti pa ce se ispod ispisati 1
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
