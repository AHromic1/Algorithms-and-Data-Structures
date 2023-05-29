#include <iostream>
#include <fstream>

using namespace std;

template<typename Tip>
void bubble_sort(Tip* niz, int vel){
    for(int i = vel - 1; i > 0; i--){  //krece se od kraja
        for(int j = 1; j < i + 1; j++){
            if(niz[j-1] > niz[j]) {//klasicna razmjena, porede se susjedni
                Tip temp = niz[j - 1];
                niz[j - 1] = niz[j];
                niz[j] = temp;
            }
        }
    }
}

template<typename Tip>
void selection_sort(Tip* niz, int vel){
    for(int  i =0; i < vel - 1; i++){
        Tip min = niz[i];
        int mini = i; //indeks minimalnog
        for(int  j = i+1; j < vel; j++ )
        if(niz[j]< min){
            min = niz[j];
            mini = j;
        }
        niz[mini] = niz[i];
        niz[i] = min; //razmijene se, i tako redom do kraja
    }

}

//quick sort/////

template<typename Tip>
int particija(Tip *niz, int f, int l){  //pomocna funkcija za pivot 
    Tip pivot=niz[f];
    int p  = f + 1;
    while(p <= l && niz[p] < pivot) p++;
    for(int i=p+1;i<l + 1; i++) 
    if(niz[i]<pivot){
        Tip temp=niz[p];   //zamjena 
        niz[p]=niz[i];
        niz[i]=temp;
        p++;
    }
    Tip temp=niz[f];   //zamjena
    niz[f]=niz[p-1];
    niz[p-1]=temp;
    return p - 1;
}

template<typename Tip>
void quick_sort_pom(Tip* niz, int f, int l){  //pomocna funkcija za quick sort, sa nizom, indeksom
//prvog i zadnjeg kao parametrima
    if(f < l){ //uslov za kr
        int temp = particija(niz,f,l);
        quick_sort_pom(niz, f, temp - 1);
        quick_sort_pom(niz, temp + 1, l);
    }
}

template<typename Tip>
void quick_sort(Tip *niz, int vel){
    quick_sort_pom(niz,0,vel - 1);
}

///////merge sort//////////

template <typename Tip>
void merge(Tip *niz, const int f, const int p, const int q, const int l){  //merge funkcija-spaja podnizove
    int i = 0;
    int  j = q - f;
    int k =  f;
    Tip *temp = new Tip[l - f + 1]{};

    for(int c = 0 ; c < l - f + 1; c++){  //c kao counter
        temp[c]=niz[f + c];
    }



    while(i <= p - f && j < l - f + 1){
        if(temp[i] < temp[j]){
            niz[k] = temp[i];   
            i++;
        }
        else{
            niz[k] = temp[j];
            j++;
        }
        k++;
    }

    while(i < p -  f + 1){
        niz[k++] = temp[i++];
      
    }

    while(j < l - f + 1){
        niz[k++] = temp[j++];
      
    }
    delete[] temp;  //jer je alocirano, NE ZABORAVITI!!! curi mem
}

template <typename Tip>
void merge_sort_pom(Tip *niz, int f, int l){
    if(f < l){
        int p = (f + l - 1)/2;
        int q = p + 1;
        merge_sort_pom(niz, f, p);  //ide rekurzija
        merge_sort_pom(niz, q, l);
        merge(niz, f, p, q, l);
    }
}

template<typename Tip>
void merge_sort(Tip *niz, int vel){  //krajnja funkcija, s razl parametrima pa  saljem pomocna
    merge_sort_pom(niz, 0, vel - 1);  //poc je 0 na pocetku
    //vel je param a ne velicina!
}


////ostale funkcije/////

//template<typename Tip>
void ucitaj(string filename, int*& niz, int &vel){
    int *temp=new int[vel];  //alociranje
    int el, counter = 0;
    ifstream datoteka_re(filename);  //dat
    if(!datoteka_re) throw "Greska pri otvaranju!";
    for(int i = 0; i < vel; i++){
        while(datoteka_re>>el){  //puni
            temp[i]=el; 
            counter++;
        }
    }
   
    niz = new int[counter];  //counter je nova vel
    for(int i=0; i < counter; i++) niz[i]=temp[i];
    ofstream datoteka_wr(filename);
    if(!datoteka_wr) throw "Greska pri otvaranju!";
    for(int i=0; i<counter; i++) datoteka_wr<<niz[i]<<" ";
    
}

void generisi(string filename, int vel){
    ofstream datoteka(filename);
    if(!datoteka) throw "Greska!";
    for(int i = 0; i < vel; i++){
        datoteka<<rand()<<" ";  //random intovi
    }
}



template<typename Tip>
int ucitaj_niz(){
    cout<<"Unesite brojeve (-1 za kraj): "<<endl;
    int n = 0, i = 0;
    Tip * niz;
    cin>>n;
    while(n!=-1){
    niz[i] = n;
    i++;
    }
    int vel = i; //treba li vratiti?
    return vel;
}

template<typename Tip>
void izaberi(){
    cout<<"Izaberite algoritam sortiranja: "<<endl;
    cout<<"1 - bubble sort"<<endl;
    cout<<"2 - selection sort "<<endl;
    cout<<"3 - quick sort "<<endl;
    cout<<"4 - merge sort "<<endl;

    int izbor = 0;
    cin>> izbor;
    cout<<"Unesite brojeve (-1 za kraj): "<<endl;
    int n = 0, i = 0;
    Tip * niz;
    cin>>n;
    while(n!=-1){
    niz[i] = n;
    i++;
    }
    int vel = i; 
    time_t poc,kr;
    poc=clock();
//sortiranje na osnovu izbora
    if(izbor == 1){
        
        bubble_sort(niz, vel);
        //for(int i = 0; i < vel; i++) cout<<niz[i]<<" ";
    }
    else  if(izbor == 2){
        selection_sort(niz,vel);
    }

        else  if(izbor == 3){
        quick_sort(niz,vel);
    }
    else {
       merge_sort(niz,  vel);
    }
    kr = clock();

    cout<<"Sortiranje niza je ukupno trajalo "<<(kr-poc)/(CLOCKS_PER_SEC/1000)<<" ms"<<endl;  //u milisekundama
   //PROVJERA///
    for(int i=0;i<n-1;i++){
        if(niz[i]>niz[i+1]){
            cout<<"Greska pri sortiranju!"<<endl;
            return;
        }
    }

    cout<<"Unesite ime datoteke"<<endl;
    string ime;
    cin>>ime;
    
    ofstream datoteka;
    datoteka.open(ime);  //nova dat s imenom
    for(int i=0; i < n; i++){  //upisivanje
        datoteka<<niz[i];
        datoteka<<" ";
    }

    datoteka.close(); //zatvaranje dat

    delete[] niz;  //dealoc mora


}





int main(){

int niz[5] = {3, 2, 8, 1, 5};
merge_sort(niz, 5);
for (int i(0); i<5; i++)
    cout << niz[i] << " ";

    return 0;
}