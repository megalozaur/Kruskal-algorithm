#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Krawedz {
	public:
		bool wybrane=0;
		int poczatek,koniec;
		double waga;
	
	Krawedz(int ipoczatek, int ikoniec, double iwaga) : poczatek(ipoczatek), koniec(ikoniec), waga(iwaga) {}
		
	bool operator < (const Krawedz& k) const {
        return (waga < k.waga);
    }
};
    
ostream& operator<<(ostream& str, const Krawedz& k) {
	int width=1;
	string color="black";
	if (k.wybrane) {width=3; color="red";}
    //return str << "Krawedz " << k.poczatek << " <---("<< k.waga <<")--->" << k.koniec << "\n";
    return str << (char)('A'+k.poczatek-1) << "--" << (char)('A'+k.koniec-1) << " [label=\" "<< k.waga << "\""
		<<" penwidth="<<width
		<<" color="<<color<<"]" << "\n";
}

double operator+ (double second, const Krawedz first) {
        return first.waga + second;
    }


class Polaczenia {
	static const int N=8;
	bool polaczenia[N][N];
	public:
	Polaczenia(): polaczenia{0} {}
	
	int polacz(int w1, int w2){
		if (czy_polaczone(w1,w2)) return 0;
		if (w1>w2) {int tmp=w1; w1=w2; w2=tmp;}
		cout <<"Lacze "<<w1<<" i "<<w2<<"\n";
		for (int w=0;w<=N;w++) {
			if (w!=w1 && w!=w2){
				if ( czy_polaczone(w, w1) ) polacz(w,w2);
				if ( czy_polaczone(w, w2) ) polacz(w,w1);
			}
		polaczenia[w1][w2] = 1;
		}
	}
	
	int czy_polaczone(int w1, int w2){
		if (w1>w2) {int tmp=w1; w1=w2; w2=tmp;}
		return polaczenia[w1][w2] != 0;
	}
};


int main()
{
	vector<Krawedz> dostepne_krawedzie {
		Krawedz(1,2,670), Krawedz(1,3,758),Krawedz(1,4,427),Krawedz(1,5,581),Krawedz(1,6,211),Krawedz(1,7,369),
		Krawedz(2,3,361),Krawedz(2,4,252),Krawedz(2,5,132),Krawedz(2,6,492),Krawedz(2,7,680),
		Krawedz(3,4,332),Krawedz(3,5,493),Krawedz(3,6,699),Krawedz(3,7,759),
		Krawedz(4,5,357),Krawedz(4,6,394),Krawedz(4,7,431),
		Krawedz(5,6,391),Krawedz(5,7,650),
		Krawedz(6,7,521)
		};
	
	vector<Krawedz> wybrane_krawedzie;
	Polaczenia p;
	
	sort(dostepne_krawedzie.begin(), dostepne_krawedzie.end());
    
    for (auto &k : dostepne_krawedzie){
	
    	cout << k;
        if (!p.czy_polaczone(k.poczatek,k.koniec)){ // jesli nie zamkniemy cyklu
			p.polacz(k.poczatek,k.koniec);
			k.wybrane=1;
			wybrane_krawedzie.push_back(k);
		}
}
   	double dlugosc_drogi = accumulate(wybrane_krawedzie.begin(), wybrane_krawedzie.end(), 0.0);
	cout << "Dlugosc drogi przez ponizsze krawedzie to " << dlugosc_drogi << ":\n";

	
	// Zapis struktury grafu do pliku
	ofstream f;
  	f.open ("graf_pelny.dot");
  	f << "graph G {\n";
  	for (auto k : dostepne_krawedzie)
 		f << k;
 	f << "}\n";
 	f.close();	
	
	f.open ("graf_wybrany.dot");
  	f << "graph W {\n";
 	for (auto k : wybrane_krawedzie)
 		f << k;
 	f << "}\n";
 	f.close();
	
    return 0;
}
