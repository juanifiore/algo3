#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <tuple>
#include <list>

using namespace std;

int peso(int n, int m){
	vector<int> ni = {(n/1000)%10,(n/100)%10,(n/10)%10,n%10};
	vector<int> mi = {(m/1000)%10,(m/100)%10,(m/10)%10,m%10};
	int peso = 0;
	for(int j=0;j<4;j++){
		int p = abs(ni[j]-mi[j]);
		if(p > 5){
			p = 10-p;
		}
		peso+=p;
	}
	return peso;
}
	

int clave_mas_cercana_a_0000(vector<int> keys, int n){
	int p;
	int peso_minimo = 21;
	int min_i;
	for(int i=0;i<n;i++){
		p = peso(0000,keys[i]);
		if(p < peso_minimo){
			peso_minimo = p;
			min_i = i;
		}
	}
	return min_i;
}

		
int min_rolls(vector<priority_queue<tuple<int,int>,vector<tuple<int,int>>,greater<tuple<int,int>>>>& grafo, const vector<int>& keys, int inicio,int n){
	int peso_total = 0;
	list<int> pisados;
	pisados.push_back(inicio);
	peso_total += peso(0000,keys[inicio]);
	n--;
	while(n > 0){
		int peso_minimo = 25; //el peso no puede exceder de 20
		//indice del nodo de origen de la arista con menor peso actual
		int nodo_origen;

		//indice del nodo de llegada de la arista con menor peso actual
		int nodo_llegada;

		for(auto nodo : pisados){
			//chequeo entre los nodos ya pisados cual es la arista que tiene menor peso
			if(get<0>(grafo[nodo].top()) < peso_minimo){
				peso_minimo = get<0>(grafo[nodo].top());
				nodo_origen = nodo;
				nodo_llegada = get<1>(grafo[nodo].top());
			}
		}
		grafo[nodo_origen].pop(); // elimino la arista que tenia menor peso
		peso_total += peso_minimo;
		pisados.push_back(nodo_llegada);
		n--;
	}
	return peso_total;
}


int main(){
	int t;
	cin >>t;
	while(t>0){
		int n;
		cin >>n;
		vector<int> keys(n);
		int k;
		for(int i=0;i<n;i++){
			cin >> k;
			keys[i] = k;
		}
		
		//lista de adyacencias, con min heap para los pesos de las aristas
		vector<priority_queue<tuple<int,int>,vector<tuple<int,int>>,greater<tuple<int,int>>>> grafo(n);

		//creo el grafo implementado como lista de adyacencias, usando minheaps
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i!=j){
					int p = peso(keys[i],keys[j]);
					grafo[i].push(make_tuple(p,j));
				}
			}
		}
		
		int inicio = clave_mas_cercana_a_0000(keys, n);

		int peso = min_rolls(grafo, keys, inicio, n);
		
		cout << peso << endl;

		t--;
	}
}

		
				


