#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <climits>
#include <list>

using namespace std;

struct arista {int u,v,peso;};

void printmap(const map<int, int>& myMap) {
    for (const auto& pair : myMap) {
        cout << "distancia[" << pair.first << "] = " << pair.second << endl;
    }
}

bool bellmanford(list<arista>& grafo, map<int,int>& distancia, int V){

	distancia[grafo.front().u] = 0;
	//vector<int> dist(V+1,INT_MAX);
	//dist[grafo.front().u] = 0;
	//vector<int> distancia(V+2,INT_MAX);

	//distancia[V+1] = 0;

	printmap(distancia);

	for(int i=0;i<V;i++){
		printmap(distancia);
		for(arista e : grafo){
			cout << "CHEQUEO DISTANCIAS \n distancia["<<e.v<<"] > distancia["<<e.u<<"] + "<<e.peso<<"  ("<<distancia[e.v]<<" > "<<distancia[e.u]<<" + "<<e.peso<<")"<<endl;
			if(distancia[e.v] > distancia[e.u] + e.peso){
				distancia[e.v] = distancia[e.u] + e.peso;
			}
		}
	}

	bool hay_ciclo_negativo = false;
	for(arista e : grafo){
		if(distancia[e.v] > distancia[e.u] + e.peso){
			hay_ciclo_negativo = true;
		}
	}
	return hay_ciclo_negativo;
}

int main(){
	int n;
	cin >> n;
	while(n!=0){
		int m;
		cin >> m;
		
		list<arista> grafo;
		map<int,int> distancia;

		for(int l=0;l<m;l++){
			int si,ni,ki;
			string signo;
			cin >>si>>ni>>signo>>ki;

			distancia[si+ni] = 1000;
			distancia[si-1] = 1000;

			if(signo == "gt"){ // el signo es >
				ki = ki*-1-1;
				arista e = {si-1,si+ni,ki};
				grafo.push_back(e);
			} else { 
				ki--;
				arista e = {si+ni,si-1,ki};
				grafo.push_back(e);
			}
		}
		//for(int i=0;i<n;i++){
		//	arista e = {n+1,i,0};
		//	grafo.push_back(e);
		//}
		for (const arista& e : grafo) {
    		    cout << "Arista: " << e.u << " -> " << e.v << ", Peso: " << e.peso << endl;
    		}
		
		if(bellmanford(grafo,distancia,n)){
			cout << "succesfull conspiracy" << endl;
		} else {
			cout << "lamentable kingdom" << endl;
		}
		cin >> n;
	}
}

			
