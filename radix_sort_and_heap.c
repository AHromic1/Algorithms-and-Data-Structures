#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



/////PRVI ZADATAK///////

//pomocna funkcija za maksimalni element

int maksimalni(vector<int> &n)  //ne zna se vel 
{
	int max = n[0]; //maksimalni privremeno inic na prvi
	int maxi = 0;
	for (int i = 1; i < n.size(); i++)  //moze i od 0, ali nema potrebe
		if (n[i] > max){
			max = n[i];
			maxi = i;  //indeks maksimalnog
			
		}
	return max;
}
 

///pomocni counting sort  - pomaze za razvrstavanje dijelova kljuceva u radixu

void CountS(vector<int> &a, int dj)
{
        int vel = a.size();
        	vector<int>pom;
	pom.resize(vel);
	int br[10] = {0};
 

	for (int i = 0; i < vel; i++)
		br[(a[i] / dj) % 10]++;
 

	for (int i = 1; i < 10; i++)
		br[i] += br[i-1];
 
	
	for (int i = vel - 1; i >= 0; i--)
	{
		pom[br[(a[i] / dj) % 10] - 1] = a[i];
		br[(a[i] / dj) % 10]--;
	}

	for (int i = 0; i < vel; i++)
		a[i] = pom[i];
}
 


///rezultatna funkcija
void radixSort(vector<int> &a)
{
	int M;
	M = maksimalni(a);
	
	for (int dj = 1; M/dj > 0; dj *= 10)
		CountS(a, dj);
}



//////DRUGI ZADATAK///////

///pom funkcija za korekciju

void PopraviDolje(int i, vector<int> &a, int vel) {
int najveci = i;
int LD = 2 * i + 1;  //lijevo 
int DD = 2 * i + 2;  //desno
if (LD < vel && a[LD] > a[najveci]) najveci = LD;
if (DD < vel && a[DD] > a[najveci]) najveci = DD;
if (najveci != i) {
swap(a[i], a[najveci]);  //zamjena i korigiranje
PopraviDolje(najveci, a, vel);  //rekurzivni poziv
}
}


void stvoriGomilu(vector<int> &a){
    
    int vel=a.size();
    for (int i=vel/2 - 1; i >= 0; i--) PopraviDolje(i, a, vel);  //radi i sa bez -1!!!
}

//pomocna funkcija za korekciju 2

void PopraviGore(int i, vector<int> &a) {
    while ((i != 0) && (a[i]>a[(i-1)/2])) {
        swap(a[i], a[(i-1)/2]);
        i=(i-1)/2;
    }
}


void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina){
     a.push_back(umetnuti);
     velicina++;
     PopraviGore(velicina-1, a);
}

int izbaciPrvi(vector<int> &a, int &velicina){
    if(velicina == 0) throw "Greska! Gomila je trenutno prazna!";
    velicina--;  //vel umanjena
    swap(a[0], a[velicina]);  //zamjena
    if (velicina != 0) PopraviDolje(0, a, velicina);  //korekcija, jer je doslo do promjene
    return a[velicina]; 

}

void gomilaSort(vector<int> &a){
    stvoriGomilu(a);
    int vel = a.size();
    for(int i = vel-1; i > 0; i--){
        swap(a[0], a[i]); //zamjena
        vel--;  
        PopraviDolje(0, a, vel);
    }
    
}
int main()
{
    /* vector<int> a;
    a.push_back(545);
    a.push_back(1545);
    a.push_back(4536);
    a.push_back(124121);
    a.push_back(1);
    a.push_back(95468);
    radixSort(a);
    for(int i(0);i<a.size();i++){
        cout<<a[i]<<" ";
    }*/
       vector<int> a;
    vector<int> b;
    a.push_back(545);
    a.push_back(1545);
    a.push_back(4536);
    a.push_back(124121);
    a.push_back(1);
    a.push_back(95468);
    for(int i=0;i<10000;i+=13){
        a.push_back(i);
    }
    for(int i=0;i<a.size();i++){
        b.push_back(a[i]);
    }
    radixSort(a);
    gomilaSort(b);
    bool testOk = true;
    for(int i(0);i<a.size();i++){
        if(a[i]!=b[i]) testOk = false;;
    }
    if(testOk) cout<<"OK";
    return 0;
}