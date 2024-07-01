#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <climits>
#include <list>

using namespace std;

struct arista {int u,v,peso;};

bool bellmanford(list<arista>& grafo, map<int,int>& distancia, int V){

	distancia[grafo.front().u] = 0;

	for(int i=0;i<V;i++){
		for(arista e : grafo){
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

			distancia[si+ni] = 10000;
			distancia[si-1] = 10000;

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
		
		if(bellmanford(grafo,distancia,n)){
			cout << "successful conspiracy" << endl;
		} else {
			cout << "lamentable kingdom" << endl;
		}
		cin >> n;
	}
}

			
